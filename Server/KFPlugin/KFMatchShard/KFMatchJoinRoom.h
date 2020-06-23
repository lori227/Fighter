#ifndef __KF_MATCH_JOIN_ROOM_H__
#define __KF_MATCH_JOIN_ROOM_H__

#include "KFMatchRoom.h"

namespace KFrame
{
    class KFMatchJoinRoom : public KFMatchRoom
    {
    public:
        // 初始化
        virtual void InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid );

        // 是否匹配
        virtual bool IsMatched( KFMatchPlayer* kfplayer );

        // 添加玩家
        virtual bool AddPlayer( KFMatchPlayer* kfplayer );

        // 取消匹配
        virtual uint32 CancelMatch( KFMatchPlayer* kfplayer );
    protected:

    };
}


#endif