#include "KFMatchJoinRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    KFMatchJoinRoom::KFMatchJoinRoom()
    {
        _type = KFMatchEnum::CreateRoom;
    }

    void KFMatchJoinRoom::InitRoom( KFMatchQueue* kfqueue, KFMatchPlayer* kfplayer, const std::string& title, const std::string& password, bool addrobot )
    {
        KFMatchRoom::InitRoom( kfqueue, kfplayer, title, password, addrobot );
        _title = title;
        _password = password;

        _master_player_id = kfplayer->_pb_player.id();
        _master_player_name = kfplayer->_pb_player.name();

        // 添加玩家
        KFMatchRoom::AddPlayer( kfplayer );
    }

    void KFMatchJoinRoom::SaveTo( KFMsg::PBMatchRoom* pbroom, bool isplayerlist )
    {
        KFMatchRoom::SaveTo( pbroom, isplayerlist );

        pbroom->set_title( _title );
        pbroom->set_password( _password );
        pbroom->set_masterid( _master_player_id );
        pbroom->set_mastername( _master_player_name );
    }

    bool KFMatchJoinRoom::AddPlayer( KFMatchPlayer* kfplayer )
    {
        // 先通知有玩家加入
        KFMsg::MsgAddMatchPlayerAck ack;
        kfplayer->SaveTo( ack.mutable_pbplayer() );
        SendToRoom( KFMsg::MSG_ADD_MATCH_PLAYER_ACK, &ack );

        // 加入玩家列表
        KFMatchRoom::AddPlayer( kfplayer );
        return false;
    }

    bool KFMatchJoinRoom::IsMatched( KFMatchPlayer* kfplayer )
    {
        return false;
    }

    uint32 KFMatchJoinRoom::CancelMatch( uint64 playerid )
    {
        auto result = KFMatchRoom::CancelMatch( playerid );
        if ( result == KFMatchEnum::CancelOk )
        {
            ChangeMasterPlayer( playerid );
            SendLeaveToRoom( playerid, KFMsg::Leave );
        }

        return result;
    }

    void KFMatchJoinRoom::ChangeMasterPlayer( uint64 playerid )
    {
        if ( playerid != _master_player_id )
        {
            return;
        }

        for ( auto& iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( !kfplayer->_pb_player.isrobot() )
            {
                _master_player_id = kfplayer->_id;
                _master_player_name = kfplayer->_pb_player.name();

                // 更新给客户端
                KFMsg::MsgChangeMatchMasterAck ack;
                ack.set_playerid( _master_player_id );
                ack.set_name( _master_player_name );
                return SendToRoom( KFMsg::MSG_CHANGE_MATCH_MASTER_ACK, &ack );
            }
        }
    }

    // 加入玩家
    uint32 KFMatchJoinRoom::JoinPlayer( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, const std::string& password )
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

        if ( _player_list.Find( pbplayer->id() ) != nullptr )
        {
            return KFMsg::MatchRoomJoinAlready;
        }

        // 加入玩家
        auto kfplayer = __KF_NEW__( KFMatchPlayer );
        kfplayer->CopyFrom( pbplayer );
        AddPlayer( kfplayer );

        // 通知新加入的玩家
        SendJoinRoomToPlayer( pbplayer->id(), pbplayer->serverid() );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::KickPlayer( uint64 masterid, uint64 playerid )
    {
        if ( _master_player_id != masterid )
        {
            return KFMsg::MatchRoomKickMaster;
        }

        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMsg::MatchRoomStartCanNotKick;
        }

        auto kfplayer = _player_list.Find( playerid );
        if ( kfplayer == nullptr )
        {
            return KFMsg::MatchRoomPlayerNoInRoom;
        }

        // 通知玩家被踢了
        KFMsg::S2SKickMatchToGameAck ack;
        ack.set_playerid( playerid );
        _kf_route->RepeatToEntity( kfplayer->_pb_player.serverid(), playerid, KFMsg::S2S_KICK_MATCH_TO_GAME_ACK, &ack );

        // 发送离开消息
        SendLeaveToRoom( playerid, KFMsg::Kick );

        // 删除玩家
        _player_list.Remove( playerid );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::FightMatch( uint64 playerid )
    {
        if ( _master_player_id != playerid )
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
                auto kfrobot = CreateMatchRobot();
                _player_list.Insert( kfrobot->_id, kfrobot );
            }
        }

        ChangeState( KFMatchEnum::CreateState, 10 );
        _match_queue->RoomMatchFinish( this );
        return KFMsg::Ok;
    }

    uint32 KFMatchJoinRoom::PrepareMatch( uint64 playerid, bool prepare )
    {
        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMsg::MatchRoomCanNotPrepare;
        }

        auto kfplayer = _player_list.Find( playerid );
        if ( kfplayer == nullptr )
        {
            return KFMsg::MatchRoomPlayerNoInRoom;
        }

        kfplayer->_pb_player.set_prepare( prepare );

        // 通知房间其他人
        KFMsg::MsgPrePareMatchAck ack;
        ack.set_playerid( playerid );
        ack.set_prepare( prepare );
        SendToRoom( KFMsg::MSG_PREPATE_MATCH_ACK, &ack );

        return KFMsg::Ok;
    }

    bool KFMatchJoinRoom::CheckAllPrepare()
    {
        for ( auto& iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( kfplayer->_id == _master_player_id )
            {
                continue;
            }

            if ( !kfplayer->_pb_player.prepare() )
            {
                return false;
            }
        }

        return true;
    }


    uint32 KFMatchJoinRoom::InviteMatch( uint64 inviteid, uint64 playerid, uint64 serverid )
    {
        if ( _player_list.Size() >= _match_queue->_match_setting->_max_count )
        {
            return KFMsg::MatchInviteMaxCount;
        }

        KFMsg::MsgInviteMatchAck ack;
        ack.set_playerid( inviteid );
        SaveTo( ack.mutable_pbroom(), false );
        _kf_route->SendToEntity( serverid, playerid, KFMsg::MSG_INVITE_MATCH_ACK, &ack );
        return KFMsg::Ok;
    }
}