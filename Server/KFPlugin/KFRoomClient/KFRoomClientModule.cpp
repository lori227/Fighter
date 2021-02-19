#include "KFRoomClientModule.hpp"

namespace KFrame
{
    void KFRoomClientModule::BeforeRun()
    {
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_INFORM_BATTLE_TO_GAME_REQ, &KFRoomClientModule::HandleInformBattleToGameReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_INFORM_BATTLE_ACK, &KFRoomClientModule::HandleInformBattleAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_QUERY_ROOM_TO_GAME_ACK, &KFRoomClientModule::HandleQueryRoomToGameAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_FINISH_ROOM_TO_GAME_REQ, &KFRoomClientModule::HandleFinishRoomToGameReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_PLAYER_BALANCE_TO_GAME_REQ, &KFRoomClientModule::HandleBalanceToGameReq );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_PLAYER_ENTER__( &KFRoomClientModule::OnEnterQueryRoom );
    }

    void KFRoomClientModule::BeforeShut()
    {
        __UN_MESSAGE__( KFMsg::S2S_INFORM_BATTLE_TO_GAME_REQ );
        __UN_MESSAGE__( KFMsg::MSG_INFORM_BATTLE_ACK );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_ROOM_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::S2S_FINISH_ROOM_TO_GAME_REQ );
        __UN_MESSAGE__( KFMsg::S2S_PLAYER_BALANCE_TO_GAME_REQ );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_PLAYER_ENTER__();
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleInformBattleToGameReq, KFMsg::S2SInformBattleToGameReq )
    {
        __LOG_DEBUG__( "player=[{}] room=[{}] battle=[{}|{}:{}]", kfmsg->playerid(), kfmsg->roomid(), kfmsg->battleid(), kfmsg->ip(), kfmsg->port() );

        SetRoomData( kfentity, kfmsg->roomid(), __ROUTE_SERVER_ID__ );

        // 通知客户端
        KFMsg::MsgInformBattleReq req;
        req.set_roomid( kfmsg->roomid() );
        req.set_battleid( kfmsg->battleid() );
        req.set_ip( kfmsg->ip() );
        req.set_port( kfmsg->port() );
        _kf_player->SendToClient( kfentity, KFMsg::MSG_INFORM_BATTLE_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleInformBattleAck, KFMsg::MsgInformBattleAck )
    {
        __LOG_DEBUG__( "player=[{}] affirm battle!", kfentity->GetKeyID() );

        auto roomid = kfentity->Get( __STRING__( roomid ) );
        auto roomserverid = kfentity->Get( __STRING__( roomserverid ) );
        if ( roomserverid == _invalid_int || roomid == _invalid_int )
        {
            return __LOG_ERROR__( "player=[{}] affirm battle failed!", kfentity->GetKeyID() );
        }

        KFMsg::S2SInformBattleToRoomAck ack;
        ack.set_roomid( roomid );
        ack.set_playerid( kfentity->GetKeyID() );
        _kf_route->SendToServer( roomserverid, KFMsg::S2S_INFORM_BATTLE_TO_ROOM_ACK, &ack );

        // 更新下排名信息, 否则如果相同不会回调
        kfentity->UpdateData( __STRING__( ranking ), KFEnum::Set, 0u );
    }

    __KF_PLAYER_ENTER_FUNCTION__( KFRoomClientModule::OnEnterQueryRoom )
    {
        // 查询结算数据
        {
            KFMsg::S2SQueryBalanceToRoomReq req;
            req.set_playerid( player->GetKeyID() );
            _kf_route->RepeatToRand( __STRING__( room ), KFMsg::S2S_QUERY_BALANCE_TO_ROOM_REQ, &req );
        }

        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid == _invalid_int )
        {
            return;
        }

        auto roomserverid = player->Get( __STRING__( roomserverid ) );

        KFMsg::S2SQueryRoomToRoomReq req;
        req.set_roomid( roomid );
        req.set_playerid( player->GetKeyID() );
        _kf_route->RepeatToServer( roomserverid, KFMsg::S2S_QUERY_ROOM_TO_ROOM_REQ, &req );
    }

    void KFRoomClientModule::SetRoomData( KFEntity* player, uint64 roomid, uint64 roomserverid )
    {
        player->UpdateData( __STRING__( roomid ), KFEnum::Set, roomid );
        player->UpdateData( __STRING__( roomserverid ), KFEnum::Set, roomserverid );

        if ( roomid == _invalid_int )
        {
            player->SetStatus( KFMsg::OnlineStatus );

            player->UpdateData( __STRING__( matchid ), KFEnum::Set, _invalid_int );
            player->UpdateData( __STRING__( matchserverid ), KFEnum::Set, _invalid_int );
        }
        else
        {
            player->SetStatus( KFMsg::PlayingStatus );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleQueryRoomToGameAck, KFMsg::S2SQueryRoomToGameAck )
    {
        SetRoomData( kfentity, _invalid_int, _invalid_int );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleFinishRoomToGameReq, KFMsg::S2SFinishRoomToGameReq )
    {
        __LOG_DEBUG__( "player=[{}] room=[{}] finish!", kfmsg->playerid(), kfmsg->roomid() );

        auto roomid = kfentity->Get( __STRING__( roomid ) );
        if ( roomid != kfmsg->roomid() )
        {
            return;
        }

        SetRoomData( kfentity, _invalid_int, _invalid_int );

        KFMsg::MsgFinishRoomReq req;
        req.set_roomid( kfmsg->roomid() );
        _kf_player->SendToClient( kfentity, KFMsg::MSG_FINISH_ROOM_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFRoomClientModule::HandleBalanceToGameReq, KFMsg::S2SPlayerBalanceToGameReq )
    {
        __LOG_DEBUG__( "player=[{}] room=[{}] balance!", kfmsg->playerid(), kfmsg->roomid() );

        auto roomid = kfentity->Get< uint64 >( __STRING__( roomid ) );
        if ( roomid == kfmsg->roomid() )
        {
            SetRoomData( kfentity, _invalid_int, _invalid_int );
        }

        // 开始结算
        auto pbbalance = &kfmsg->balance();

        // 排名ranking
        kfentity->UpdateData( __STRING__( ranking ), KFEnum::Set, pbbalance->ranking() );

        // 结算奖励
        for ( auto i = 0; i < pbbalance->data_size(); ++i )
        {
            auto pbdata = &pbbalance->data( i );
            auto kfdata = kfentity->Find( pbdata->name() );
            if ( kfdata == nullptr )
            {
                kfdata = kfentity->Find( __STRING__( basic ), pbdata->name() );
                if ( kfdata == nullptr )
                {
                    continue;
                }
            }

            if ( pbdata->value() > 0 )
            {
                kfentity->UpdateData( kfdata, KFEnum::Add, ( uint32 )pbdata->value() );
            }
            else
            {
                kfentity->UpdateData( kfdata, KFEnum::Dec, ( uint32 )abs( pbdata->value() ) );
            }
        }

        // 返回结果
        KFMsg::S2SPlayerBalanceToRoomResult result;
        result.set_roomid( kfmsg->roomid() );
        result.set_playerid( kfmsg->playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_PLAYER_BALANCE_TO_ROOM_RESULT, &result );
    }
}