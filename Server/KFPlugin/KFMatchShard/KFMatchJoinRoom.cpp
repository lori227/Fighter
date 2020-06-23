#include "KFMatchJoinRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    void KFMatchJoinRoom::InitRoom( KFMatchQueue* kfqueue, KFMatchPlayer* kfplayer, const std::string& title, const std::string& password )
    {
        KFMatchRoom::InitRoom( kfqueue, kfplayer, title, password );
        _title = title;
        _password = password;

        _master_player_id = kfplayer->_pb_player.id();
        _master_player_name = kfplayer->_pb_player.name();

        // 添加玩家
        KFMatchRoom::AddPlayer( kfplayer );
    }

    void KFMatchJoinRoom::SaveTo( KFMsg::PBMatchRoom* pbroom, bool isplayerlist )
    {
        KFMatchRoom::SaveTo( pbroom, isplayerlist );

        pbroom->set_title( _title );
        pbroom->set_password( _password );
        pbroom->set_masterid( _master_player_id );
        pbroom->set_mastername( _master_player_name );
    }

    bool KFMatchJoinRoom::AddPlayer( KFMatchPlayer* kfplayer )
    {
        KFMatchRoom::AddPlayer( kfplayer );


        return false;
    }

    bool KFMatchJoinRoom::IsMatched( KFMatchPlayer* kfplayer )
    {
        return false;
    }

    uint32 KFMatchJoinRoom::CancelMatch( KFMatchPlayer* kfplayer )
    {
        auto result = KFMatchRoom::CancelMatch( kfplayer );

        return result;
    }
}