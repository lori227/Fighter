#include "KFMatchRoom.h"
#include "KFMatchQueue.h"
#include "KFZConfig/KFNameConfig.hpp"
#include "KFZConfig/KFHeroConfig.hpp"
#include "KFZConfig/KFMatchConfig.hpp"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    void KFMatchRoom::InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid )
    {
        _grade = grade;
        _version = version;
        _match_queue = kfqueue;
        _battle_server_id = battleserverid;
        _id = KFGlobal::Instance()->STMakeUUID();

        _state = MatchState;
        _next_add_robot_time = KFGlobal::Instance()->_game_time + _match_queue->_match_setting->_add_robot_time;
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
        __LOG_DEBUG__( "room=[{}] add player=[{}] count=[{}]!", _id, kfplayer->_id, _player_list.Size() );

        SentMatchCountToClient();
        return CheckFull();
    }

    bool KFMatchRoom::CheckFull()
    {
        auto ok = ( _player_list.Size() >= _match_queue->_match_setting->_max_count );
        if ( ok )
        {
            ChangeState( CreateState, 1 );
        }

        return ok;
    }

    bool KFMatchRoom::IsValid()
    {
        return _state != DestroyState;
    }

    bool KFMatchRoom::Run()
    {
        if ( _timer.DoneTimer() )
        {
            switch ( _state )
            {
            case CreateState:
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
        ChangeState( CreateState, 5000 );

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

        _kf_route->SendToBalance( __STRING__( room ), KFMsg::S2S_CREATE_ROOM_TO_ROOM_REQ, &req, false );
    }

    void KFMatchRoom::AffirmCreate()
    {
        ChangeState( DestroyState, 100 );
    }

    void KFMatchRoom::CancelMatch( KFMatchPlayer* kfplayer )
    {
        if ( _state != MatchState )
        {
            return;
        }

        // 删除玩家
        _player_list.Remove( kfplayer->_id );

        // 判断是否全是机器人
        for ( auto iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( !kfplayer->_pb_player.isrobot() )
            {
                return;
            }
        }

        // 如果没有真是玩家, 房间销毁
        _match_queue->RemoveRoom( this );
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

        // 上限积分差距
        if ( kfplayer->_pb_player.grade() > _grade + _match_queue->_match_setting->_upper_grade )
        {
            return false;
        }

        // 下限积分差距
        if ( kfplayer->_pb_player.grade() + _match_queue->_match_setting->_lower_grade < _grade )
        {
            return false;
        }

        return true;
    }

    bool KFMatchRoom::AddRobot()
    {
        if ( _next_add_robot_time > KFGlobal::Instance()->_game_time )
        {
            return false;
        }

        _next_add_robot_time = KFGlobal::Instance()->_game_time + _match_queue->_match_setting->_add_robot_time;
        auto addcount = __MIN__( _match_queue->_match_setting->_add_robot_count, _match_queue->_match_setting->_max_count - _player_list.Size() );

        do
        {
            auto kfrobot = CreateMatchRobot();
            _player_list.Insert( kfrobot->_id, kfrobot );
            __LOG_DEBUG__( "room=[{}] add robot=[{}] count=[{}]!", _id, kfrobot->_id, _player_list.Size() );

        } while ( ( --addcount ) > 0 );
        SentMatchCountToClient();

        return CheckFull();
    }

    KFMatchPlayer* KFMatchRoom::CreateMatchRobot()
    {
        auto kfrobot = __KF_NEW__( KFMatchPlayer );
        kfrobot->_id = KFGlobal::Instance()->STMakeUUID();
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

    void KFMatchRoom::SentMatchCountToClient()
    {
        KFMsg::MsgTellMatchCount tell;
        tell.set_count( _player_list.Size() );
        SendToRoom( KFMsg::MSG_TELL_MATCH_COUNT, &tell );
    }

    void KFMatchRoom::SendToRoom( uint32 msgid, google::protobuf::Message* message )
    {
        for ( auto& iter : _player_list._objects )
        {
            auto kfplayer = iter.second;
            if ( !kfplayer->_pb_player.isrobot() )
            {
                _kf_route->SendToPlayer( kfplayer->_pb_player.serverid(), kfplayer->_id, msgid, message, false );
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
}