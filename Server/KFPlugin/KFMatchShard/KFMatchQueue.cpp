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
        kfroom->InitRoom( this, kfplayer->_pb_player.grade(), kfplayer->_version, kfplayer->_battle_server_id );
        _room_list.Insert( kfroom->_id, kfroom );
        return kfroom;
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
                _match_module->AddRoom( kfroom );
                _room_list.Remove( kfroom->_id, false );
            }
        }

        _player_list.Clear( false );
    }

    void KFMatchQueue::RunMatchRoom()
    {
        for ( auto iter = _room_list._objects.begin(); iter != _room_list._objects.end(); )
        {
            auto kfroom = iter->second;
            bool ok = kfroom->AddRobot();
            if ( ok )
            {
                iter = _room_list._objects.erase( iter );
                _match_module->AddRoom( kfroom );
            }
            else
            {
                ++iter;
            }
        }
    }

}