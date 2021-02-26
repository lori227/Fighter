#include "KFMatchPlayer.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    void KFMatchPlayerManage::Add( uint64 id, KFMatchPlayer* player )
    {
        _player_list[id] = player;
    }

    void KFMatchPlayerManage::Remove( uint64 id )
    {
        _player_list.erase( id );
    }

    KFMatchPlayer* KFMatchPlayerManage::Find( uint64 id )
    {
        auto iter = _player_list.find( id );
        if ( iter == _player_list.end() )
        {
            return nullptr;
        }

        return iter->second;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    KFMatchPlayer::~KFMatchPlayer()
    {
        _match_player_manage->Remove( _id );
    }

    void KFMatchPlayer::CopyFrom( const KFMsg::PBMatchPlayer* pb_player )
    {
        _id = pb_player->id();
        _pb_player.CopyFrom( *pb_player );
        _match_player_manage->Add( _id, this );
    }

    void KFMatchPlayer::SaveTo( KFMsg::PBMatchPlayer* pb_player )
    {
        pb_player->CopyFrom( _pb_player );
    }
}