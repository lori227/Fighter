#ifndef __KF_ROOM_CLIENT_MOUDLE_H__
#define __KF_ROOM_CLIENT_MOUDLE_H__

/************************************************************************
//    @Moudle			:    房间系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2019-3-21
************************************************************************/
#include "KFrameEx.h"
#include "KFProtocol/KFProtocol.h"
#include "KFRoomClientInterface.h"
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    class KFRoomClientModule : public KFRoomClientInterface
    {
    public:
        KFRoomClientModule() = default;
        ~KFRoomClientModule() = default;

        // 逻辑
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
    protected:
        // 通知战场服务器请求
        __KF_MESSAGE_FUNCTION__( HandleInformBattleToGameReq, KFMsg::S2SInformBattleToGameReq );

        // 确认战场服务器
        __KF_MESSAGE_FUNCTION__( HandleInformBattleAck, KFMsg::MsgInformBattleAck );

        // 上线查询房间
        __KF_MESSAGE_FUNCTION__( HandleQueryRoomToGameAck, KFMsg::S2SQueryRoomToGameAck );

        // 房间结束
        __KF_MESSAGE_FUNCTION__( HandleFinishRoomToGameReq, KFMsg::S2SFinishRoomToGameReq );

        // 结算请求
        __KF_MESSAGE_FUNCTION__( HandleBalanceToGameReq, KFMsg::S2SPlayerBalanceToGameReq );

    protected:
        // 上线查新
        __KF_PLAYER_ENTER_FUNCTION__( OnEnterQueryRoom );

        // 设置房间信息
        void SetRoomData( EntityPtr player, uint64 room_id, uint64 room_server_id );
    };
}



#endif