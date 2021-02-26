#include "KFBattleRoom.h"
#include "KFBattleAllot.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    void KFBattleRoom::Init( uint64 room_id )
    {
        _id = room_id;
        ChangeState( AllotState, 1000, __FUNC_LINE__ );
    }

    bool KFBattleRoom::Run()
    {
        if ( _timer.DoneTimer() )
        {
            switch ( _state )
            {
            case AllotState:
                RunAllotBattle();
                break;
            case OpenState:
                RunOpenBattle();
                break;
            case InformState:
                RunInformPlayer();
                break;
            case PlayState:
                break;
            default:
                break;
            }
        }

        // 发送通知消息到玩家
        RunSendInformToPlayer();
        return IsValid();
    }

    bool KFBattleRoom::IsValid()
    {
        // 有效时间过了
        if ( KFGlobal::Instance()->_game_time > _valid_time )
        {
            __LOG_ERROR__( "room=[{}] battle=[{}|{}:{}] valid timeout!", _id, KFAppId::ToString( _allot_id ), _allot_ip, _allot_port );

            SendFinishToPlayer();
            return false;
        }

        if ( _heartbeat_timeout > 0 && KFGlobal::Instance()->_game_time > _heartbeat_timeout )
        {
            __LOG_ERROR__( "room=[{}] battle=[{}|{}:{}] heartbeat timeout!", _id, KFAppId::ToString( _allot_id ), _allot_ip, _allot_port );

            SendFinishToPlayer();
            return false;
        }

        return _state != DestroyState;
    }

    void KFBattleRoom::UpdateHeartBeatTime()
    {
        // 3分钟没收收到消息, 认为战场服务器挂了
        _heartbeat_timeout = KFGlobal::Instance()->_game_time + 180000;
    }

    void KFBattleRoom::ChangeState( uint32 state, uint32 time, const char* function, uint32 line )
    {
        _state = state;
        _timer.StartLoop( time );

        __LOG_DEBUG_FUNCTION__( function, line, "room=[{}] state=[{}] time=[{}]", _id, _state, time );
    }

    void KFBattleRoom::SendToRoom( uint32 msg_id, google::protobuf::Message* message )
    {
        for ( auto& iter : _player_list._objects )
        {
            iter.second->SendToGame( msg_id, message );
        }
    }

    void KFBattleRoom::RunAllotBattle()
    {
        _allot_ip.clear();
        _allot_id = _invalid_int;
        _allot_port = _invalid_int;
        bool is_failed = false;

        std::tie( _allot_id, _allot_ip, _allot_port, is_failed ) = _battle_allot->AllotBattle( _battle_server_id, _version );
        if ( _allot_id == _invalid_int || _allot_ip.empty() || _allot_port == _invalid_int )
        {
            if ( _battle_server_id == _invalid_int )
            {
                ChangeState( AllotState, 5000, __FUNC_LINE__ );

                // 发送消息到房间
                for ( auto& iter : _player_list._objects )
                {
                    auto battle_player = iter.second;
                    if ( !battle_player->_pb_player.isrobot() )
                    {
                        _kf_display->SendToPlayer( battle_player->_pb_player.serverid(), battle_player->_id, KFMsg::RoomAllotBattle );
                    }
                }
            }
            else
            {
                // 指定的直接销毁房间
                ChangeState( DestroyState, 1000, __FUNC_LINE__ );
            }
        }
        else
        {
            _battle_open_count = _invalid_int;
            ChangeState( OpenState, 10, __FUNC_LINE__ );

            __LOG_INFO__( "room=[{}] serverid=[{}] version=[{}] allot=[{}|{}:{}]",
                          _id, KFAppId::ToString( _battle_server_id ), _version, KFAppId::ToString( _allot_id ), _allot_ip, _allot_port );
        }
    }

    void KFBattleRoom::RunOpenBattle()
    {
        if ( _battle_open_count > 10u )
        {
            __LOG_ERROR__( "room=[{}] allot=[{}|{}:{}] open failed!", _id, KFAppId::ToString( _allot_id ), _allot_ip, _allot_port );
            return ChangeState( AllotState, 10, __FUNC_LINE__ );
        }

        ++_battle_open_count;
        ChangeState( OpenState, 5000, __FUNC_LINE__ );

        // 发送消息到战场服务器
        KFMsg::S2SOpenRoomToBattleReq req;
        req.set_roomid( _id );
        req.set_matchid( _match_id );
        req.set_roomserverid( KFGlobal::Instance()->_app_id->GetId() );
        for ( auto& iter : _player_list._objects )
        {
            iter.second->SaveTo( req.add_pbplayer() );
        }
        _kf_route->SendToServer( _allot_id, KFMsg::S2S_OPEN_ROOM_TO_BATTLE_REQ, &req );
    }

    void KFBattleRoom::AffirmOpenBattle( bool ok )
    {
        if ( !ok )
        {
            if ( _battle_server_id == _invalid_int )
            {
                ChangeState( AllotState, 10, __FUNC_LINE__ );
            }
            else
            {
                // 指定的房间 直接销毁掉
                ChangeState( DestroyState, 1000, __FUNC_LINE__ );
            }
        }
        else
        {
            UpdateHeartBeatTime();
            ChangeState( InformState, 10, __FUNC_LINE__ );
        }
    }

    void KFBattleRoom::RunInformPlayer()
    {
        ChangeState( PlayState, 1000, __FUNC_LINE__ );

        // 把玩家添加到通知列表
        for ( auto& iter : _player_list._objects )
        {
            AddInformPlayer( iter.second );
        }
    }

    void KFBattleRoom::AddInformPlayer( std::shared_ptr<KFBattlePlayer> battle_player )
    {
        if ( battle_player->_pb_player.isrobot() )
        {
            return;
        }

        // 发送通知
        SendInformToPlayer( battle_player );

        // 添加进列表
        _inform_list[battle_player] = KFGlobal::Instance()->_game_time + 6000;
    }

    void KFBattleRoom::RunSendInformToPlayer()
    {
        for ( auto& iter : _inform_list )
        {
            if ( KFGlobal::Instance()->_game_time >= iter.second )
            {
                SendInformToPlayer( iter.first );
                iter.second = KFGlobal::Instance()->_game_time + 6000;
            }
        }
    }

    void KFBattleRoom::SendInformToPlayer( std::shared_ptr<KFBattlePlayer> battle_player )
    {
        KFMsg::S2SInformBattleToGameReq req;
        req.set_playerid( battle_player->_id );
        req.set_roomid( _id );
        req.set_battleid( _allot_id );
        req.set_ip( _allot_ip );
        req.set_port( _allot_port );
        battle_player->SendToGame( KFMsg::S2S_INFORM_BATTLE_TO_GAME_REQ, &req );

        __LOG_DEBUG__( "inform player=[{}] battle=[{}|{}:{}]", battle_player->_id, KFAppId::ToString( _allot_id ), _allot_ip, _allot_port );
    }

    void KFBattleRoom::AffirmInformPlayer( uint64 player_id )
    {
        auto battle_player = _player_list.Find( player_id );
        if ( battle_player == nullptr )
        {
            return;
        }

        _inform_list.erase( battle_player );
    }

    bool KFBattleRoom::QueryRoom( uint64 player_id, uint64 server_id )
    {
        auto battle_player = _player_list.Find( player_id );
        if ( battle_player == nullptr )
        {
            return false;
        }

        battle_player->_pb_player.set_serverid( server_id );
        AddInformPlayer( battle_player );
        return true;
    }

    void KFBattleRoom::FinishRoom()
    {
        __LOG_DEBUG__( "room=[{}] battle=[{}] finish!", _id, KFAppId::ToString( _allot_id ) );

        // 通知房间
        ChangeState( DestroyState, 100, __FUNC_LINE__ );

        // 发送结束消息给玩家
        SendFinishToPlayer();
    }

    void KFBattleRoom::SendFinishToPlayer()
    {
        for ( auto& iter : _player_list._objects )
        {
            auto battle_player = iter.second;

            KFMsg::S2SFinishRoomToGameReq req;
            req.set_roomid( _id );
            req.set_playerid( battle_player->_id );
            battle_player->SendToGame( KFMsg::S2S_FINISH_ROOM_TO_GAME_REQ, &req );
        }
    }
}