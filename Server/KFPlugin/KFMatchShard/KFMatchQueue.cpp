#include "KFMatchQueue.h"
#include "KFMatchShardModule.hpp"

namespace KFrame
{
    //////////////////////////////////////////////////////////////////////////////////
    void KFMatchQueue::RemovePlayer( uint64 playerid )
    {
        _player_list.Remove( playerid );
    }

    void KFMatchQueue::AddPlayer( KFMatchPlayer* kfplayer )
    {
        kfplayer->_match_room = nullptr;
        _player_list.Insert( kfplayer->_id, kfplayer );
    }

    void KFMatchQueue::RemoveRoom( KFMatchRoom* kfroom )
    {
        _room_list.Remove( kfroom->_id );
    }
    //////////////////////////////////////////////////////////////////////////////////
    void KFMatchQueue::StartMatch( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, uint64 battleserverid )
    {
        auto kfplayer = __KF_NEW__( KFMatchPlayer );
        kfplayer->_version = version;
        kfplayer->_battle_server_id = battleserverid;
        kfplayer->CopyFrom( pbplayer );
        _player_list.Insert( kfplayer->_id, kfplayer );
    }

    bool KFMatchQueue::CancelMatch( uint64 playerid )
    {
        RemovePlayer( playerid );
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////
    void KFMatchQueue::RunMatch()
    {
        // 匹配玩家
        RunMatchPlayer();

        // 匹配房间
        RunMatchRoom();
    }

    KFMatchRoom* KFMatchQueue::FindMatchRoom( KFMatchPlayer* kfplayer )
    {
        for ( auto iter : _room_list._objects )
        {
            auto kfroom = iter.second;
            if ( kfroom->IsMatched( kfplayer ) )
            {
                return kfroom;
            }
        }

        // 创建一个新的房间
        auto kfroom = __KF_NEW__( KFMatchRandRoom );
        kfroom->InitRoom( this, kfplayer, _invalid_string, _invalid_string );
        _room_list.Insert( kfroom->_id, kfroom );
        return kfroom;
    }

    void KFMatchQueue::RoomMatchFinish( KFMatchRoom* kfroom )
    {
        _match_module->AddRoom( kfroom );
        _room_list.Remove( kfroom->_id, false );
    }

    void KFMatchQueue::RunMatchPlayer()
    {
        for ( auto iter = _player_list._objects.begin(); iter != _player_list._objects.end(); ++iter )
        {
            auto kfplayer = iter->second;

            auto kfroom = FindMatchRoom( kfplayer );
            auto ok = kfroom->AddPlayer( kfplayer );
            if ( ok )
            {
                RoomMatchFinish( kfroom );
            }
        }

        _player_list.Clear( false );
    }

    void KFMatchQueue::RunMatchRoom()
    {
        std::list< KFMatchRoom* > finishlist;
        for ( auto iter = _room_list._objects.begin(); iter != _room_list._objects.end(); ++iter )
        {
            auto kfroom = iter->second;
            bool ok = kfroom->AddRobot();
            if ( ok )
            {
                finishlist.push_back( kfroom );
            }
        }

        for ( auto kfroom : finishlist )
        {
            RoomMatchFinish( kfroom );
        }
    }

    KFMatchRoom* KFMatchQueue::CreateMatch( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, uint64 battleserverid, const std::string& title, const std::string& password )
    {
        // 添加玩家
        auto kfplayer = __KF_NEW__( KFMatchPlayer );
        kfplayer->_version = version;
        kfplayer->_battle_server_id = battleserverid;
        kfplayer->CopyFrom( pbplayer );

        // 创建一个新的房间
        auto kfroom = __KF_NEW__( KFMatchJoinRoom );
        kfroom->InitRoom( this, kfplayer, title, password );
        _room_list.Insert( kfroom->_id, kfroom );

        // 通知玩家加入房间
        kfroom->SendJoinRoomToPlayer( pbplayer->id(), pbplayer->serverid() );
        return kfroom;
    }

    uint32 KFMatchQueue::JoinMatch( const KFMsg::PBMatchPlayer* pbplayer, uint64 roomid, const std::string& version, const std::string& password )
    {
        auto kfroom = _room_list.Find( roomid );
        if ( kfroom == nullptr )
        {
            return KFMsg::MatchRoomNotExist;
        }

        return kfroom->JoinPlayer( pbplayer, version, password );
    }

    void KFMatchQueue::QueryMatch( uint64 playerid, uint64 serverid, uint64 roomid, const std::string& version )
    {
        KFMsg::MsgQueryMatchListAck ack;
        if ( roomid != 0u )
        {
            auto kfroom = _room_list.Find( roomid );
            if ( kfroom != nullptr )
            {
                kfroom->SaveTo( ack.add_pbroom(), false );
            }
        }
        else
        {
            for ( auto& iter : _room_list._objects )
            {
                auto kfroom = iter.second;
                if ( kfroom->_type == KFMatchEnum::CreateRoom &&
                        kfroom->_version == version )
                {
                    kfroom->SaveTo( ack.add_pbroom(), false );
                }
            }
        }
        _kf_route->SendToPlayer( playerid, serverid, playerid, KFMsg::MSG_QUERY_MATCH_LIST_ACK, &ack );
    }
}