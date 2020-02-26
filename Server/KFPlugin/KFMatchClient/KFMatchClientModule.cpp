﻿#include "KFMatchClientModule.hpp"

namespace KFrame
{
    void KFMatchClientModule::BeforeRun()
    {
        __REGISTER_ENTER_PLAYER__( &KFMatchClientModule::OnEnterQueryMatch );
        __REGISTER_LEAVE_PLAYER__( &KFMatchClientModule::OnLeaveCancelMatch );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_START_MATCH_REQ, &KFMatchClientModule::HandleStartMatchReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_START_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleStartMatchToGameAck );
        __REGISTER_MESSAGE__( KFMsg::MSG_CANCEL_MATCH_REQ, &KFMatchClientModule::HandleCancelMatchReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleQueryMatchToGameAck );

    }

    void KFMatchClientModule::BeforeShut()
    {
        __UN_ENTER_PLAYER__();
        __UN_LEAVE_PLAYER__();
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_START_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_START_MATCH_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::MSG_CANCEL_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_ENTER_PLAYER_FUNCTION__( KFMatchClientModule::OnEnterQueryMatch )
    {
        auto matchid = player->Get( __STRING__( matchid ) );
        if ( matchid == _invalid_int )
        {
            return;
        }

        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return;
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SQueryMatchToMatchReq req;
        req.set_matchid( matchid );
        req.set_playerid( player->GetKeyID() );
        _kf_route->RepeatToServer( matchserverid, KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleQueryMatchToGameAck )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SQueryMatchToGameAck );

        SetMatchData( player, _invalid_int, _invalid_int );
        __LOG_DEBUG__( "player=[{}] query no match", player->GetKeyID() );
    }

    __KF_LEAVE_PLAYER_FUNCTION__( KFMatchClientModule::OnLeaveCancelMatch )
    {
        auto matchid = player->Get( __STRING__( matchid ) );
        if ( matchid == _invalid_int )
        {
            return;
        }

        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return;
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SCancelMatchToShardReq req;
        req.set_matchid( matchid );
        req.set_playerid( player->GetKeyID() );
        _kf_route->RepeatToServer( matchserverid, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &req );

        player->Set( __STRING__( matchid ), _invalid_int );
        player->Set( __STRING__( matchserverid ), _invalid_int );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleStartMatchReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgStartMatchReq );

        // 开始匹配
        auto result = ProcessStartMatch( player, kfmsg.version(), kfmsg.matchid(), kfmsg.serverid() );
        if ( result != KFMsg::MatchRequestOk )
        {
            _kf_display->SendToClient( player, result );
        }
    }

    uint32 KFMatchClientModule::ProcessStartMatch( KFEntity* player, const std::string& version, uint32 matchid, uint64 serverid )
    {
        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            __LOG_ERROR__( "player=[{}] already in battle[{}]", player->GetKeyID(), roomid );
            return KFMsg::MatchRequestOk;
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid != _invalid_int )
        {
            __LOG_ERROR__( "player=[{}] already in match[{}] ", player->GetKeyID(), waitmatchid );
            return KFMsg::MatchAlreadyWait;
        }

        // 出战英雄
        auto heroid = player->Get< uint32 >( __STRING__( heroid ) );
        if ( heroid == _invalid_int )
        {
            return KFMsg::MatchNotFighterHero;
        }

        // 发送给匹配集群， 进行匹配
        KFMsg::S2SStartMatchToShardReq req;
        req.set_version( version );
        req.set_matchid( matchid );
        req.set_serverid( serverid );
        FormatMatchPlayerData( player, req.mutable_pbplayer() );
        auto ok = _kf_route->RepeatToObject( __STRING__( match ), matchid, KFMsg::S2S_START_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            return KFMsg::MatchServerBusy;
        }

        return KFMsg::MatchRequestOk;
    }

    void KFMatchClientModule::FormatMatchPlayerData( KFEntity* player, KFMsg::PBMatchPlayer* pbplayer )
    {
        auto kfbasic = player->Find( __STRING__( basic ) );

        pbplayer->set_id( player->GetKeyID() );
        pbplayer->set_name( kfbasic->Get< std::string >( __STRING__( name ) ) );
        pbplayer->set_serverid( KFGlobal::Instance()->_app_id->GetId() );

        pbplayer->set_isrobot( false );
        pbplayer->set_heroid( player->Get<uint32>( __STRING__( heroid ) ) );
        pbplayer->set_grade( kfbasic->Get<uint32>( __STRING__( grade ) ) );
    }

    void KFMatchClientModule::SetMatchData( KFEntity* player, uint32 matchid, uint64 serverid )
    {
        player->UpdateData( __STRING__( matchid ), KFEnum::Set, matchid );
        player->UpdateData( __STRING__( matchserverid ), KFEnum::Set, serverid );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleStartMatchToGameAck )
    {
        __SERVER_PROTO_PARSE__( KFMsg::S2SStartMatchToGameAck );

        if ( kfmsg.result() == KFMsg::MatchRequestOk )
        {
            SetMatchData( player, kfmsg.matchid(), kfmsg.serverid() );
            __LOG_DEBUG__( "player=[{}] match=[{}|{}] ok!", kfmsg.playerid(), kfmsg.matchid(), KFAppId::ToString( kfmsg.serverid() ) );
        }

        _kf_display->SendToClient( player, kfmsg.result() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleCancelMatchReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgCancelMatchReq );

        auto matchid = player->Get< uint32 >( __STRING__( matchid ) );
        if ( matchid == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SCancelMatchToShardReq req;
        req.set_matchid( matchid );
        req.set_playerid( playerid );
        auto ok = _kf_route->SendToServer( matchserverid, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }

        SetMatchData( player, _invalid_int, _invalid_int );
        _kf_display->SendToClient( player, KFMsg::MatchCancelOk );
        __LOG_DEBUG__( "player=[{}] cancel match req!", playerid );
    }
}