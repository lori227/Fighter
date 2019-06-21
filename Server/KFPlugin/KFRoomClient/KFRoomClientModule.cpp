﻿#include "KFRoomClientModule.hpp"

namespace KFrame
{
    void KFRoomClientModule::BeforeRun()
    {
        __REGISTER_MESSAGE__( KFMsg::S2S_INFORM_BATTLE_TO_GAME_REQ, &KFRoomClientModule::HandleInformBattleToGameReq );
        __REGISTER_MESSAGE__( KFMsg::MSG_INFORM_BATTLE_ACK, &KFRoomClientModule::HandleInformBattleAck );
        __REGISTER_MESSAGE__( KFMsg::S2S_QUERY_ROOM_TO_GAME_ACK, &KFRoomClientModule::HandleQueryRoomToGameAck );
        __REGISTER_MESSAGE__( KFMsg::S2S_FINISH_ROOM_TO_GAME_REQ, &KFRoomClientModule::HandleFinishRoomToGameReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_PLAYER_BALANCE_TO_GAME_REQ, &KFRoomClientModule::HandleBalanceToGameReq );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        _kf_player->RegisterEnterFunction( this, &KFRoomClientModule::OnEnterQueryRoom );
    }

    void KFRoomClientModule::BeforeShut()
    {
        __UNREGISTER_MESSAGE__( KFMsg::S2S_INFORM_BATTLE_TO_GAME_REQ );
        __UNREGISTER_MESSAGE__( KFMsg::MSG_INFORM_BATTLE_ACK );
        __UNREGISTER_MESSAGE__( KFMsg::S2S_QUERY_ROOM_TO_GAME_ACK );
        __UNREGISTER_MESSAGE__( KFMsg::S2S_FINISH_ROOM_TO_GAME_REQ );
        __UNREGISTER_MESSAGE__( KFMsg::S2S_PLAYER_BALANCE_TO_GAME_REQ );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        _kf_player->UnRegisterEnterFunction( this );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleInformBattleToGameReq )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SInformBattleToGameReq );

        __LOG_DEBUG__( "player=[{}] room=[{}] battle=[{}|{}:{}]", kfmsg.playerid(), kfmsg.roomid(), kfmsg.battleid(), kfmsg.ip(), kfmsg.port() );

        SetRoomData( player, kfmsg.roomid(), __ROUTE_SERVER_ID__ );

        // 通知客户端
        KFMsg::MsgInformBattleReq req;
        req.set_roomid( kfmsg.roomid() );
        req.set_battleid( kfmsg.battleid() );
        req.set_ip( kfmsg.ip() );
        req.set_port( kfmsg.port() );
        _kf_player->SendToClient( player, KFMsg::MSG_INFORM_BATTLE_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleInformBattleAck )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgInformBattleAck );

        __LOG_DEBUG__( "player=[{}] affirm battle!", playerid );

        auto kfobject = player->GetData();
        auto roomid = kfobject->GetValue( __KF_STRING__( roomid ) );
        auto roomserverid = kfobject->GetValue( __KF_STRING__( roomserverid ) );
        if ( roomserverid == _invalid_int || roomid == _invalid_int )
        {
            return __LOG_ERROR__( "player=[{}] affirm battle failed!", playerid );
        }

        KFMsg::S2SInformBattleToRoomAck ack;
        ack.set_playerid( playerid );
        ack.set_roomid( roomid );
        _kf_route->SendToServer( roomserverid, KFMsg::S2S_INFORM_BATTLE_TO_ROOM_ACK, &ack, false );
    }

    void KFRoomClientModule::OnEnterQueryRoom( KFEntity* player )
    {
        // 查询结算数据
        {
            KFMsg::S2SQueryBalanceToRoomReq req;
            req.set_playerid( player->GetKeyID() );
            _kf_route->SendToRand( __KF_STRING__( room ), KFMsg::S2S_QUERY_BALANCE_TO_ROOM_REQ, &req, true );
        }

        auto kfobject = player->GetData();
        auto roomid = kfobject->GetValue( __KF_STRING__( roomid ) );
        if ( roomid == _invalid_int )
        {
            return;
        }

        auto roomserverid = kfobject->GetValue( __KF_STRING__( roomserverid ) );

        KFMsg::S2SQueryRoomToRoomReq req;
        req.set_roomid( roomid );
        req.set_playerid( player->GetKeyID() );
        _kf_route->SendToServer( roomserverid, KFMsg::S2S_QUERY_ROOM_TO_ROOM_REQ, &req, true );
    }

    void KFRoomClientModule::SetRoomData( KFEntity* player, uint64 roomid, uint64 roomserverid )
    {
        player->UpdateData( __KF_STRING__( roomid ), KFEnum::Set, roomid );
        player->UpdateData( __KF_STRING__( roomserverid ), KFEnum::Set, roomserverid );

        if ( roomid == _invalid_int )
        {
            player->UpdateData( __KF_STRING__( matchid ), KFEnum::Set, _invalid_int );
            player->UpdateData( __KF_STRING__( matchserverid ), KFEnum::Set, _invalid_int );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleQueryRoomToGameAck )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SQueryRoomToGameAck );

        SetRoomData( player, _invalid_int, _invalid_int );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleFinishRoomToGameReq )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SFinishRoomToGameReq );

        __LOG_DEBUG__( "player=[{}] room=[{}] finish!", kfmsg.playerid(), kfmsg.roomid() );

        auto kfobject = player->GetData();
        auto roomid = kfobject->GetValue( __KF_STRING__( roomid ) );
        if ( roomid != kfmsg.roomid() )
        {
            return;
        }

        SetRoomData( player, _invalid_int, _invalid_int );

        KFMsg::MsgFinishRoomReq req;
        req.set_roomid( kfmsg.roomid() );
        _kf_player->SendToClient( player, KFMsg::MSG_FINISH_ROOM_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleBalanceToGameReq )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SPlayerBalanceToGameReq );
        __LOG_DEBUG__( "player=[{}] room=[{}] balance!", kfmsg.playerid(), kfmsg.roomid() );

        // 开始结算
        auto pbbalance = &kfmsg.balance();

        // 排名ranking

        // 结算奖励
        auto kfobject = player->GetData();
        for ( auto i = 0; i < pbbalance->data_size(); ++i )
        {
            auto pbdata = &pbbalance->data( i );
            auto kfdata = kfobject->FindData( pbdata->name() );
            if ( kfdata == nullptr )
            {
                kfdata = kfobject->FindData( __KF_STRING__( basic ), pbdata->name() );
                if ( kfdata == nullptr )
                {
                    continue;
                }
            }

            if ( pbdata->value() > 0 )
            {
                player->UpdateData( kfdata, KFEnum::Add, ( uint32 )pbdata->value() );
            }
            else
            {
                player->UpdateData( kfdata, KFEnum::Dec, ( uint32 )abs( pbdata->value() ) );
            }
        }

        // 返回结果
        KFMsg::S2SPlayerBalanceToRoomResult result;
        result.set_roomid( kfmsg.roomid() );
        result.set_playerid( kfmsg.playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_RESULT, &result );
    }
}