#include "KFMatchRoom.h"
#include "KFMatchQueue.h"
#include "KFZConfig/KFNameConfig.hpp"
#include "KFZConfig/KFHeroConfig.hpp"

namespace KFrame
{
    void KFMatchRoom::InitRoom( KFMatchQueue* kfqueue, KFMatchPlayer* kfplayer, const std::string& title, const std::string& password )
    {
        _match_queue = kfqueue;
        _state = KFMatchEnum::MatchState;
        _grade = kfplayer->_pb_player.grade();
        _version = kfplayer->_version;
        _battle_server_id = kfplayer->_battle_server_id;
        _id = KFGlobal::Instance()->STMakeUuid();
    }

    void KFMatchRoom::SaveTo( KFMsg::PBMatchRoom* pbroom, bool isplayerlist )
    {
        pbroom->set_matchid( _match_queue->_match_setting->_id );
        pbroom->set_roomid( _id );
        pbroom->set_version( _version );
        pbroom->set_maxplayer( _match_queue->_match_setting->_max_count );
        pbroom->set_nowplayer( _player_list.Size() );
        pbroom->set_grade( _grade );

        if ( isplayerlist )
        {
            for ( auto& iter : _player_list._objects )
            {
                auto player = iter.second;
                player->SaveTo( pbroom->add_pbplayer() );
            }
        }
    }

    void KFMatchRoom::ChangeState( uint32 state, uint32 time )
    {
        _state = state;
        _timer.StartLoop( time );
        __LOG_DEBUG__( "room=[{}] state=[{}] time=[{}]", _id, _state, time );
    }

    bool KFMatchRoom::AddPlayer( KFMatchPlayer* kfplayer )
    {
        kfplayer->_match_room = this;
        _player_list.Insert( kfplayer->_id, kfplayer );
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

    uint32 KFMatchRoom::CancelMatch( uint64 playerid )
    {
        if ( _state != KFMatchEnum::MatchState )
        {
            return KFMatchEnum::CancelFailed;
        }

        // 删除玩家
        _player_list.Remove( playerid );

        // 判断是否全是机器人
        for ( auto iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( !kfplayer->_pb_player.isrobot() )
            {
                return KFMatchEnum::CancelOk;
            }
        }

        // 如果没有真是玩家, 房间销毁
        _match_queue->RemoveRoom( this );
        return KFMatchEnum::CancelDestory;
    }

    bool KFMatchRoom::IsMatched( KFMatchPlayer* kfplayer )
    {
        // 版本号
        if ( kfplayer->_version != _version )
        {
            return false;
        }

        // 服务器id
        if ( kfplayer->_battle_server_id != _battle_server_id )
        {
            return false;
        }

        return true;
    }

    bool KFMatchRoom::AddRobot()
    {
        return false;
    }

    KFMatchPlayer* KFMatchRoom::CreateMatchRobot()
    {
        auto kfrobot = __KF_NEW__( KFMatchPlayer );
        kfrobot->_id = KFGlobal::Instance()->STMakeUuid();
        kfrobot->_version = _version;
        kfrobot->_battle_server_id = _battle_server_id;
        kfrobot->_pb_player.set_id( kfrobot->_id );
        kfrobot->_pb_player.set_grade( _grade );
        kfrobot->_pb_player.set_isrobot( true );

        // 机器人名字
        auto name = KFNameConfig::Instance()->RandName();
        kfrobot->_pb_player.set_name( name );

        // 英雄id
        auto heroid = RandHeroId();
        kfrobot->_pb_player.set_heroid( heroid );
        return kfrobot;
    }

    void KFMatchRoom::SendToRoom( uint32 msgid, google::protobuf::Message* message )
    {
        for ( auto& iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( !kfplayer->_pb_player.isrobot() )
            {
                _kf_route->SendToPlayer( kfplayer->_pb_player.serverid(), kfplayer->_id, msgid, message );
            }
        }
    }

    uint32 KFMatchRoom::RandHeroId()
    {
        auto size = KFHeroConfig::Instance()->_settings.Size();
        if ( size == 0u )
        {
            return _invalid_int;
        }

        auto index = KFGlobal::Instance()->RandRatio( size );
        auto begin = KFHeroConfig::Instance()->_settings._objects.begin();
        std::advance( begin, index );
        return ( uint32 )begin->second->_id;
    }

    void KFMatchRoom::SendJoinRoomToPlayer( uint64 playerid, uint64 serverid )
    {
        KFMsg::S2SJoinMatchToGameAck ack;
        SaveTo( ack.mutable_pbroom(), true );
        auto ok = _kf_route->SendToPlayer( serverid, playerid, KFMsg::S2S_JOIN_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] send join match ack failed!", playerid );
        }
    }

    // 加入玩家
    uint32 KFMatchRoom::JoinPlayer( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, const std::string& password )
    {
        return KFMsg::MatchRoomIdError;
    }

    uint32 KFMatchRoom::KickPlayer( uint64 masterid, uint64 playerid )
    {
        return KFMsg::MatchRoomKickTypeError;
    }

    void KFMatchRoom::SendLeaveToRoom( uint64 playerid, uint32 type )
    {
        KFMsg::MsgLeaveMatchAck ack;
        ack.set_playerid( playerid );
        ack.set_type( type );
        SendToRoom( KFMsg::MSG_LEAVE_MATCH_ACK, &ack );
    }

    uint32 KFMatchRoom::FightMatch( uint64 playerid )
    {
        return KFMsg::MatchRoomKickTypeError;
    }

    uint32 KFMatchRoom::PrepareMatch( uint64 playerid, bool prepare )
    {
        return KFMsg::MatchRoomPrepareTypeError;
    }
}