#include "KFMatchRoom.h"
#include "KFMatchQueue.h"
#include "KFConfig/KFNameConfig.hpp"
#include "KFConfig/KFHeroConfig.hpp"

namespace KFrame
{
    void KFMatchRoom::InitRoom( std::shared_ptr<KFMatchQueue> match_queue, std::shared_ptr<KFMatchPlayer> match_player,
                                const std::string& title, const std::string& password, bool add_robot )
    {
        _match_queue = match_queue;
        _is_add_robot = add_robot;
        _state = KFMatchEnum::MatchState;
        _grade = match_player->_pb_player.grade();
        _version = match_player->_version;
        _battle_server_id = match_player->_battle_server_id;
        _id = KFGlobal::Instance()->STMakeUuid();
    }

    void KFMatchRoom::SaveTo( KFMsg::PBMatchRoom* pb_room, bool is_player_list )
    {
        pb_room->set_matchid( _match_queue->_match_setting->_id );
        pb_room->set_roomid( _id );
        pb_room->set_version( _version );
        pb_room->set_maxplayer( _match_queue->_match_setting->_max_count );
        pb_room->set_nowplayer( _player_list.Size() );
        pb_room->set_grade( _grade );
        pb_room->set_addrobot( _is_add_robot );

        if ( is_player_list )
        {
            for ( auto& iter : _player_list._objects )
            {
                auto player = iter.second;
                player->SaveTo( pb_room->add_pbplayer() );
            }
        }
    }

    void KFMatchRoom::ChangeState( uint32 state, uint32 time )
    {
        _state = state;
        _timer.StartLoop( time );
        __LOG_DEBUG__( "room=[{}] state=[{}] time=[{}]", _id, _state, time );
    }

    bool KFMatchRoom::AddPlayer( std::shared_ptr<KFMatchPlayer> match_player )
    {
        match_player->_match_room = this;
        _player_list.Insert( match_player->_id, match_player );
        return false;
    }

    bool KFMatchRoom::CheckFull()
    {
        auto ok = ( _player_list.Size() >= _match_queue->_match_setting->_max_count );
        if ( ok )
        {
            ChangeState( KFMatchEnum::CreateState, 1 );
        }

        return ok;
    }

    bool KFMatchRoom::IsValid()
    {
        return _state != KFMatchEnum::DestroyState;
    }

    bool KFMatchRoom::Run()
    {
        if ( _timer.DoneTimer() )
        {
            switch ( _state )
            {
            case KFMatchEnum::CreateState:
                CreateRoom();
                break;
            default:
                break;
            }
        }

        return IsValid();
    }

    void KFMatchRoom::CreateRoom()
    {
        ChangeState( KFMatchEnum::CreateState, 5000 );

        KFMsg::S2SCreateRoomToRoomReq req;
        req.set_roomid( _id );
        req.set_version( _version );
        req.set_serverid( _battle_server_id );
        req.set_matchid( _match_queue->_match_setting->_id );

        for ( auto& iter : _player_list._objects )
        {
            auto player = iter.second;
            player->SaveTo( req.add_pbplayer() );
        }

        _kf_route->SendToBalance( __STRING__( room ), KFMsg::S2S_CREATE_ROOM_TO_ROOM_REQ, &req );
    }

    void KFMatchRoom::AffirmCreate()
    {
        ChangeState( KFMatchEnum::DestroyState, 100 );
    }

    uint32 KFMatchRoom::CancelMatch( uint64 player_id )
    {
        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMatchEnum::CancelFailed;
        }

        // 删除玩家
        auto match_player = _player_list.Remove( player_id );
        if ( match_player != nullptr )
        {
            match_player->_match_room = nullptr;
        }

        // 判断是否全是机器人
        for ( auto iter : _player_list._objects )
        {
            if ( !iter.second->_pb_player.isrobot() )
            {
                return KFMatchEnum::CancelOk;
            }
        }

