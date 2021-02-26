#include "KFMatchShardModule.hpp"

namespace KFrame
{
    void KFMatchShardModule::BeforeRun()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_START_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleStartMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleCancelMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK, &KFMatchShardModule::HandleCreateRoomToMatchAck );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ, &KFMatchShardModule::HandleQueryMatchToMatchReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleCreateMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_JOIN_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleJoinMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_QUERY_MATCH_LIST_TO_SHARD_REQ, &KFMatchShardModule::HandleQueryMatchListToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_KICK_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleKickMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_FIGHT_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleFightMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_PREPARE_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandlePrepareMatchToShardReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Normal, KFMsg::S2S_INVITE_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleInviteMatchToShardReq );
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
        UInt64Set match_list;
        for ( auto iter : KFMatchConfig::Instance()->_setting_list._objects )
        {
            auto setting = iter.second;
            match_list.insert( setting->_id );
        }
        _kf_route->SyncObject( match_list );
    }

    void KFMatchShardModule::Run()
    {
        // 匹配逻辑
        for ( auto& iter : _match_queue_list._objects )
        {
            iter.second->RunMatch();
        }

        // 房间逻辑
        {
            UInt64Set remove_list;
            for ( auto& iter : _match_room_list._objects )
            {
                auto ok = iter.second->Run();
                if ( !ok )
                {
                    remove_list.insert( iter.first );
                }
            }

            for ( auto id : remove_list )
            {
                _match_room_list.Remove( id );
            }
        }
    }

    void KFMatchShardModule::AddRoom( std::shared_ptr<KFMatchRoom> room )
    {
        _match_room_list.Insert( room->_id, room );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    std::shared_ptr<KFMatchQueue> KFMatchShardModule::FindMatchQueue( uint32 match_id )
    {
        auto setting = KFMatchConfig::Instance()->FindSetting( match_id );
        if ( setting == nullptr )
        {
            __LOG_ERROR__( "can't find match=[{}] setting!", match_id );
            return nullptr;
        }

        auto match_queue = _match_queue_list.Find( match_id );
        if ( match_queue == nullptr )
        {
            match_queue = _match_queue_list.Create( match_id );
            match_queue->_match_module = this;
            match_queue->_match_setting = setting;
        }

        return match_queue;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleStartMatchToShardReq, KFMsg::S2SStartMatchToShardReq )
    {
        auto pb_player = &kfmsg->pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] grade=[{}] version=[{}] server=[{}] req!",
                       pb_player->id(), kfmsg->matchid(), pb_player->grade(), kfmsg->version(), KFAppId::ToString( kfmsg->serverid() ) );

        // 先判断是否在匹配中
        auto match_player = _match_player_manage->Find( pb_player->id() );
        if ( match_player != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto match_queue = FindMatchQueue( kfmsg->matchid() );
        if ( match_queue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 处理匹配
        match_queue->StartMatch( pb_player, kfmsg->version(), kfmsg->serverid() );

        // 发送给玩家
        KFMsg::S2SStartMatchToGameAck ack;
        ack.set_matchid( kfmsg->matchid() );
        ack.set_playerid( pb_player->id() );
        ack.set_serverid( KFGlobal::Instance()->_app_id->GetId() );
        auto ok = _kf_route->SendToRoute( route, KFMsg::S2S_START_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] send match ack failed!", pb_player->id() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateMatchToShardReq, KFMsg::S2SCreateMatchToShardReq )
    {
        auto pb_player = &kfmsg->pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] version=[{}] server=[{}] req!",
                       pb_player->id(), kfmsg->matchid(), kfmsg->version(), KFAppId::ToString( kfmsg->serverid() ) );

        // 先判断是否在匹配中
        auto match_player = _match_player_manage->Find( pb_player->id() );
        if ( match_player != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto match_queue = FindMatchQueue( kfmsg->matchid() );
        if ( match_queue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 创建匹配
        match_queue->CreateMatch( pb_player, kfmsg->version(), kfmsg->serverid(), kfmsg->title(), kfmsg->password(), kfmsg->addrobot() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCancelMatchToShardReq, KFMsg::S2SCancelMatchToShardReq )
    {
        __LOG_DEBUG__( "player=[{}] cancel match req!", kfmsg->playerid() );

        auto match_player = _match_player_manage->Find( kfmsg->playerid() );
        if ( match_player == nullptr )
        {
            return __LOG_ERROR__( "player=[{}] not in match!", kfmsg->playerid() );
        }

        if ( match_player->_match_room != nullptr )
        {
            match_player->_match_room->CancelMatch( kfmsg->playerid() );
        }
        else
        {
            // 删除玩家
            auto match_queue = FindMatchQueue( kfmsg->matchid() );
            if ( match_queue != nullptr )
            {
                match_queue->CancelMatch( match_player->_id );
            }
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateRoomToMatchAck, KFMsg::S2SCreateRoomToMatchAck )
    {
        __LOG_DEBUG__( "room=[{}] create ack!", kfmsg->roomid() );

        auto room = _match_room_list.Find( kfmsg->roomid() );
        if ( room == nullptr )
        {
            return __LOG_ERROR__( "can't find room=[{}]!", kfmsg->roomid() );
        }

        room->AffirmCreate();
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleQueryMatchToMatchReq, KFMsg::S2SQueryMatchToMatchReq )
    {
        __LOG_DEBUG__( "player=[{}] query match req!", kfmsg->playerid() );
        auto match_player = _match_player_manage->Find( kfmsg->playerid() );
        if ( match_player != nullptr )
        {
            match_player->_pb_player.set_serverid( __ROUTE_SERVER_ID__ );
            return __LOG_DEBUG__( "player=[{}] query in match!", kfmsg->playerid() );
        }

        KFMsg::S2SQueryMatchToGameAck ack;
        ack.set_playerid( kfmsg->playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleJoinMatchToShardReq, KFMsg::S2SJoinMatchToShardReq )
    {
        auto pb_player = &kfmsg->pbplayer();
        auto match_queue = FindMatchQueue( kfmsg->matchid() );
        if ( match_queue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 创建匹配
        auto result = match_queue->JoinMatch( pb_player, kfmsg->roomid(), kfmsg->version(), kfmsg->password() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleQueryMatchListToShardReq, KFMsg::S2SQueryMatchListToShardReq )
    {
        auto match_queue = FindMatchQueue( kfmsg->matchid() );
        if ( match_queue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 查询匹配列表
        match_queue->QueryMatch( __ROUTE_SEND_ID__, __ROUTE_SERVER_ID__, kfmsg->roomid(), kfmsg->version() );
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleKickMatchToShardReq, KFMsg::S2SKickMatchToShardReq )
    {
        // 先判断是否在匹配中
        auto match_player = _match_player_manage->Find( __ROUTE_SEND_ID__ );
        if ( match_player == nullptr || match_player->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = match_player->_match_room->KickPlayer( match_player->_id, kfmsg->playerid() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleFightMatchToShardReq, KFMsg::S2SFightMatchToShardReq )
    {
        auto match_player = _match_player_manage->Find( kfmsg->playerid() );
        if ( match_player == nullptr || match_player->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = match_player->_match_room->FightMatch( match_player->_id );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandlePrepareMatchToShardReq, KFMsg::S2SPrepareMatchToShardReq )
    {
        auto match_player = _match_player_manage->Find( kfmsg->playerid() );
        if ( match_player == nullptr || match_player->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = match_player->_match_room->PrepareMatch( match_player->_id, kfmsg->prepare() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleInviteMatchToShardReq, KFMsg::S2SInviteMatchToShardReq )
    {
        auto match_player = _match_player_manage->Find( kfmsg->playerid() );
        if ( match_player == nullptr || match_player->_match_room == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchNotInMatch );
        }

        auto result = match_player->_match_room->InviteMatch( kfmsg->playerid(), kfmsg->targetid(), kfmsg->serverid() );
        if ( result != KFMsg::Ok )
        {
            _kf_display->SendToPlayer( route, result );
        }
    }
}