#ifndef __KF_MATCH_ROOM_H__
#define __KF_MATCH_ROOM_H__

#include "KFMatchPlayer.h"

namespace KFrame
{
    class KFMatchQueue;
    class KFMatchRoom
    {
    protected:
        enum MyEnum
        {
            MatchState = 0,		// 初始
            CreateState = 1,	// 创建room
            DestroyState = 2,	// 销毁
        };

    public:
        // 初始化
        void InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid );

        // 逻辑
        bool Run();

        // 是否匹配
        bool IsMatched( KFMatchPlayer* kfplayer );

        // 添加玩家
        bool AddPlayer( KFMatchPlayer* kfplayer );

        // 添加机器人,
        bool AddRobot();

        // 确认创建
        void AffirmCreate();

        // 取消匹配
        void CancelMatch( KFMatchPlayer* kfplayer );
    protected:
        // 是否有效
        bool IsValid();

        // 改变状态
        void ChangeState( uint32 state, uint32 time );

        // 判断是否满
        bool CheckFull();

        // 创建机器人
        KFMatchPlayer* CreateMatchRobot();

        // 创建房间
        void CreateRoom();

        // 发送匹配玩家数量
        void SentMatchCountToClient();

        // 发送消息
        void SendToRoom( uint32 msgid, google::protobuf::Message* message );

    public:
        // 房间id
        uint64 _id = _invalid_int;

        // 玩家的列表
        KFHashMap< uint64, uint64, KFMatchPlayer > _player_list;

        // 积分
        uint32 _grade = _invalid_int;
    private:
        // 版本号
        std::string _version;

        // 房间id
        uint64 _battle_server_id = _invalid_int;

        // 状态
        uint32 _state = _invalid_int;

        // 定时器
        KFTimer _timer;

        // 匹配队列
        KFMatchQueue* _match_queue;

        // 添加机器人时间
        uint64 _next_add_robot_time;
    };
}


#endif