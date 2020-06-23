#ifndef __KF_MATCH_ROOM_H__
#define __KF_MATCH_ROOM_H__

#include "KFMatchPlayer.h"
#include "KFZConfig/KFMatchConfig.hpp"
#include "KFRouteClient/KFRouteClientInterface.h"

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
            ///////////////////////////////////////
            CancelFailed = 0,	// 取消失败
            CancelOk = 1,		// 取消成功
            CancelDestory = 2,	// 取消销毁
        };

    public:
        // 初始化
        virtual void InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid );

        // 逻辑
        virtual bool Run();

        // 是否匹配
        virtual bool IsMatched( KFMatchPlayer* kfplayer );

        // 添加玩家
        virtual bool AddPlayer( KFMatchPlayer* kfplayer );

        // 添加机器人
        virtual bool AddRobot();

        // 确认创建
        virtual void AffirmCreate();

        // 取消匹配
        virtual uint32 CancelMatch( KFMatchPlayer* kfplayer );
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

        // 随机机器人英雄id
        uint32 RandHeroId();

        // 发送消息
        void SendToRoom( uint32 msgid, google::protobuf::Message* message );

    public:
        // 房间id
        uint64 _id = _invalid_int;

        // 玩家的列表
        KFHashMap< uint64, uint64, KFMatchPlayer > _player_list;

    protected:
        // 版本号
        std::string _version;

        // 房间id
        uint64 _battle_server_id = _invalid_int;

        // 状态
        uint32 _state = _invalid_int;

        // 积分
        uint32 _grade = _invalid_int;

        // 定时器
        KFTimer _timer;

        // 匹配队列
        KFMatchQueue* _match_queue;
    };
}


#endif