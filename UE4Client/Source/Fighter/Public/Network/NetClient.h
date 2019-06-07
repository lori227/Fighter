// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetSocket.h"
#include "google/protobuf/message.h"

class NetClient
{
private:
    typedef std::function<void( uint32 msgid, const int8* data, uint32 length )> MessageFunction;

public:
    ~NetClient();

    // 初始化
    void Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend );

    // tick
    void Tick( float deltatime );

    // 开始连接
    void Connect( uint64 id, const FString& ip, uint32 port );

    // 关闭
    void Shutdown();

    // 发送消息
    bool SendNetMessage( uint32 msgid, const int8* data, uint32 length );
    bool SendNetMessage( uint32 msgid, google::protobuf::Message* message );

public:
    // 注册网络事件函数
    template< class T >
    void RegisterNetEventFunction( uint32 type, T* object, void( T::*handle )( uint64 id, int32 code ) )
    {
        NetEventFunction function = std::bind( handle, object, std::placeholders::_1, std::placeholders::_2 );
        _event_function.Add( type, function );
    }

    // 注册消息处理函数
    template< class T >
    void RegisterMessageFunction( T* object, void ( T::*handle )( uint32, const int8*, uint32 ) )
    {
        _message_function = std::bind( handle, object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
    }

protected:
    // 处理网络时间
    void HandleNetEvent();

    // 处理网络消息
    void HandleNetMessage();
protected:
    // id
    uint64 _id = 0u;
    
    // socket
    NetSocket* _net_socket = nullptr;

    // 网络时间
    TMap< uint32, NetEventFunction > _event_function;

    // 消息处理函数
    MessageFunction _message_function;
};
