#ifndef __KF_MATCH_JOIN_ROOM_H__
#define __KF_MATCH_JOIN_ROOM_H__

#include "KFMatchRoom.h"

namespace KFrame
{
    class KFMatchJoinRoom : public KFMatchRoom
    {
    public:
        KFMatchJoinRoom();

        // 初始化
        virtual void InitRoom( std::shared_ptr<KFMatchQueue> match_queue, std::shared_ptr<KFMatchPlayer> match_player,
                               const std::string& title, const std::string& password, bool add_robot );

        // 保存房间信息
        virtual void SaveTo( KFMsg::PBMatchRoom* pb_room, bool is_player_list );

        // 是否匹配
        virtual bool IsMatched( std::shared_ptr<KFMatchPlayer> match_player );

        // 添加玩家
        virtual bool AddPlayer( std::shared_ptr<KFMatchPlayer> match_player );

        // 取消匹配
        virtual uint32 CancelMatch( uint64 player_id );

        // 加入玩家
        virtual uint32 JoinPlayer( const KFMsg::PBMatchPlayer* pb_player, const std::string& version, const std::string& password );

        // 踢掉玩家
        virtual uint32 KickPlayer( uint64 master_id, uint64 player_id );

        // 开始战斗
        virtual uint32 FightMatch( uint64 player_id );

        // 准备匹配
        virtual uint32 PrepareMatch( uint64 player_id, bool prepare );

        // 邀请匹配
        virtual uint32 InviteMatch( uint64 invite_id, uint64 player_id, uint64 server_id );
    protected:
        // 更新房主信息
        void ChangeMasterPlayer( uint64 player_id );

        // 判断是否都准备
        bool CheckAllPrepare();

    protected:
        // 标题
        std::string _title;

        // 密码
        std::string _password;

        // 房主
        uint64 _master_player_id;
        std::string _master_player_name;
    };
}


#endif