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
        virtual void InitRoom( KFMatchQueue* kfqueue, KFMatchPlayer* kfplayer, const std::string& title, const std::string& password );

        // 保存房间信息
        virtual void SaveTo( KFMsg::PBMatchRoom* pbroom, bool isplayerlist );

        // 是否匹配
        virtual bool IsMatched( KFMatchPlayer* kfplayer );

        // 添加玩家
        virtual bool AddPlayer( KFMatchPlayer* kfplayer );

        // 取消匹配
        virtual uint32 CancelMatch( uint64 playerid );

        // 加入玩家
        virtual uint32 JoinPlayer( const KFMsg::PBMatchPlayer* pbplayer, const std::string& version, const std::string& password );

        // 踢掉玩家
        virtual uint32 KickPlayer( uint64 masterid, uint64 playerid );

        // 开始战斗
        virtual uint32 FightMatch( uint64 playerid );
    protected:
        // 更新房主信息
        void ChangeMasterPlayer( uint64 playerid );

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