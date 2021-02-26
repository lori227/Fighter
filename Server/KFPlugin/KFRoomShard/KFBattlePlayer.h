#ifndef __KF_BATTLE_PLAYER_H__
#define __KF_BATTLE_PLAYER_H__

#include "KFrame.h"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    class KFBattlePlayer
    {
    public:
        // 加载
        void CopyFrom( const KFMsg::PBMatchPlayer* pb_player );

        // 保存
        void SaveTo( KFMsg::PBMatchPlayer* pb_player );

        // 发送消息
        bool SendToGame( uint32 msg_id, google::protobuf::Message* message );

    public:
        // 玩家id
        uint64 _id = 0u;

        // 是否已经结算
        bool _is_balance = false;

        // 游戏玩家数据
        KFMsg::PBMatchPlayer _pb_player;
    };
}

#endif