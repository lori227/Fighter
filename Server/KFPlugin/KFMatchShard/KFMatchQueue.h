#ifndef __KF_MATCH_QUEUE_H__
#define __KF_MATCH_QUEUE_H__

#include "KFMatchRandRoom.h"
#include "KFMatchJoinRoom.h"

namespace KFrame
{
    class KFMatchSetting;
    class KFMatchShardModule;
    class KFMatchQueue : public std::enable_shared_from_this<KFMatchQueue>
    {
    public:
        //////////////////////////////////////////////////////////////////////////////////////
        // 删除匹配玩家
        void RemovePlayer( uint64 player_id );

        // 添加玩家
        void AddPlayer( std::shared_ptr<KFMatchPlayer> match_player );

        // 删除房间
        void RemoveRoom( std::shared_ptr<KFMatchRoom> match_room );
        //////////////////////////////////////////////////////////////////////////////////////
        // 开始匹配
        void StartMatch( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, uint64 battle_server_id );

        // 创建匹配房间
        std::shared_ptr<KFMatchRoom> CreateMatch( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, uint64 battle_server_id, const std::string& title, const std::string& password, bool add_robot );

        // 加入匹配房间
        uint32 JoinMatch( const KFMsg::PBMatchPlayer* pb_player, uint64 room_id, const std::string& version, const std::string& password );

        // 取消匹配
        bool CancelMatch( uint64 player_id );

        // 逻辑
        void RunMatch();

        // 查询房间列表
        void QueryMatch( uint64 player_id, uint64 server_id, uint64 room_id, const std::string& version );

        // 匹配完成
        void RoomMatchFinish( std::shared_ptr<KFMatchRoom> match_room );
    protected:
        // 匹配两个玩家
        void RunMatchPlayer();

        // 房间匹配
        void RunMatchRoom();

        // 查找匹配的房间
        std::shared_ptr<KFMatchRoom> FindMatchRoom( std::shared_ptr<KFMatchPlayer> match_player );

    public:
        // 匹配id
        std::shared_ptr<const KFMatchSetting> _match_setting = nullptr;

        // 匹配模式
        KFMatchShardModule* _match_module = nullptr;

        // 玩家的列表
        KFHashMap<uint64, KFMatchPlayer> _player_list;

        // 正在等待匹配的房间
        KFHashMap<uint64, KFMatchRoom> _room_list;
    };
}


#endif