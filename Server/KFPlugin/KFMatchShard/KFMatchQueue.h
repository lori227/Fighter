#ifndef __KF_MATCH_QUEUE_H__
#define __KF_MATCH_QUEUE_H__

#include "KFMatchRandRoom.h"
#include "KFMatchJoinRoom.h"

namespace KFrame
{
    class KFMatchSetting;
    class KFMatchShardModule;
    class KFMatchQueue
    {
    public:
        //////////////////////////////////////////////////////////////////////////////////////
        // 删除匹配玩家
        void RemovePlayer( uint64 playerid );

        // 添加玩家
        void AddPlayer( KFMatchPlayer* kfplayer );

        // 删除房间
        void RemoveRoom( KFMatchRoom* kfroom );
        //////////////////////////////////////////////////////////////////////////////////////
        // 开始匹配
        void StartMatch( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, uint64 battleserverid );

        // 创建匹配房间
        KFMatchRoom* CreateMatch( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, uint64 battleserverid, const std::string& title, const std::string& password );

        // 加入匹配房间
        uint32 JoinMatch( const KFMsg::PBMatchPlayer* pbplayer, uint64 roomid, const std::string& version, const std::string& password );

        // 取消匹配
        bool CancelMatch( uint64 playerid );

        // 逻辑
        void RunMatch();

        // 查询房间列表
        void QueryMatch( uint64 playerid, uint64 serverid, uint64 roomid, const std::string& version );

        // 匹配完成
        void RoomMatchFinish( KFMatchRoom* kfroom );
    protected:
        // 匹配两个玩家
        void RunMatchPlayer();

        // 房间匹配
        void RunMatchRoom();

        // 查找匹配的房间
        KFMatchRoom* FindMatchRoom( KFMatchPlayer* kfplayer );

    public:
        // 匹配id
        const KFMatchSetting* _match_setting = nullptr;

        // 匹配模式
        KFMatchShardModule* _match_module;

        // 玩家的列表
        KFHashMap< uint64, uint64, KFMatchPlayer > _player_list;

        // 正在等待匹配的房间
        KFHashMap< uint64, uint64, KFMatchRoom > _room_list;
    };
}


#endif