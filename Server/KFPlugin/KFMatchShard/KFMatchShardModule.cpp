#include "KFMatchShardModule.hpp"

namespace KFrame
{
    void KFMatchShardModule::BeforeRun()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::S2S_START_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleStartMatchToShardReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleCancelMatchToShardReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK, &KFMatchShardModule::HandleCreateRoomToMatchAck );
        __REGISTER_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ, &KFMatchShardModule::HandleQueryMatchToMatchReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ, &KFMatchShardModule::HandleCreateMatchToShardReq );
    }

    void KFMatchShardModule::BeforeShut()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::S2S_START_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CANCEL_MATCH_TO_SHARD_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CREATE_ROOM_TO_MATCH_ACK );
        __UN_MESSAGE__( KFMsg::S2S_QUERY_MATCH_TO_MATCH_REQ );
        __UN_MESSAGE__( KFMsg::S2S_CREATE_MATCH_TO_SHARD_REQ );
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
    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleStartMatchToShardReq )
    {
        __PROTO_PARSE__( KFMsg::S2SStartMatchToShardReq );

        auto pbplayer = &kfmsg.pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] grade=[{}] version=[{}] server=[{}] req!",
                       pbplayer->id(), kfmsg.matchid(), pbplayer->grade(), kfmsg.version(), KFAppId::ToString( kfmsg.serverid() ) );

        // 先判断是否在匹配中
        auto kfplayer = _match_player_manage->Find( pbplayer->id() );
        if ( kfplayer != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto kfqueue = FindMatchQueue( kfmsg.matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 处理匹配
        kfqueue->StartMatch( pbplayer, kfmsg.version(), kfmsg.serverid() );

        // 发送给玩家
        KFMsg::S2SStartMatchToGameAck ack;
        ack.set_matchid( kfmsg.matchid() );
        ack.set_playerid( pbplayer->id() );
        ack.set_serverid( KFGlobal::Instance()->_app_id->GetId() );
        auto ok = _kf_route->SendToRoute( route, KFMsg::S2S_START_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] send match ack failed!", pbplayer->id() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateMatchToShardReq )
    {
        __PROTO_PARSE__( KFMsg::S2SCreateMatchToShardReq );

        auto pbplayer = &kfmsg.pbplayer();
        __LOG_DEBUG__( "player=[{}] match=[{}] version=[{}] server=[{}] req!",
                       pbplayer->id(), kfmsg.matchid(), kfmsg.version(), KFAppId::ToString( kfmsg.serverid() ) );

        // 先判断是否在匹配中
        auto kfplayer = _match_player_manage->Find( pbplayer->id() );
        if ( kfplayer != nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchInRoom );
        }

        // 判断版本

        auto kfqueue = FindMatchQueue( kfmsg.matchid() );
        if ( kfqueue == nullptr )
        {
            return _kf_display->SendToPlayer( route, KFMsg::MatchDataError );
        }

        // 创建匹配
        auto kfroom = kfqueue->CreateMatch( pbplayer, kfmsg.version(), kfmsg.serverid(), kfmsg.title(), kfmsg.password() );

        KFMsg::S2SCreateMatchToGameAck ack;
        kfroom->SaveTo( ack.mutable_pbroom(), true );
        auto ok = _kf_route->SendToRoute( route, KFMsg::S2S_CREATE_MATCH_TO_GAME_ACK, &ack );
        if ( !ok )
        {
            __LOG_ERROR__( "player=[{}] create match ack failed!", pbplayer->id() );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCancelMatchToShardReq )
    {
        __PROTO_PARSE__( KFMsg::S2SCancelMatchToShardReq );

        __LOG_DEBUG__( "player=[{}] cancel match req!", kfmsg.playerid() );

        auto kfplayer = _match_player_manage->Find( kfmsg.playerid() );
        if ( kfplayer == nullptr )
        {
            return __LOG_ERROR__( "player=[{}] not in match!", kfmsg.playerid() );
        }

        if ( kfplayer->_match_room != nullptr )
        {
            kfplayer->_match_room->CancelMatch( kfplayer );
        }
        else
        {
            // 删除玩家
            auto kfqueue = FindMatchQueue( kfmsg.matchid() );
            if ( kfqueue != nullptr )
            {
                kfqueue->CancelMatch( kfplayer->_id );
            }
        }
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleCreateRoomToMatchAck )
    {
        __PROTO_PARSE__( KFMsg::S2SCreateRoomToMatchAck );

        __LOG_DEBUG__( "room=[{}] create ack!", kfmsg.roomid() );

        auto kfroom = _match_room_list.Find( kfmsg.roomid() );
        if ( kfroom == nullptr )
        {
            return __LOG_ERROR__( "can't find room=[{}]!", kfmsg.roomid() );
        }

        kfroom->AffirmCreate();
    }

    __KF_MESSAGE_FUNCTION__( KFMatchShardModule::HandleQueryMatchToMatchReq )
    {
        __PROTO_PARSE__( KFMsg::S2SQueryMatchToMatchReq );

        __LOG_DEBUG__( "player=[{}] query match req!", kfmsg.playerid() );
        auto kfplayer = _match_player_manage->Find( kfmsg.playerid() );
        if ( kfplayer != nullptr )
        {
            kfplayer->_pb_player.set_serverid( __ROUTE_SERVER_ID__ );
            return __LOG_DEBUG__( "player=[{}] query in match!", kfmsg.playerid() );
        }

        KFMsg::S2SQueryMatchToGameAck ack;
        ack.set_playerid( kfmsg.playerid() );
        _kf_route->SendToRoute( route, KFMsg::S2S_QUERY_MATCH_TO_GAME_ACK, &ack );
    }
}