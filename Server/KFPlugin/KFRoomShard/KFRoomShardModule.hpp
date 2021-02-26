#ifndef __KF_ROOM_SHARD_MOUDLE_H__
#define __KF_ROOM_SHARD_MOUDLE_H__

/************************************************************************
//    @Moudle			:    房间系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2019-3-21
************************************************************************/
#include "KFrameEx.h"
#include "KFBattleRoom.h"
#include "KFRoomShardInterface.h"
#include "KFProtocol/KFProtocol.h"
#include "KFRedis/KFRedisInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    class KFRoomShardModule : public KFRoomShardInterface
    {
    public:
        KFRoomShardModule() = default;
        ~KFRoomShardModule() = default;

        // 逻辑
        virtual void BeforeRun();
        virtual void PrepareRun();
        virtual void Run();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
    protected:
        // 注册战场
        __KF_MESSAGE_FUNCTION__( HandleRegisterBattleToRoomReq, KFMsg::S2SRegisterBattleToRoomReq );

        // 创建房间
        __KF_MESSAGE_FUNCTION__( HandleCreateRoomToRoomReq, KFMsg::S2SCreateRoomToRoomReq );

        // 开启房间
        __KF_MESSAGE_FUNCTION__( HandleOpenRoomToRoomAck, KFMsg::S2SOpenRoomToRoomAck );

        // 通知房间
        __KF_MESSAGE_FUNCTION__( HandleInformBattleToRoomAck, KFMsg::S2SInformBattleToRoomAck );

        // 查询房间
        __KF_MESSAGE_FUNCTION__( HandleQueryRoomToRoomReq, KFMsg::S2SQueryRoomToRoomReq );

        // 结束房间
        __KF_MESSAGE_FUNCTION__( HandleFinishRoomToRoomReq, KFMsg::S2SFinishRoomToRoomReq );

        // 房间心跳
        __KF_MESSAGE_FUNCTION__( HandleHeartBeatToRoomReq, KFMsg::S2SHeartBeatToRoomReq );

        // 玩家结算
        __KF_MESSAGE_FUNCTION__( HandlePlayerBalanceToRoomReq, KFMsg::S2SPlayerBalanceToRoomReq );

        // 玩家结算结果
        __KF_MESSAGE_FUNCTION__( HandlePlayerBalanceToRoomResult, KFMsg::S2SPlayerBalanceToRoomResult );

        // 查询结算
        __KF_MESSAGE_FUNCTION__( HandleQueryBalanceToRoomReq, KFMsg::S2SQueryBalanceToRoomReq );

    protected:
        // 创建战场房间
        std::shared_ptr<KFBattleRoom> CreateBattleRoom( uint64 room_id );

        // 删除战场房间
        void RemoveBattleRoom( uint64 room_id );

        // 发送结算消息到服务器
        void SendPlayerBalanceToGame( uint64 server_id, uint64 player_id, uint64 room_id, const KFMsg::PBBattleBalance* pb_balance );

    private:
        // 房间列表
        KFHashMap<uint64, KFBattleRoom> _room_list;

        // battle redis
        std::shared_ptr<KFRedisDriver> _redis_driver = nullptr;
    };
}



#endif