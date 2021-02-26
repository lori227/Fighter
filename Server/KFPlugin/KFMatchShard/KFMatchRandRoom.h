﻿#ifndef __KF_MATCH_RAND_ROOM_H__
#define __KF_MATCH_RAND_ROOM_H__

#include "KFMatchRoom.h"

namespace KFrame
{
    class KFMatchRandRoom : public KFMatchRoom
    {
    public:
        KFMatchRandRoom();

        // 初始化
        virtual void InitRoom( std::shared_ptr<KFMatchQueue> match_queue, std::shared_ptr<KFMatchPlayer> match_player,
                               const std::string& title, const std::string& password, bool add_robot );

        // 保存房间信息
        virtual void SaveTo( KFMsg::PBMatchRoom* pb_room, bool is_player_list );

        // 是否匹配
        virtual bool IsMatched( std::shared_ptr<KFMatchPlayer> match_player );

        // 添加玩家
        virtual bool AddPlayer( std::shared_ptr<KFMatchPlayer> match_player );

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