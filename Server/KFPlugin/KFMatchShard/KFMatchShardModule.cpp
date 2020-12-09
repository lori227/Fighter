#include "KFMatchShardModule.hpp"

namespace KFrame
{
    void KFMatchShardModule::BeforeRun()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_START_MATCH_TO_SHARD_REQ, KFMsg::S2SStartMatchToShardReq, HandleStartMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, KFMsg::S2SCancelMatchToShardReq, HandleCancelMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK, KFMsg::S2SCreateRoomToMatchAck, HandleCreateRoomToMatchAck );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ, KFMsg::S2SQueryMatchToMatchReq, HandleQueryMatchToMatchReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ, KFMsg::S2SCreateMatchToShardReq, HandleCreateMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_JOIN_MATCH_TO_SHARD_REQ, KFMsg::S2SJoinMatchToShardReq, HandleJoinMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_QUERY_MATCH_LIST_TO_SHARD_REQ, KFMsg::S2SQueryMatchListToShardReq, HandleQueryMatchListToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_KICK_MATCH_TO_SHARD_REQ, KFMsg::S2SKickMatchToShardReq, HandleKickMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_FIGHT_MATCH_TO_SHARD_REQ, KFMsg::S2SFightMatchToShardReq, HandleFightMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_PREPARE_MATCH_TO_SHARD_REQ, KFMsg::S2SPrepareMatchToShardReq, HandlePrepareMatchToShardReq );
        __REGISTER_MESSAGE__( KFMatchShardModule, KFMessageEnum::Normal, KFMsg::S2S_INVITE_MATCH_TO_SHARD_REQ, KFMsg::S2SInviteMatchToShardReq, HandleInviteMatchToShardReq );
    }

    void KFMatchShardModule::BeforeShut()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::S2S_START_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_JOIN_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_MATCH_LIST_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_KICK_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_FIGHT_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_PREPARE_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_INVITE_MATCH_TO_SHARD_REQ );
    }

    void KFMatchShardModule::PrepareRun()
    {
        // 添加匹配模式
        RouteObjectList matchlist;
        for ( auto iter : KFMatchConfig::Instance()->_settings._objects )
        {
            auto kfsetting = iter.second;
            matchlist.insert( kfsetting->_id );
        }
        _kf_route->SyncObject( matchlist );
    }

    void KFMatchShardModule::Run()
    {
        // 匹配逻辑
        for ( auto& iter : _match_queue_list._objects )
        {
            auto kfqueue = iter.second;
            kfqueue->RunMatch();
        }

        // 房间逻辑
        {
            std::set< uint64 > _removes;
            for ( auto& iter : _match_room_list._objects )
            {
                auto kfroom = iter.second;
                auto ok = kfroom->Run();
                if ( !ok )
                {
                    _removes.insert( kfroom->_id );
                }
            }

            for ( auto id : _removes )
            {
                _match_room_list.Remove( id );
            }
        }
    }

    void KFMatchShardModule::AddRoom( KFMatchRoom* kfroom )
    {
        _match_room_list.Insert( kfroom->_id, kfroom );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    KFMatchQueue* KFMatchShardModule::FindMatchQueue( uint32 matchid )
    {
        auto kfsetting = KFMatchConfig::Instance()->FindSetting( matchid );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR__( "can't find match=[{}] setting!", matchid );
            return nullptr;
        }

        auto kfqueue = _match_queue_list.Find( matchid );
        if ( kfqueue == nullptr )
        {
            kfqueue = _match_queue_list.Create( matchid );
            kfqueue->_match_setting = kfsetting;
            kfqueue->_match_module = this;
        }

        return kfqueue;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleStartMatchToShardReq, KFMsg::S2SStartMatchToShardReq )
    {
        auto pbplayer = &kfmsg->pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] grade=[{}] version=[{}] server=[{}] req!",
                       pbplayer->id(), kfmsg->matchid(), pbplayer->grade(), kfmsg->version(), KFAppId::ToString( kfmsg->serverid() ) );

        // 先判断是否在匹配中
        auto kfplayer = _match_player_manage->Find( pbplayer->id() );
        if ( kfplayer != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto kfqueue = FindMatchQueue( kfmsg->matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 处理匹配
        kfqueue->StartMatch( pbplayer, kfmsg->version(), kfmsg->serverid() );

        // 发送给玩家
        KFMsg::S2SStartMatchToGameAck ack;
        ack.set_matchid( kfmsg->matchid() );
        ack.set_playerid( pbplayer->id() );
        ack.set_serverid( KFGlobal::Instance()->_app_id->GetId() );
        auto ok = _kf_route->SendToRoute( route, KFMsg::S2S_START_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] send match ack failed!", pbplayer->id() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateMatchToShardReq, KFMsg::S2SCreateMatchToShardReq )
    {
        auto pbplayer = &kfmsg->pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] version=[{}] server=[{}] req!",
                       pbplayer->id(), kfmsg->matchid(), kfmsg->version(), KFAppId::ToString( kfmsg->serverid() ) );

        // 先判断是否在匹配中
        auto kfplayer = _match_player_manage->Find( pbplayer->id() );
        if ( kfplayer != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto kfqueue = FindMatchQueue( kfmsg->matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 创建匹配
        kfqueue->CreateMatch( pbplayer, kfmsg->version(), kfmsg->serverid(), kfmsg->title(), kfmsg->password(), kfmsg->addrobot() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCancelMatchToShardReq, KFMsg::S2SCancelMatchToShardReq )
    {
        __LOG_DEBUG__( "player=[{}] cancel match req!", kfmsg->playerid() );

        auto kfplayer = _match_player_manage->Find( kfmsg->playerid() );
        if ( kfplayer == nullptr )
        {
            return __LOG_ERROR__( "player=[{}] not in match!", kfmsg->playerid() );
        }

        if ( kfplayer->_match_room != nullptr )
        {
            kfplayer->_match_room->CancelMatch( kfmsg->playerid() );
        }
        else
        {
            // 删除玩家
            auto kfqueue = FindMatchQueue( kfmsg->matchid() );
            if ( kfqueue != nullptr )
            {
                kfqueue->CancelMatch( kfplayer->_id );
            }
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateRoomToMatchAck, KFMsg::S2SCreateRoomToMatchAck )
    {
        __LOG_DEBUG__( "room=[{}] create ack!", kfmsg->roomid() );

        auto kfroom = _match_room_list.Find( kfmsg->roomid() );
        if ( kfroom == nullptr )
        {
            return __LOG_ERROR__( "can't find room=[{}]!", kfmsg->roomid() );
        }

        kfroom->AffirmCreate();
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleQueryMatchToMatchReq, KFMsg::S2SQueryMatchToMatchReq )
    {
        __LOG_DEBUG__( "player=[{}] query match req!", kfmsg->playerid() );
        auto kfplayer = _match_player_manage->Find( kfmsg->playerid() );
        if ( kfplayer != nullptr )
        {
            kfplayer->_pb_player.set_serverid( __ROUTE_SERVER_ID__ );
            return __LOG_DEBUG__( "player=[{}] query in match!", kfmsg->playerid() );
        }

        KFMsg::S2SQueryMatchToGameAck ack;
        ack.set_playerid( kfmsg->playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleJoinMatchToShardReq, KFMsg::S2SJoinMatchToShardReq )
    {
        auto pbplayer = &kfmsg->pbplayer();
        auto kfqueue = FindMatchQueue( kfmsg->matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 创建匹配
        auto result = kfqueue->JoinMatch( pbplayer, kfmsg->roomid(), kfmsg->version(), kfmsg->password() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleQueryMatchListToShardReq, KFMsg::S2SQueryMatchListToShardReq )
    {
        auto kfqueue = FindMatchQueue( kfmsg->matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 查询匹配列表
        kfqueue->QueryMatch( __ROUTE_SEND_ID__, __ROUTE_SERVER_ID__, kfmsg->roomid(), kfmsg->version() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleKickMatchToShardReq, KFMsg::S2SKickMatchToShardReq )
    {
        // 先判断是否在匹配中
        auto kfplayer = _match_player_manage->Find( __ROUTE_SEND_ID__ );
        if ( kfplayer == nullptr || kfplayer->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = kfplayer->_match_room->KickPlayer( kfplayer->_id, kfmsg->playerid() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleFightMatchToShardReq, KFMsg::S2SFightMatchToShardReq )
    {
        auto kfplayer = _match_player_manage->Find( kfmsg->playerid() );
        if ( kfplayer == nullptr || kfplayer->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = kfplayer->_match_room->FightMatch( kfplayer->_id );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandlePrepareMatchToShardReq, KFMsg::S2SPrepareMatchToShardReq )
    {
        auto kfplayer = _match_player_manage->Find( kfmsg->playerid() );
        if ( kfplayer == nullptr || kfplayer->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = kfplayer->_match_room->PrepareMatch( kfplayer->_id, kfmsg->prepare() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleInviteMatchToShardReq, KFMsg::S2SInviteMatchToShardReq )
    {
        auto kfplayer = _match_player_manage->Find( kfmsg->playerid() );
        if ( kfplayer == nullptr || kfplayer->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = kfplayer->_match_room->InviteMatch( kfmsg->playerid(), kfmsg->targetid(), kfmsg->serverid() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }
}