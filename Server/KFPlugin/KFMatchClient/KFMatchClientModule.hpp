﻿#ifndef __KF_MATCH_CLIENT_MOUDLE_H__
#define __KF_MATCH_CLIENT_MOUDLE_H__

/************************************************************************
//    @Moudle			:    匹配系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2019-3-21
************************************************************************/
#include "KFrameEx.h"
#include "KFMatchClientInterface.h"
#include "KFProtocol/KFProtocol.h"
#include "KFOption/KFOptionInterface.h"
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"
#include "KFZConfig/KFMatchConfig.hpp"

namespace KFrame
{
    class KFMatchClientModule : public KFMatchClientInterface
    {
    public:
        KFMatchClientModule() = default;
        ~KFMatchClientModule() = default;

        // 逻辑
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
    protected:
        // 开始匹配
        __KF_MESSAGE_FUNCTION__( HandleStartMatchReq );

        // 匹配反馈
        __KF_MESSAGE_FUNCTION__( HandleStartMatchToGameAck );

        // 取消匹配
        __KF_MESSAGE_FUNCTION__( HandleCancelMatchReq );

        // 查询匹配
        __KF_MESSAGE_FUNCTION__( HandleQueryMatchToGameAck );

    protected:
        // 上线查询匹配
        __KF_ENTER_PLAYER_FUNCTION__( OnEnterQueryMatch );

        // 下线取消匹配
        __KF_LEAVE_PLAYER_FUNCTION__( OnLeaveCancelMatch );
    protected:
        // 处理匹配请求
        uint32 ProcessStartMatch( KFEntity* player, const std::string& version, uint32 matchid, uint64 serverid );

        // 初始化玩家
        void FormatMatchPlayerData( KFEntity* player, KFMsg::PBMatchPlayer* pbplayer );

        // 设置玩家的匹配信息
        void SetMatchData( KFEntity* player, uint32 matchid, uint64 serverid );
    };
}



#endif