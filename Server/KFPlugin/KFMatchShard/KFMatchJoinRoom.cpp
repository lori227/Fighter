#include "KFMatchJoinRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    void KFMatchJoinRoom::InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid )
    {
        KFMatchRoom::InitRoom( kfqueue, grade, version, battleserverid );
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