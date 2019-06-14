// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"

class FNetSocket;

class FNetSend : public FThread
{
public:
    FNetSend( FNetSocket* socket, uint32 queuesize );
    ~FNetSend();

    // start
    void StartService();

    // stop
    void StopService();

    // send
    bool SendNetMessage( uint32 msgid, const int8* data, uint32 length );

protected:
    // body
    virtual void ThreadBody();

    // 发送单个消息
    bool SendSingleMessage( uint32 msgid, const int8* data, uint32 length );

    // 发送拆分消息
    bool SendMultiMessage( uint32 msgid, const int8* data, uint32 length );

    // 判断发送buff
    bool CheckBuffLength( uint32 totallength, uint32 messagelength );

    // 发送数据
    void SendNetBuff();

private:
    // socket
    FNetSocket* _net_socket = nullptr;

    // 是否开启了发送
    bool _is_send_start = false;

    // 发消息队列
    TCircle< FNetMessage > _send_queue;

    // 发送消息buff
    uint32 _send_length = 0u;
    int8 _send_buff[ ENetDefine::MaxReqBuffLength ];
};
