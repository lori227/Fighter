#include "KFMatchQueue.h"
#include "KFMatchShardModule.hpp"

namespace KFrame
{
    //////////////////////////////////////////////////////////////////////////////////
    void KFMatchQueue::RemovePlayer( uint64 player_id )
    {
        _player_list.Remove( player_id );
    }

    void KFMatchQueue::AddPlayer( std::shared_ptr<KFMatchPlayer> match_player )
    {
        match_player->_match_room = nullptr;
        _player_list.Insert( match_player->_id, match_player );
    }

    void KFMatchQueue::RemoveRoom( std::shared_ptr<KFMatchRoom> match_room )
    {
        _room_list.Remove( match_room->_id );
    }
    //////////////////////////////////////////////////////////////////////////////////
    void KFMatchQueue::StartMatch( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, uint64 battle_server_id )
    {
        auto match_player = __MAKE_SHARED__( KFMatchPlayer );
        match_player->_version = version;
        match_player->_battle_server_id = battle_server_id;
        match_player->CopyFrom( pb_player );
        _player_list.Insert( match_player->_id, match_player );
    }

    bool KFMatchQueue::CancelMatch( uint64 player_id )
    {
        RemovePlayer( player_id );
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

    std::shared_ptr<KFMatchRoom> KFMatchQueue::FindMatchRoom( std::shared_ptr<KFMatchPlayer> match_player )
    {
        for ( auto iter : _room_list._objects )
        {
            auto room = iter.second;
            if ( room->IsMatched( match_player ) )
            {
                return room;
            }
        }

        // 创建一个新的房间
        auto room = __MAKE_SHARED__( KFMatchRandRoom );
        room->InitRoom( shared_from_this(), match_player, _invalid_string, _invalid_string, true );
        _room_list.Insert( room->_id, room );
        return room;
    }

    void KFMatchQueue::RoomMatchFinish( std::shared_ptr<KFMatchRoom> match_room )
    {
        _match_module->AddRoom( match_room );
        _room_list.Remove( match_room->_id );
    }

    void KFMatchQueue::RunMatchPlayer()
    {
        for ( auto iter = _player_list._objects.begin(); iter != _player_list._objects.end(); ++iter )
        {
            auto match_player = iter->second;

            auto room = FindMatchRoom( match_player );
            auto ok = room->AddPlayer( match_player );
            if ( ok )
            {
                RoomMatchFinish( room );
            }
        }

        _player_list.Clear();
    }

    void KFMatchQueue::RunMatchRoom()
    {
        std::list<std::shared_ptr<KFMatchRoom>> finish_list;
        for ( auto iter = _room_list._objects.begin(); iter != _room_list._objects.end(); ++iter )
        {
            auto room = iter->second;
            bool ok = room->AddRobot();
            if ( ok )
            {
                finish_list.push_back( room );
            }
        }

        for ( auto room : finish_list )
        {
            RoomMatchFinish( room );
        }
    }

    std::shared_ptr<KFMatchRoom> KFMatchQueue::CreateMatch( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, uint64 battle_server_id,
                                            const std::string& title, const std::string& password, bool add_robot )
    {
        // 添加玩家
        auto match_player = __MAKE_SHARED__( KFMatchPlayer );
        match_player->_version = version;
        match_player->_battle_server_id = battle_server_id;
        match_player->CopyFrom( pb_player );

        // 创建一个新的房间
        auto room = __MAKE_SHARED__( KFMatchJoinRoom );
        room->InitRoom( shared_from_this(), match_player, title, password, add_robot );
        _room_list.Insert( room->_id, room );

        // 通知玩家加入房间
        room->SendJoinRoomToPlayer( pb_player->id(), pb_player->serverid() );
        return room;
    }

    uint32 KFMatchQueue::JoinMatch( const KFMsg::PBMatchPlayer* pb_player, uint64 room_id, const std::string& version, const std::string& password )
    {
        auto room = _room_list.Find( room_id );
        if ( room == nullptr )
        {
            return KFMsg::MatchRoomNotExist;
        }

        return room->JoinPlayer( pb_player, version, password );
    }

    void KFMatchQueue::QueryMatch( uint64 player_id, uint64 server_id, uint64 room_id, const std::string& version )
    {
        KFMsg::MsgQueryMatchListAck ack;
        if ( room_id != 0u )
        {
            auto room = _room_list.Find( room_id );
            if ( room != nullptr )
            {
                room->SaveTo( ack.add_pbroom(), false );
            }
        }
        else
        {
            for ( auto& iter : _room_list._objects )
            {
                auto room = iter.second;
                if ( room->_type == KFMatchEnum::CreateRoom &&
                        room->_version == version )
                {
                    room->SaveTo( ack.add_pbroom(), false );
                }
            }
        }
        _kf_route->SendToEntity( player_id, server_id, player_id, KFMsg::MSG_QUERY_MATCH_LIST_ACK, &ack );
    }
}