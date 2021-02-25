﻿#ifndef __KF_GAME_INTERFACE_H__
#define __KF_GAME_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    class KFGameInterface : public KFModule
    {
    public:
        // 发送消息到世界服务器
        virtual bool SendToWorld( uint32 msg_id, ::google::protobuf::Message* message ) = 0;

        // 发送消息到Gate服务器
        virtual void SendToGate( uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        virtual bool SendToGate( uint64 gate_id, uint32 msg_id, ::google::protobuf::Message* message ) = 0;

        // 发送消息到客户端
        virtual bool SendToClient( uint64 gate_id, uint64 player_id, uint32 msg_id, ::google::protobuf::Message* message, uint32 delay = 0u ) = 0;
        virtual bool SendToClient( EntityPtr player, uint32 msg_id, ::google::protobuf::Message* message, uint32 delay = 0u ) = 0;

        // 发送到玩家
        virtual bool SendToPlayer( uint64 send_id, DataPtr basic_data, uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        virtual bool SendToPlayer( uint64 send_id, uint64 server_id, uint64 player_id, uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////
        // 广播消息到客户端
        virtual void BroadcastToGate( uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        virtual void BroadcastToGame( uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        virtual void BroadcastToWorld( uint32 msg_id, ::google::protobuf::Message* message ) = 0;

        // 广播到本进程的所有玩家
        virtual void BroadcastToServer( uint32 msg_id, ::google::protobuf::Message* message ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////
        // 踢掉角色
        virtual bool KickPlayer( uint64 player_id, uint32 type, const char* function, uint32 line ) = 0;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_game, KFGameInterface );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}



#endif