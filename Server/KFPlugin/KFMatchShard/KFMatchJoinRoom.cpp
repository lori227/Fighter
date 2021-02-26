#include "KFMatchJoinRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    KFMatchJoinRoom::KFMatchJoinRoom()
    {
        _type = KFMatchEnum::CreateRoom;
    }

    void KFMatchJoinRoom::InitRoom( std::shared_ptr<KFMatchQueue> match_queue, std::shared_ptr<KFMatchPlayer> match_player,
                                    const std::string& title, const std::string& password, bool add_robot )
    {
        KFMatchRoom::InitRoom( match_queue, match_player, title, password, add_robot );
        _title = title;
        _password = password;

        _master_player_id = match_player->_pb_player.id();
        _master_player_name = match_player->_pb_player.name();

        // 添加玩家
        KFMatchRoom::AddPlayer( match_player );
    }

    void KFMatchJoinRoom::SaveTo( KFMsg::PBMatchRoom* pb_room, bool is_player_list )
    {
        KFMatchRoom::SaveTo( pb_room, is_player_list );

        pb_room->set_title( _title );
        pb_room->set_password( _password );
        pb_room->set_masterid( _master_player_id );
        pb_room->set_mastername( _master_player_name );
    }

    bool KFMatchJoinRoom::AddPlayer( std::shared_ptr<KFMatchPlayer> match_player )
    {
        // 先通知有玩家加入
        KFMsg::MsgAddMatchPlayerAck ack;
        match_player->SaveTo( ack.mutable_pbplayer() );
        SendToRoom( KFMsg::MSG_ADD_MATCH_PLAYER_ACK, &ack );

        // 加入玩家列表
        KFMatchRoom::AddPlayer( match_player );
        return false;
    }

    bool KFMatchJoinRoom::IsMatched( std::shared_ptr<KFMatchPlayer> match_player )
    {
        return false;
    }

    uint32 KFMatchJoinRoom::CancelMatch( uint64 player_id )
    {
        auto result = KFMatchRoom::CancelMatch( player_id );
        if ( result == KFMatchEnum::CancelOk )
        {
            ChangeMasterPlayer( player_id );
            SendLeaveToRoom( player_id, KFMsg::Leave );
        }

        return result;
    }

    void KFMatchJoinRoom::ChangeMasterPlayer( uint64 player_id )
    {
        if ( player_id != _master_player_id )
        {
            return;
        }

        for ( auto& iter : _player_list._objects )
        {
            auto match_player = iter.second;
            if ( !match_player->_pb_player.isrobot() )
            {
                _master_player_id = match_player->_id;
                _master_player_name = match_player->_pb_player.name();

                // 更新给客户端
                KFMsg::MsgChangeMatchMasterAck ack;
                ack.set_playerid( _master_player_id );
                ack.set_name( _master_player_name );
                return SendToRoom( KFMsg::MSG_CHANGE_MATCH_MASTER_ACK, &ack );
            }
        }
    }

    // 加入玩家
    uint32 KFMatchJoinRoom::JoinPlayer( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, const std::string& password )
    {
        if ( _version != version )
        {
            return KFMsg::MatchRoomVersionError;
        }

        if ( _password != password )
        {
            return KFMsg::MatchRoomPasswordError;
        }

        if ( _player_list.Size() >= _match_queue->_match_setting->_max_count )
        {
            return KFMsg::MatchRoomIsFull;
        }

        if ( _player_list.Find( pb_player->id() ) != nullptr )
        {
            return KFMsg::MatchRoomJoinAlready;
        }

        // 加入玩家
        auto match_player = __MAKE_SHARED__( KFMatchPlayer );
        match_player->CopyFrom( pb_player );
        AddPlayer( match_player );

        // 通知新加入的玩家
        SendJoinRoomToPlayer( pb_player->id(), pb_player->serverid() );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::KickPlayer( uint64 master_id, uint64 player_id )
    {
        if ( _master_player_id != master_id )
        {
            return KFMsg::MatchRoomKickMaster;
        }

        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMsg::MatchRoomStartCanNotKick;
        }

        auto match_player = _player_list.Find( player_id );
        if ( match_player == nullptr )
        {
            return KFMsg::MatchRoomPlayerNoInRoom;
        }

        // 通知玩家被踢了
        KFMsg::S2SKickMatchToGameAck ack;
        ack.set_playerid( player_id );
        _kf_route->RepeatToEntity( match_player->_pb_player.serverid(), player_id, KFMsg::S2S_KICK_MATCH_TO_GAME_ACK, &ack );

        // 发送离开消息
        SendLeaveToRoom( player_id, KFMsg::Kick );

        // 删除玩家
        _player_list.Remove( player_id );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::FightMatch( uint64 player_id )
    {
        if ( _master_player_id != player_id )
        {
            return KFMsg::MatchRoomFightMaster;
        }

        // 需要全部准备完成
        if ( !CheckAllPrepare() )
        {
            return KFMsg::MatchRoomNotPrepare;
        }

        // 如果需要补满机器人
        if ( _is_add_robot )
        {
            while ( _player_list.Size() < _match_queue->_match_setting->_max_count )
            {
                auto robot = CreateMatchRobot();
                _player_list.Insert( robot->_id, robot );
            }
        }

        ChangeState( KFMatchEnum::CreateState, 10 );
        _match_queue->RoomMatchFinish( this );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::PrepareMatch( uint64 player_id, bool prepare )
    {
        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMsg::MatchRoomCanNotPrepare;
        }

        auto match_player = _player_list.Find( player_id );
        if ( match_player == nullptr )
        {
            return KFMsg::MatchRoomPlayerNoInRoom;
        }

        match_player->_pb_player.set_prepare( prepare );

        // 通知房间其他人
        KFMsg::MsgPrePareMatchAck ack;
        ack.set_playerid( player_id );
        ack.set_prepare( prepare );
        SendToRoom( KFMsg::MSG_PREPATE_MATCH_ACK, &ack );

        return KFMsg::Ok;
    }

    bool KFMatchJoinRoom::CheckAllPrepare()
    {
        for ( auto& iter : _player_list._objects )
        {
            auto match_player = iter.second;
            if ( match_player->_id == _master_player_id )
            {
                continue;
            }

            if ( !match_player->_pb_player.prepare() )
            {
                return false;
            }
        }

        return true;
    }


    uint32 KFMatchJoinRoom::InviteMatch( uint64 invite_id, uint64 player_id, uint64 server_id )
    {
        if ( _player_list.Size() >= _match_queue->_match_setting->_max_count )
        {
            return KFMsg::MatchInviteMaxCount;
        }

        KFMsg::MsgInviteMatchAck ack;
        ack.set_playerid( invite_id );
        SaveTo( ack.mutable_pbroom(), false );
        _kf_route->SendToEntity( server_id, player_id, KFMsg::MSG_INVITE_MATCH_ACK, &ack );
        return KFMsg::Ok;
    }
}