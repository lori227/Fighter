// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"

class FNetSocket;

class FNetRecv : public FThread
{
public:
    FNetRecv( FNetSocket* socket, uint32 queuesize );
    ~FNetRecv();

    // 开始服务
    void StartService();

    // 停止服务
    void StopService();

    // 弹出消息
    FNetMessage* PopMessage();

protected:
    // read
    virtual void ThreadBody();

    // parse message
    void ParseBuffToMessage();

    // read head
    FNetHead* CheckRecvBuffValid( uint32 position );

    // 计算地址长度
    void CalcBuffTotalLength( uint32 totallength );

    FNetMessage* PopSingleMessage( FNetMessage* message );
    FNetMessage* PopMultiMessage( FNetMessage* message );

private:
    // socket
    FNetSocket* _net_socket = nullptr;

    // 缓冲区
    int8* _data_buff = nullptr;
    uint32 _data_buff_length = 0u;

    // 收消息队列
    TCircle< FNetMessage > _recv_queue;

    // 投递接受数据的大小
    int8 _req_buff[ ENetDefine::MaxReqBuffLength ];

    // 接受消息队列
    uint32 _recv_length = 0u;
    int8 _recv_buff[ ENetDefine::MaxRecvBuffLength ];
};
