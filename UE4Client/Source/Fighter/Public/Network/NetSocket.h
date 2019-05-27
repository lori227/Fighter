// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "NetEvent.h"
#include "Runtime/Networking/Public/Networking.h"

DECLARE_LOG_CATEGORY_CLASS( LogNetwork, All, All );

class FSocket;
class UNetSend;
class UNetRecv;
class UNetConnect;

class NetSocket
{
public:
    NetSocket( uint32 headlength );
    ~NetSocket();

public:
    // init
    void Init( const FString& name, uint32 sendqueuesize, uint32 recvqueuesize );

    // close
    void Close();

    // shutdown
    void Shutdown();

    // tick
    void Tick( float DeltaTime );

public:
    // event
    void AddNetEvent( uint32 type, const FString& describe = TEXT( "" ), int32 code = 0, void* data = nullptr );

    // connect
    void StartConnect( const FString& ip, uint32 port );



public:
    // socket
    FSocket* _socket = nullptr;

    // 是否连接
    std::atomic<bool> _is_connect;

    // 是否关闭
    std::atomic<bool> _is_close;

    // 消息头长度
    uint32 _message_head_length = 0u;

    UNetConnect* _net_connect = nullptr;
    UNetSend* _net_send = nullptr;
    UNetRecv* _net_recv = nullptr;

    // 网络事件列表
    TArray< UNetEvent* > _event_queue;

    /**< 互斥锁 */
    FCriticalSection _event_lock;
};
