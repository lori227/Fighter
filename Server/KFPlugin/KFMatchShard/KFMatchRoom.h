#ifndef __KF_MATCH_ROOM_H__
#define __KF_MATCH_ROOM_H__

#include "KFMatchPlayer.h"
#include "KFXmlReader/KFMatchConfig.hpp"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    namespace KFMatchEnum
    {
        enum MyEnum
        {
            MatchState = 0,		// 初始
            CreateState = 1,	// 创建room
            DestroyState = 2,	// 销毁
            ///////////////////////////////////////
            CancelFailed = 0,	// 取消失败
            CancelOk = 1,		// 取消成功
            CancelDestory = 2,	// 取消销毁
            ///////////////////////////////////////
            RandRoom = 1,		// 随机匹配房间
            CreateRoom = 2,		// 创建匹配房间
        };
    }

    class KFMatchQueue;
    class KFMatchRoom
    {
    public:
        KFMatchRoom() = default;
        virtual ~KFMatchRoom() = default;

        // 初始化
        virtual void InitRoom( KFMatchQueue* kfqueue, KFMatchPlayer* kfplayer, const std::string& title, const std::string& password, bool addrobot );

        // 保存房间信息
        virtual void SaveTo( KFMsg::PBMatchRoom* pbroom, bool isplayerlist );

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
        virtual uint32 CancelMatch( uint64 playerid );

        // 加入房间
        virtual void SendJoinRoomToPlayer( uint64 playerid, uint64 serverid );

        // 加入玩家
        virtual uint32 JoinPlayer( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, const std::string& password );

        // 踢掉玩家
        virtual uint32 KickPlayer( uint64 masterid, uint64 playerid );

        // 开始战斗
        virtual uint32 FightMatch( uint64 playerid );

        // 准备匹配
        virtual uint32 PrepareMatch( uint64 playerid, bool prepare );

        // 邀请匹配
        virtual uint32 InviteMatch( uint64 inviteid, uint64 playerid, uint64 serverid );
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

        // 发送离开消息
        void SendLeaveToRoom( uint64 playerid, uint32 type );

    public:
        // 类型
        uint32 _type = _invalid_int;

        // 房间id
        uint64 _id = _invalid_int;

        // 玩家的列表
        KFHashMap< uint64, uint64, KFMatchPlayer > _player_list;

        // 版本号
        std::string _version;

    protected:
        // 房间id
        uint64 _battle_server_id = _invalid_int;

        // 是否添加机器人
        bool _is_add_robot = false;

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