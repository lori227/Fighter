#include "KFMatchClientModule.hpp"

namespace KFrame
{
    void KFMatchClientModule::BeforeRun()
    {
        __REGISTER_PLAYER_ENTER__( &KFMatchClientModule::OnEnterQueryMatch );
        __REGISTER_PLAYER_LEAVE__( &KFMatchClientModule::OnLeaveCancelMatch );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMatchClientModule,  KFMsg::MSG_START_MATCH_REQ, KFMsg::MsgStartMatchReq, HandleStartMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::S2S_START_MATCH_TO_GAME_ACK, KFMsg::S2SStartMatchToGameAck, HandleStartMatchToGameAck );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_CANCEL_MATCH_REQ, KFMsg::MsgCancelMatchReq, HandleCancelMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, KFMsg::S2SQueryMatchToGameAck, HandleQueryMatchToGameAck );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_CREATE_MATCH_REQ, KFMsg::MsgCreateMatchReq, HandleCreateMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::S2S_JOIN_MATCH_TO_GAME_ACK, KFMsg::S2SJoinMatchToGameAck, HandleJoinMatchToGameAck );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_JOIN_MATCH_REQ, KFMsg::MsgJoinMatchReq, HandleJoinMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_QUERY_MATCH_LIST_REQ, KFMsg::MsgQueryMatchListReq, HandleQueryMatchListReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_KICK_MATCH_REQ, KFMsg::MsgKickMatchReq, HandleKickMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::S2S_KICK_MATCH_TO_GAME_ACK, KFMsg::S2SKickMatchToGameAck, HandleKickMatchToGameAck );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_FIGHT_MATCH_REQ, KFMsg::MsgFightMatchReq, HandleFightMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_PREPARE_MATCH_REQ, KFMsg::MsgPrePareMatchReq, HandlePrepareMatchReq );
        __REGISTER_MESSAGE__( KFMatchClientModule, KFMsg::MSG_INVITE_MATCH_REQ, KFMsg::MsgInviteMatchReq, HandleInviteMatchReq );
    }

    void KFMatchClientModule::BeforeShut()
    {
        __UN_PLAYER_ENTER__();
        __UN_PLAYER_LEAVE__();
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_START_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_START_MATCH_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::MSG_CANCEL_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::MSG_CREATE_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_JOIN_MATCH_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::MSG_JOIN_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::MSG_QUERY_MATCH_LIST_REQ );
        __UN_MESSAGE__( KFMsg::MSG_KICK_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_KICK_MATCH_TO_GAME_ACK );
        __UN_MESSAGE__( KFMsg::MSG_FIGHT_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::MSG_PREPARE_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::MSG_INVITE_MATCH_REQ );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_PLAYER_ENTER_FUNCTION__( KFMatchClientModule::OnEnterQueryMatch )
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

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleQueryMatchToGameAck, KFMsg::S2SQueryMatchToGameAck )
    {
        __ROUTE_FIND_PLAYER__;

        SetMatchData( player, _invalid_int, _invalid_int );
        __LOG_DEBUG__( "player=[{}] query no match", player->GetKeyID() );
    }

    __KF_PLAYER_LEAVE_FUNCTION__( KFMatchClientModule::OnLeaveCancelMatch )
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
    bool KFMatchClientModule::CheckCanMatch( KFEntity* player, uint32 matchid )
    {
        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchInRoom );
            return false;
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid != _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchAlreadyWait );
            return false;
        }

        // 出战英雄
        auto heroid = player->Get< uint32 >( __STRING__( heroid ) );
        if ( heroid == _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchNotFighterHero );
            return false;
        }

        return true;
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleStartMatchReq, KFMsg::MsgStartMatchReq )
    {
        __ROUTE_FIND_PLAYER__;
        if ( !CheckCanMatch( player, kfmsg->matchid() ) )
        {
            return;
        }

        // 发送给匹配集群， 进行匹配
        KFMsg::S2SStartMatchToShardReq req;
        req.set_version( kfmsg->version() );
        req.set_matchid( kfmsg->matchid() );
        req.set_serverid( kfmsg->serverid() );
        FormatMatchPlayerData( player, req.mutable_pbplayer() );
        auto ok = _kf_route->RepeatToObject( player->GetKeyID(), __STRING__( match ), kfmsg->matchid(), KFMsg::S2S_START_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    void KFMatchClientModule::FormatMatchPlayerData( KFEntity* player, KFMsg::PBMatchPlayer* pbplayer )
    {
        auto kfbasic = player->Find( __STRING__( basic ) );

        pbplayer->set_id( player->GetKeyID() );
        pbplayer->set_name( kfbasic->Get< std::string >( __STRING__( name ) ) );
        pbplayer->set_serverid( KFGlobal::Instance()->_app_id->GetId() );

        pbplayer->set_isrobot( false );
        pbplayer->set_grade( kfbasic->Get<uint32>( __STRING__( grade ) ) );
        pbplayer->set_heroid( player->Get<uint32>( __STRING__( heroid ) ) );
        pbplayer->set_footid( player->Get<uint32>( __STRING__( footid ) ) );
        pbplayer->set_effectid( player->Get<uint32>( __STRING__( effectid ) ) );
    }

    void KFMatchClientModule::SetMatchData( KFEntity* player, uint32 matchid, uint64 serverid )
    {
        player->UpdateData( __STRING__( matchid ), KFEnum::Set, matchid );
        player->UpdateData( __STRING__( matchserverid ), KFEnum::Set, serverid );

        if ( matchid != 0u )
        {
            player->SetStatus( KFMsg::MatchStatus );
        }
        else
        {
            player->SetStatus( KFMsg::OnlineStatus );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleStartMatchToGameAck, KFMsg::S2SStartMatchToGameAck )
    {
        __SERVER_FIND_PLAYER__;

        _kf_display->SendToClient( player, KFMsg::MatchRequestOk );
        SetMatchData( player, kfmsg->matchid(), kfmsg->serverid() );
        __LOG_DEBUG__( "player=[{}] match=[{}|{}] ok!", kfmsg->playerid(), kfmsg->matchid(), KFAppId::ToString( kfmsg->serverid() ) );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleCancelMatchReq, KFMsg::MsgCancelMatchReq )
    {
        __ROUTE_FIND_PLAYER__;

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

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleCreateMatchReq, KFMsg::MsgCreateMatchReq )
    {
        __ROUTE_FIND_PLAYER__;

        if ( !CheckCanMatch( player, kfmsg->matchid() ) )
        {
            return;
        }

        // 发送给匹配集群，创建房间
        KFMsg::S2SCreateMatchToShardReq req;
        req.set_version( kfmsg->version() );
        req.set_matchid( kfmsg->matchid() );
        req.set_serverid( kfmsg->serverid() );
        req.set_title( kfmsg->title() );
        req.set_password( kfmsg->password() );
        req.set_addrobot( kfmsg->addrobot() );
        FormatMatchPlayerData( player, req.mutable_pbplayer() );
        auto ok = _kf_route->SendToObject( player->GetKeyID(), __STRING__( match ), kfmsg->matchid(), KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleJoinMatchReq, KFMsg::MsgJoinMatchReq )
    {
        __ROUTE_FIND_PLAYER__;
        if ( !CheckCanMatch( player, kfmsg->matchid() ) )
        {
            return;
        }

        // 发送给匹配集群， 加入房间
        KFMsg::S2SJoinMatchToShardReq req;
        req.set_version( kfmsg->version() );
        req.set_roomid( kfmsg->roomid() );
        req.set_password( kfmsg->password() );
        req.set_matchid( kfmsg->matchid() );
        FormatMatchPlayerData( player, req.mutable_pbplayer() );
        auto ok = _kf_route->SendToObject( player->GetKeyID(), __STRING__( match ), kfmsg->matchid(), KFMsg::S2S_JOIN_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleJoinMatchToGameAck, KFMsg::S2SJoinMatchToGameAck )
    {
        __ROUTE_FIND_PLAYER__;
        auto pbroom = &kfmsg->pbroom();
        SetMatchData( player, pbroom->matchid(), __ROUTE_SERVER_ID__ );

        KFMsg::MsgJoinMatchAck ack;
        ack.mutable_pbroom()->CopyFrom( *pbroom );
        _kf_player->SendToClient( player, KFMsg::MSG_JOIN_MATCH_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleQueryMatchListReq, KFMsg::MsgQueryMatchListReq )
    {
        __ROUTE_FIND_PLAYER__;

        // 发送给匹配集群，查询房间列表
        KFMsg::S2SQueryMatchListToShardReq req;
        req.set_version( kfmsg->version() );
        req.set_matchid( kfmsg->matchid() );
        req.set_roomid( kfmsg->roomid() );
        auto ok = _kf_route->SendToObject( player->GetKeyID(), __STRING__( match ), kfmsg->matchid(), KFMsg::S2S_QUERY_MATCH_LIST_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleKickMatchReq, KFMsg::MsgKickMatchReq )
    {
        __ROUTE_FIND_PLAYER__;
        if ( playerid == kfmsg->playerid() )
        {
            return;
        }

        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SKickMatchToShardReq req;
        req.set_matchid( waitmatchid );
        req.set_playerid( kfmsg->playerid() );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), matchserverid, KFMsg::S2S_KICK_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleKickMatchToGameAck, KFMsg::S2SKickMatchToGameAck )
    {
        __SERVER_FIND_PLAYER__;
        SetMatchData( player, _invalid_int, _invalid_int );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleFightMatchReq, KFMsg::MsgFightMatchReq )
    {
        __ROUTE_FIND_PLAYER__;

        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SFightMatchToShardReq req;
        req.set_playerid( playerid );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), matchserverid, KFMsg::S2S_FIGHT_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandlePrepareMatchReq, KFMsg::MsgPrePareMatchReq )
    {
        __ROUTE_FIND_PLAYER__;

        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SPrepareMatchToShardReq req;
        req.set_playerid( playerid );
        req.set_prepare( kfmsg->prepare() );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), matchserverid, KFMsg::S2S_PREPARE_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }

    }
    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleInviteMatchReq, KFMsg::MsgInviteMatchReq )
    {
        __ROUTE_FIND_PLAYER__;

        // 正在房间中
        auto roomid = player->Get( __STRING__( roomid ) );
        if ( roomid != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto waitmatchid = player->Get( __STRING__( matchid ) );
        if ( waitmatchid == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }
        auto matchserverid = player->Get( __STRING__( matchserverid ) );

        // 判断是否是关系
        auto kfrelation = player->Find( kfmsg->relationname(), kfmsg->playerid() );
        if ( kfrelation == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInviteNotRelation );
        }

        auto serverid = kfrelation->Get( __STRING__( basic ), __STRING__( serverid ) );
        if ( serverid == 0u )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInviteNotOnline );
        }

        KFMsg::S2SInviteMatchToShardReq req;
        req.set_playerid( playerid );
        req.set_targetid( kfmsg->playerid() );
        req.set_serverid( serverid );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), matchserverid, KFMsg::S2S_INVITE_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }
}