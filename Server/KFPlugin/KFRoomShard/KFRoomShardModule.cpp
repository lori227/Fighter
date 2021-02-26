#include "KFRoomShardModule.hpp"
#include "KFBattleAllot.h"

namespace KFrame
{
    void KFRoomShardModule::BeforeRun()
    {
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_REGISTER_BATTLE_TO_ROOM_REQ, &KFRoomShardModule::HandleRegisterBattleToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_CREATE_ROOM_TO_ROOM_REQ, &KFRoomShardModule::HandleCreateRoomToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_OPEN_ROOM_TO_ROOM_ACK, &KFRoomShardModule::HandleOpenRoomToRoomAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_INFORM_BATTLE_TO_ROOM_ACK, &KFRoomShardModule:: HandleInformBattleToRoomAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_QUERY_ROOM_TO_ROOM_REQ, &KFRoomShardModule::HandleQueryRoomToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_FINISH_ROOM_TO_ROOM_REQ, &KFRoomShardModule::HandleFinishRoomToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_HEART_BEAT_TO_ROOM_REQ, &KFRoomShardModule::HandleHeartBeatToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_REQ, &KFRoomShardModule::HandlePlayerBalanceToRoomReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_RESULT, &KFRoomShardModule::HandlePlayerBalanceToRoomResult );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_QUERY_BALANCE_TO_ROOM_REQ, &KFRoomShardModule::HandleQueryBalanceToRoomReq );

        //////////////////////////////////////////////////////////////////////////////////////////////////
    }

    void KFRoomShardModule::BeforeShut()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::S2S_REGISTER_BATTLE_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CREATE_ROOM_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_OPEN_ROOM_TO_ROOM_ACK );
        __UN_MESSAGE__( KFMsg::S2S_INFORM_BATTLE_TO_ROOM_ACK );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_ROOM_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_FINISH_ROOM_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_HEART_BEAT_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_REQ );
        __UN_MESSAGE__( KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_RESULT );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_BALANCE_TO_ROOM_REQ );
    }

    void KFRoomShardModule::PrepareRun()
    {
        _redis_driver = _kf_redis->Create( __STRING__( logic ) );
        _battle_allot->Initialize( _redis_driver );
    }

    void KFRoomShardModule::Run()
    {
        UInt64Set remove_list;
        for ( auto& iter : _room_list._objects )
        {
            auto ok = iter.second->Run();
            if ( !ok )
            {
                remove_list.insert( iter.first );
            }
        }

        for ( auto id : remove_list )
        {
            RemoveBattleRoom( id );
        }
    }

    std::shared_ptr<KFBattleRoom> KFRoomShardModule::CreateBattleRoom( uint64 room_id )
    {
        auto room = _room_list.Create( room_id );
        if ( room->_id == _invalid_int )
        {
            // 创建房间
            room->Init( room_id );
        }

        return room;
    }

    void KFRoomShardModule::RemoveBattleRoom( uint64 room_id )
    {
        // 删除房间
        _room_list.Remove( room_id );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleRegisterBattleToRoomReq, KFMsg::S2SRegisterBattleToRoomReq )
    {
        __LOG_INFO__( "register battle[{}|{}|{}:{}]!", KFAppId::ToString( kfmsg->serverid() ), kfmsg->version(), kfmsg->ip(), kfmsg->port() );

        // 注册房间
        auto ok = _battle_allot->AddBattle( kfmsg->serverid(), kfmsg->ip(), kfmsg->port(), kfmsg->version() );

        // 返回结果
        KFMsg::S2SRegisterBattleToBattleAck ack;
        ack.set_result( ok );
        _kf_route->SendToRoute( route, KFMsg::S2S_REGISTER_BATTLE_TO_BATTLE_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleOpenRoomToRoomAck, KFMsg::S2SOpenRoomToRoomAck )
    {
        __LOG_DEBUG__( "open room[{}] result[{}] ack!", kfmsg->roomid(), kfmsg->result() );

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room == nullptr )
        {
            return __LOG_ERROR__( "can't find room[{}]!", kfmsg->roomid() );
        }

        room->AffirmOpenBattle( kfmsg->result() );
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleCreateRoomToRoomReq, KFMsg::S2SCreateRoomToRoomReq )
    {
        __LOG_DEBUG__( "create room[{}|{}|{}] req!", kfmsg->roomid(), kfmsg->version(), KFAppId::ToString( kfmsg->serverid() ) );

        auto room = CreateBattleRoom( kfmsg->roomid() );

        room->_version = kfmsg->version();
        room->_match_id = kfmsg->matchid();
        room->_battle_server_id = kfmsg->serverid();
        room->_valid_time = KFGlobal::Instance()->_game_time + 3600000;
        for ( auto i = 0; i < kfmsg->pbplayer_size(); ++i )
        {
            auto pb_player = &kfmsg->pbplayer( i );

            auto battle_player = __MAKE_SHARED__( KFBattlePlayer );
            battle_player->CopyFrom( pb_player );
            room->_player_list.Insert( battle_player->_id, battle_player );
        }

        // 返回确认信息
        KFMsg::S2SCreateRoomToMatchAck ack;
        ack.set_roomid( kfmsg->roomid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleInformBattleToRoomAck, KFMsg::S2SInformBattleToRoomAck )
    {
        __LOG_DEBUG__( "player=[{}] inform room=[{}] ack!", kfmsg->playerid(), kfmsg->roomid() );

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room == nullptr )
        {
            return __LOG_ERROR__( "can't find room[{}]!", kfmsg->roomid() );
        }

        room->AffirmInformPlayer( kfmsg->playerid() );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleQueryRoomToRoomReq, KFMsg::S2SQueryRoomToRoomReq )
    {
        __LOG_DEBUG__( "player=[{}] query room=[{}] req!", kfmsg->playerid(), kfmsg->roomid() );

        auto ok = false;

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room != nullptr )
        {
            ok = room->QueryRoom( kfmsg->playerid(), __ROUTE_SERVER_ID__ );
        }

        if ( !ok )
        {
            KFMsg::S2SQueryRoomToGameAck ack;
            ack.set_playerid( kfmsg->playerid() );
            _kf_route->SendToRoute( route, KFMsg::S2S_QUERY_ROOM_TO_GAME_ACK, &ack );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleFinishRoomToRoomReq, KFMsg::S2SFinishRoomToRoomReq )
    {
        __LOG_DEBUG__( "room=[{}] finish req!", kfmsg->roomid() );

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room != nullptr )
        {
            room->FinishRoom();
        }

        KFMsg::S2SFinishRoomToBattleAck ack;
        ack.set_roomid( kfmsg->roomid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_FINISH_ROOM_TO_BATTLE_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleHeartBeatToRoomReq, KFMsg::S2SHeartBeatToRoomReq )
    {
        //__LOG_DEBUG__( "server=[{}] room=[{}] heartbeat req!", KFAppId::ToString( kfmsg->serverid() ), kfmsg->roomid() );

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room != nullptr )
        {
            room->UpdateHeartBeatTime();
        }
        else
        {
            _battle_allot->UpdateBattle( kfmsg->serverid() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandlePlayerBalanceToRoomReq, KFMsg::S2SPlayerBalanceToRoomReq )
    {
        __LOG_DEBUG__( "room=[{}] player=[{}] balance req!", kfmsg->roomid(), kfmsg->playerid() );

        auto room = _room_list.Find( kfmsg->roomid() );
        if ( room == nullptr )
        {
            return __LOG_ERROR__( "room=[{}] not exist!", kfmsg->roomid() );
        }

        auto battle_player = room->_player_list.Find( kfmsg->playerid() );
        if ( battle_player == nullptr )
        {
            return __LOG_ERROR__( "player=[{}] not in room!", kfmsg->playerid() );
        }

        if ( !battle_player->_is_balance )
        {
            // 先保存到数据库
            auto pb_balance = &kfmsg->balance();
            auto balance_data = KFProto::Serialize( pb_balance, KFCompressEnum::ZSTD, 5u, true );
            auto result = _redis_driver->HSet( __DATABASE_KEY_2__( __STRING__( balance ), kfmsg->playerid() ), kfmsg->roomid(), balance_data );
            if ( !result->IsOk() )
            {
                return __LOG_ERROR__( "player=[{}] balance save failed!", kfmsg->playerid() );
            }

            // 发送到游戏服务器
            battle_player->_is_balance = true;
            SendPlayerBalanceToGame( battle_player->_pb_player.serverid(), kfmsg->playerid(), kfmsg->roomid(), pb_balance );
        }

        KFMsg::S2SPlayerBalanceToBattleAck ack;
        ack.set_roomid( kfmsg->roomid() );
        ack.set_playerid( kfmsg->playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_PLAYER_BALANCE_TO_BATTLE_ACK, &ack );
    }

    void KFRoomShardModule::SendPlayerBalanceToGame( uint64 server_id, uint64 player_id, uint64 room_id, const KFMsg::PBBattleBalance* pb_balance )
    {
        KFMsg::S2SPlayerBalanceToGameReq req;
        req.set_roomid( roomid );
        req.set_playerid( playerid );
        req.mutable_balance()->CopyFrom( *pbbalance );
        _kf_route->RepeatToEntity( serverid, playerid, KFMsg::S2S_PLAYER_BALANCE_TO_GAME_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandlePlayerBalanceToRoomResult, KFMsg::S2SPlayerBalanceToRoomResult )
    {
        __LOG_DEBUG__( "room=[{}] player=[{}] balance ok!", kfmsg->roomid(), kfmsg->playerid() );

        auto result = _redis_driver->HDel( __DATABASE_KEY_2__( __STRING__( balance ), kfmsg->playerid() ), kfmsg->roomid() );
        if ( !result->IsOk() )
        {
            return __LOG_ERROR__( "player=[{}] balance failed!", kfmsg->playerid() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFRoomShardModule::HandleQueryBalanceToRoomReq, KFMsg::S2SQueryBalanceToRoomReq )
    {
        auto result = _redis_driver->HGetAll( __DATABASE_KEY_2__( __STRING__( balance ), kfmsg->playerid() ) );
        for ( auto& iter : result->_value )
        {
            KFMsg::PBBattleBalance pb_balance;
            KFProto::Parse( &pb_balance, iter.second, KFCompressEnum::ZSTD, true );

            auto room_id = KFUtility::ToValue< uint64 >( iter.first );
            SendPlayerBalanceToGame( __ROUTE_SERVER_ID__, kfmsg->playerid(), room_id, &pb_balance );
        }
    }
}