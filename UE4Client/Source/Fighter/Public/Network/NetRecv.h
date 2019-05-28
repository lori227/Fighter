// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"

class NetSocket;

class NetRecv : public Thread
{
public:
    NetRecv( NetSocket* socket, uint32 queuesize );
    ~NetRecv();

    // 开始服务
    void StartService();

    // 停止服务
    void StopService();

    // 弹出消息
    NetMessage* PopMessage();

protected:
    // read
    virtual void ThreadBody();

    // parse message
    void ParseBuffToMessage();

    // read head
    NetHead* CheckRecvBuffValid( uint32 position );

    // 计算地址长度
    void CalcBuffTotalLength( uint32 totallength );

    NetMessage* PopSingleMessage( NetMessage* message );
    NetMessage* PopMultiMessage( NetMessage* message );

private:
    // socket
    NetSocket* _net_socket = nullptr;

    // 缓冲区
    int8* _data_buff = nullptr;
    uint32 _data_buff_length = 0u;

    // 收消息队列
    TCircle< NetMessage > _recv_queue;

    // 投递接受数据的大小
    int8 _req_buff[ NetDefine::MaxReqBuffLength ];

    // 接受消息队列
    uint32 _recv_length = 0u;
    int8 _recv_buff[ NetDefine::MaxRecvBuffLength ];
};
