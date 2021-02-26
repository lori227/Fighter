#include "KFBattlePlayer.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////
    void KFBattlePlayer::CopyFrom( const KFMsg::PBMatchPlayer* pb_player )
    {
        _id = pb_player->id();
        _pb_player.CopyFrom( *pb_player );
    }

    void KFBattlePlayer::SaveTo( KFMsg::PBMatchPlayer* pb_player )
    {
        pb_player->CopyFrom( _pb_player );
    }

    bool KFBattlePlayer::SendToGame( uint32 msg_id, google::protobuf::Message* message )
    {
        if ( _pb_player.isrobot() )
        {
            return true;
        }

        return _kf_route->SendToEntity( _pb_player.serverid(), _id, msg_id, message );
    }


}