        // 如果没有真是玩家, 房间销毁
        _match_queue->RemoveRoom( shared_from_this() );
        return KFMatchEnum::CancelDestory;
    }

    bool KFMatchRoom::IsMatched( std::shared_ptr<KFMatchPlayer> match_player )
    {
        // 版本号
        if ( match_player->_version != _version )
        {
            return false;
        }

        // 服务器id
        if ( match_player->_battle_server_id != _battle_server_id )
        {
            return false;
        }

        return true;
    }

    bool KFMatchRoom::AddRobot()
    {
        return false;
    }

    std::shared_ptr<KFMatchPlayer> KFMatchRoom::CreateMatchRobot()
    {
        auto robot = __MAKE_SHARED__( KFMatchPlayer );
        robot->_id = KFGlobal::Instance()->STMakeUuid();
        robot->_version = _version;
        robot->_battle_server_id = _battle_server_id;
        robot->_pb_player.set_id( robot->_id );
        robot->_pb_player.set_grade( _grade );
        robot->_pb_player.set_isrobot( true );

        // 英雄id
        robot->_pb_player.set_heroid( RandRobotHeroId() );
        // 机器人名字
        robot->_pb_player.set_name( RandRobotName() );
        return robot;
    }

    void KFMatchRoom::SendToRoom( uint32 msg_id, google::protobuf::Message* message )
    {
        for ( auto& iter : _player_list._objects )
        {
            auto match_player = iter.second;
            if ( !match_player->_pb_player.isrobot() )
            {
                _kf_route->SendToEntity( match_player->_pb_player.serverid(), match_player->_id, msg_id, message );
            }
        }
    }

    uint32 KFMatchRoom::RandRobotHeroId()
    {
        auto size = KFHeroConfig::Instance()->_setting_list.Size();
        if ( size == 0u )
        {
            return _invalid_int;
        }

        auto index = KFGlobal::Instance()->RandRatio( size );
        auto begin = KFHeroConfig::Instance()->_setting_list._objects.begin();
        std::advance( begin, index );
        return ( uint32 )begin->second->_id;
    }

    // 随机名字
    const std::string& KFMatchRoom::RandRobotName()
    {
        static std::string _name = "";
        _name.clear();

        for ( auto iter : KFNameConfig::Instance()->_setting_list._objects )
        {
            auto setting = iter.second;
            if ( setting->_name.empty() )
            {
                continue;
            }

            auto index = KFGlobal::Instance()->RandRatio( ( uint32 )setting->_name.size() );
            _name += setting->_name[ index ];
        }

        return _name;
    }


    void KFMatchRoom::SendJoinRoomToPlayer( uint64 player_id, uint64 server_id )
    {
        KFMsg::S2SJoinMatchToGameAck ack;
        SaveTo( ack.mutable_pbroom(), true );
        auto ok = _kf_route->SendToEntity( server_id, player_id, KFMsg::S2S_JOIN_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] send join match ack failed!", player_id );
        }
    }

    // 加入玩家
    uint32 KFMatchRoom::JoinPlayer( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, const std::string& password )
    {
        return KFMsg::MatchRoomIdError;
    }

    uint32 KFMatchRoom::KickPlayer( uint64 master_id, uint64 player_id )
    {
        return KFMsg::MatchRoomKickTypeError;
    }

    void KFMatchRoom::SendLeaveToRoom( uint64 player_id, uint32 type )
    {
        KFMsg::MsgLeaveMatchAck ack;
        ack.set_playerid( player_id );
        ack.set_type( type );
        SendToRoom( KFMsg::MSG_LEAVE_MATCH_ACK, &ack );
    }

    uint32 KFMatchRoom::FightMatch( uint64 player_id )
    {
        return KFMsg::MatchRoomKickTypeError;
    }

    uint32 KFMatchRoom::PrepareMatch( uint64 player_id, bool prepare )
    {
        return KFMsg::MatchRoomPrepareTypeError;
    }

    uint32 KFMatchRoom::InviteMatch( uint64 invite_id, uint64 player_id, uint64 server_id )
    {
        return KFMsg::MatchInviteTypeError;
    }
}