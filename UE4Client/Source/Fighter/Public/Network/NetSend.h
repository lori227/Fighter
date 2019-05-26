// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"
#include "NetSend.generated.h"

class NetSocket;

UCLASS()
class UNetSend : public UThread
{
    GENERATED_UCLASS_BODY()

public:
    ~UNetSend();

    // init
    void InitData( NetSocket* socket, uint32 queuesize );

private:
    // socket
    NetSocket* _net_socket = nullptr;

    // 发消息队列
    CircleQueue< UNetMessage > _send_queue;

    // 发送消息buff
    uint32 _send_length = 0u;
    int8 _send_buff[ NetDefine::MaxReqBuffLength ];
};
