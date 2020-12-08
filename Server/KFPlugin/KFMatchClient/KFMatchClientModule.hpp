#ifndef __KF_MATCH_CLIENT_MOUDLE_H__
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
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"
#include "KFConfig/KFMatchConfig.hpp"

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
        __KF_MESSAGE_FUNCTION__( HandleStartMatchReq, KFMsg::MsgStartMatchReq );

        // 匹配反馈
        __KF_MESSAGE_FUNCTION__( HandleStartMatchToGameAck, KFMsg::S2SStartMatchToGameAck );

        // 取消匹配
        __KF_MESSAGE_FUNCTION__( HandleCancelMatchReq, KFMsg::MsgCancelMatchReq );

        // 查询匹配
        __KF_MESSAGE_FUNCTION__( HandleQueryMatchToGameAck, KFMsg::S2SQueryMatchToGameAck );

        // 创建匹配房间
        __KF_MESSAGE_FUNCTION__( HandleCreateMatchReq, KFMsg::MsgCreateMatchReq );

        // 创建匹配房间
        __KF_MESSAGE_FUNCTION__( HandleJoinMatchToGameAck, KFMsg::S2SJoinMatchToGameAck );

        // 加入匹配房间
        __KF_MESSAGE_FUNCTION__( HandleJoinMatchReq, KFMsg::MsgJoinMatchReq );

        // 查询房间列表
        __KF_MESSAGE_FUNCTION__( HandleQueryMatchListReq, KFMsg::MsgQueryMatchListReq );

        // 踢人请求
        __KF_MESSAGE_FUNCTION__( HandleKickMatchReq, KFMsg::MsgKickMatchReq );

        // 处理被踢了
        __KF_MESSAGE_FUNCTION__( HandleKickMatchToGameAck, KFMsg::S2SKickMatchToGameAck );

        // 开始匹配战斗
        __KF_MESSAGE_FUNCTION__( HandleFightMatchReq, KFMsg::MsgFightMatchReq );

        // 准备匹配
        __KF_MESSAGE_FUNCTION__( HandlePrepareMatchReq, KFMsg::MsgPrePareMatchReq );

        // 邀请匹配
        __KF_MESSAGE_FUNCTION__( HandleInviteMatchReq, KFMsg::MsgInviteMatchReq );
    protected:
        // 上线查询匹配
        __KF_PLAYER_ENTER_FUNCTION__( OnEnterQueryMatch );

        // 下线取消匹配
        __KF_PLAYER_LEAVE_FUNCTION__( OnLeaveCancelMatch );
    protected:
        // 判断是否能匹配
        bool CheckCanMatch( KFEntity* player, uint32 matchid );

        // 初始化玩家
        void FormatMatchPlayerData( KFEntity* player, KFMsg::PBMatchPlayer* pbplayer );

        // 设置玩家的匹配信息
        void SetMatchData( KFEntity* player, uint32 matchid, uint64 serverid );
    };
}



#endif