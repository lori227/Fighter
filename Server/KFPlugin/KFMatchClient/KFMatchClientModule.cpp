#include "KFMatchClientModule.hpp"

namespace KFrame
{
    void KFMatchClientModule::BeforeRun()
    {
        __REGISTER_PLAYER_ENTER__( &KFMatchClientModule::OnEnterQueryMatch );
        __REGISTER_PLAYER_LEAVE__( &KFMatchClientModule::OnLeaveCancelMatch );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_START_MATCH_REQ, &KFMatchClientModule::HandleStartMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_START_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleStartMatchToGameAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_CANCEL_MATCH_REQ, &KFMatchClientModule::HandleCancelMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleQueryMatchToGameAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_CREATE_MATCH_REQ, &KFMatchClientModule::HandleCreateMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_JOIN_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleJoinMatchToGameAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_JOIN_MATCH_REQ, &KFMatchClientModule::HandleJoinMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_QUERY_MATCH_LIST_REQ, &KFMatchClientModule::HandleQueryMatchListReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_KICK_MATCH_REQ, &KFMatchClientModule::HandleKickMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::S2S_KICK_MATCH_TO_GAME_ACK, &KFMatchClientModule::HandleKickMatchToGameAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_FIGHT_MATCH_REQ, &KFMatchClientModule::HandleFightMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_PREPARE_MATCH_REQ, &KFMatchClientModule::HandlePrepareMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_INVITE_MATCH_REQ, &KFMatchClientModule::HandleInviteMatchReq );
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
        auto match_id = player->Get( __STRING__( matchid ) );
        if ( match_id == _invalid_int )
        {
            return;
        }

        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            return;
        }

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SQueryMatchToMatchReq req;
        req.set_matchid( match_id );
        req.set_playerid( player->GetKeyID() );
        _kf_route->RepeatToServer( match_server_id, KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ, &req );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleQueryMatchToGameAck, KFMsg::S2SQueryMatchToGameAck )
    {
        SetMatchData( player, _invalid_int, _invalid_int );
        __LOG_DEBUG__( "player=[{}] query no match", player->GetKeyID() );
    }

    __KF_PLAYER_LEAVE_FUNCTION__( KFMatchClientModule::OnLeaveCancelMatch )
    {
        auto match_id = player->Get( __STRING__( matchid ) );
        if ( match_id == _invalid_int )
        {
            return;
        }

        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            return;
        }

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SCancelMatchToShardReq req;
        req.set_matchid( match_id );
        req.set_playerid( player->GetKeyID() );
        _kf_route->RepeatToServer( match_server_id, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &req );

        player->Operate( __STRING__( matchid ), KFEnum::Set, _invalid_int );
        player->Operate( __STRING__( matchserverid ), KFEnum::Set, _invalid_int );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMatchClientModule::CheckCanMatch( EntityPtr player, uint32 match_id )
    {
        // 正在房间中
        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchInRoom );
            return false;
        }

        // 是否正在匹配中
        auto wait_match_id = player->Get( __STRING__( matchid ) );
        if ( wait_match_id != _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchAlreadyWait );
            return false;
        }

        // 出战英雄
        auto hero_id = player->Get< uint32 >( __STRING__( heroid ) );
        if ( hero_id == _invalid_int )
        {
            _kf_display->SendToClient( player, KFMsg::MatchNotFighterHero );
            return false;
        }

        return true;
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleStartMatchReq, KFMsg::MsgStartMatchReq )
    {
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

    void KFMatchClientModule::FormatMatchPlayerData( EntityPtr player, KFMsg::PBMatchPlayer* match_player )
    {
        auto basic_data = player->Find( __STRING__( basic ) );

        match_player->set_id( player->GetKeyID() );
        match_player->set_name( basic_data->Get< std::string >( __STRING__( name ) ) );
        match_player->set_serverid( KFGlobal::Instance()->_app_id->GetId() );

        match_player->set_isrobot( false );
        match_player->set_grade( basic_data->Get<uint32>( __STRING__( grade ) ) );
        match_player->set_heroid( player->Get<uint32>( __STRING__( heroid ) ) );
        match_player->set_footid( player->Get<uint32>( __STRING__( footid ) ) );
        match_player->set_effectid( player->Get<uint32>( __STRING__( effectid ) ) );
    }

    void KFMatchClientModule::SetMatchData( EntityPtr player, uint32 match_id, uint64 server_id )
    {
        player->UpdateData( __STRING__( matchid ), KFEnum::Set, match_id );
        player->UpdateData( __STRING__( matchserverid ), KFEnum::Set, server_id );

        if ( match_id != 0u )
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
        _kf_display->SendToClient( player, KFMsg::MatchRequestOk );
        SetMatchData( player, kfmsg->matchid(), kfmsg->serverid() );
        __LOG_DEBUG__( "player=[{}] match=[{}|{}] ok!", kfmsg->playerid(), kfmsg->matchid(), KFAppId::ToString( kfmsg->serverid() ) );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleCancelMatchReq, KFMsg::MsgCancelMatchReq )
    {
        auto match_id = player->Get< uint32 >( __STRING__( matchid ) );
        if ( match_id == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SCancelMatchToShardReq req;
        req.set_matchid( match_id );
        req.set_playerid( player->GetKeyID() );
        auto ok = _kf_route->SendToServer( match_server_id, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }

        SetMatchData( player, _invalid_int, _invalid_int );
        _kf_display->SendToClient( player, KFMsg::MatchCancelOk );
        __LOG_DEBUG__( "player=[{}] cancel match req!", player->GetKeyID() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleCreateMatchReq, KFMsg::MsgCreateMatchReq )
    {
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
        auto pb_room = &kfmsg->pbroom();
        SetMatchData( player, pb_room->matchid(), __ROUTE_SERVER_ID__ );

        KFMsg::MsgJoinMatchAck ack;
        ack.mutable_pbroom()->CopyFrom( *pb_room );
        _kf_player->SendToClient( player, KFMsg::MSG_JOIN_MATCH_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleQueryMatchListReq, KFMsg::MsgQueryMatchListReq )
    {
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
        if ( player->GetKeyID() == kfmsg->playerid() )
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

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SKickMatchToShardReq req;
        req.set_matchid( waitmatchid );
        req.set_playerid( kfmsg->playerid() );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), match_server_id, KFMsg::S2S_KICK_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleKickMatchToGameAck, KFMsg::S2SKickMatchToGameAck )
    {
        SetMatchData( player, _invalid_int, _invalid_int );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleFightMatchReq, KFMsg::MsgFightMatchReq )
    {
        // 正在房间中
        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto wait_match_id = player->Get( __STRING__( matchid ) );
        if ( wait_match_id == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SFightMatchToShardReq req;
        req.set_playerid( player->GetKeyID() );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), match_server_id, KFMsg::S2S_FIGHT_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandlePrepareMatchReq, KFMsg::MsgPrePareMatchReq )
    {
        // 正在房间中
        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto wait_match_id = player->Get( __STRING__( matchid ) );
        if ( wait_match_id == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }

        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        KFMsg::S2SPrepareMatchToShardReq req;
        req.set_prepare( kfmsg->prepare() );
        req.set_playerid( player->GetKeyID() );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), match_server_id, KFMsg::S2S_PREPARE_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }

    }
    __KF_MESSAGE_FUNCTION__( KFMatchClientModule::HandleInviteMatchReq, KFMsg::MsgInviteMatchReq )
    {
        // 正在房间中
        auto room_id = player->Get( __STRING__( roomid ) );
        if ( room_id != _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInRoom );
        }

        // 是否正在匹配中
        auto wait_match_id = player->Get( __STRING__( matchid ) );
        if ( wait_match_id == _invalid_int )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchNotInMatch );
        }
        auto match_server_id = player->Get( __STRING__( matchserverid ) );

        // 判断是否是关系
        auto relation_data = player->Find( kfmsg->relationname(), kfmsg->playerid() );
        if ( relation_data == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInviteNotRelation );
        }

        auto server_id = relation_data->Get( __STRING__( basic ), __STRING__( serverid ) );
        if ( server_id == 0u )
        {
            return _kf_display->SendToClient( player, KFMsg::MatchInviteNotOnline );
        }

        KFMsg::S2SInviteMatchToShardReq req;
        req.set_playerid( player->GetKeyID() );
        req.set_targetid( kfmsg->playerid() );
        req.set_serverid( server_id );
        auto ok = _kf_route->SendToServer( player->GetKeyID(), match_server_id, KFMsg::S2S_INVITE_MATCH_TO_SHARD_REQ, &req );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::MatchServerBusy );
        }
    }
}