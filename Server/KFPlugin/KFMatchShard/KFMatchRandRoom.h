#ifndef __KF_MATCH_RAND_ROOM_H__
#define __KF_MATCH_RAND_ROOM_H__

#include "KFMatchRoom.h"

namespace KFrame
{
    class KFMatchRandRoom : public KFMatchRoom
    {
    public:
        // 初始化
        virtual void InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid );

        // 是否匹配
        virtual bool IsMatched( KFMatchPlayer* kfplayer );

        // 添加玩家
        virtual bool AddPlayer( KFMatchPlayer* kfplayer );

        // 添加机器人,
        virtual bool AddRobot();

    protected:
        // 发送匹配玩家数量
        void SentMatchCountToClient();
    private:
        // 添加机器人时间
        uint64 _next_add_robot_time;
    };
}


#endif