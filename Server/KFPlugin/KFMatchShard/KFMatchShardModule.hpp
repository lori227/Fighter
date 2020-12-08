#ifndef __KF_MATCH_SHARD_MOUDLE_H__
#define __KF_MATCH_SHARD_MOUDLE_H__

/************************************************************************
//    @Moudle			:    匹配系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2019-3-21s
************************************************************************/
#include "KFrameEx.h"
#include "KFMatchQueue.h"
#include "KFMatchShardInterface.h"
#include "KFProtocol/KFProtocol.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"
#include "KFConfig/KFMatchConfig.hpp"
#include "KFConfig/KFNameConfig.hpp"
#include "KFConfig/KFHeroConfig.hpp"

namespace KFrame
{
    class KFMatchShardModule : public KFMatchShardInterface
    {
    public:
        KFMatchShardModule() = default;
        ~KFMatchShardModule() = default;

        // 逻辑
        virtual void BeforeRun();
        virtual void PrepareRun();
        virtual void Run();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        // 创建房间
        void AddRoom( KFMatchRoom* kfroom );

    protected:
        // 请求开始匹配
        __KF_MESSAGE_FUNCTION__( HandleStartMatchToShardReq, KFMsg::S2SStartMatchToShardReq );

        // 请求取消匹配
        __KF_MESSAGE_FUNCTION__( HandleCancelMatchToShardReq, KFMsg::S2SCancelMatchToShardReq );

        // 创建房间
        __KF_MESSAGE_FUNCTION__( HandleCreateRoomToMatchAck, KFMsg::S2SCreateRoomToMatchAck );

        // 查询匹配
        __KF_MESSAGE_FUNCTION__( HandleQueryMatchToMatchReq, KFMsg::S2SQueryMatchToMatchReq );

        // 创建匹配房间
        __KF_MESSAGE_FUNCTION__( HandleCreateMatchToShardReq, KFMsg::S2SCreateMatchToShardReq );

        // 申请加入匹配房间
        __KF_MESSAGE_FUNCTION__( HandleJoinMatchToShardReq, KFMsg::S2SJoinMatchToShardReq );

        // 查询房间列表
        __KF_MESSAGE_FUNCTION__( HandleQueryMatchListToShardReq, KFMsg::S2SQueryMatchListToShardReq );

        // 剔除玩家
        __KF_MESSAGE_FUNCTION__( HandleKickMatchToShardReq, KFMsg::S2SKickMatchToShardReq );

        // 开始匹配战斗
        __KF_MESSAGE_FUNCTION__( HandleFightMatchToShardReq, KFMsg::S2SFightMatchToShardReq );

        // 准备匹配房间
        __KF_MESSAGE_FUNCTION__( HandlePrepareMatchToShardReq, KFMsg::S2SPrepareMatchToShardReq );

        // 邀请参加匹配
        __KF_MESSAGE_FUNCTION__( HandleInviteMatchToShardReq, KFMsg::S2SInviteMatchToShardReq );

    protected:
        // 查找匹配模式
        KFMatchQueue* FindMatchQueue( uint32 matchid );

    private:
        // 版本列表
        std::set< std::string > _battle_version_list;

        // 匹配模式列表
        KFHashMap< uint32, KFMatchQueue > _match_queue_list;

        // 匹配的房间
        KFHashMap< uint64, KFMatchRoom > _match_room_list;
    };
}



#endif