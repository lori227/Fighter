// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"
#include "NetRecv.generated.h"

class NetSocket;

UCLASS()
class UNetRecv : public UThread
{
    GENERATED_UCLASS_BODY()

public:
    ~UNetRecv();

    // init
    void InitData( NetSocket* socket, uint32 queuesize );

private:
    // socket
    NetSocket* _net_socket = nullptr;

    // 缓冲区
    int8* _data_buff = nullptr;

    // 收消息队列
    CircleQueue< UNetMessage > _recv_queue;

    // 投递接受数据的大小
    int8 _req_buff[ NetDefine::MaxReqBuffLength ];

    // 接受消息队列
    uint32 _recv_length = 0u;
    int8 _recv_buff[ NetDefine::MaxRecvBuffLength ];
};
