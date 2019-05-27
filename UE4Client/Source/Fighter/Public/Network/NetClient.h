// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetSocket.h"
#include "NetClient.generated.h"

UCLASS()
class UNetClient : public UObject
{
    GENERATED_UCLASS_BODY()

private:
    typedef std::function<void( uint32 msgid, const int8* data, uint32 length )> MessageFunction;

public:
    ~UNetClient();

    // 初始化
    void Init( const FString& name, uint32 sendqueuesize, uint32 recvqueuesize, uint32 headlength, bool disconnectsend );

    // tick
    void Tick( float ParamDeltaTime );

    // 开始连接
    void Connect( const FString& ip, uint32 port );

    // 关闭
    void Close();

public:
    // 注册网络事件函数
    template< class T >
    void RegisterEventFunction( uint32 type, T* object, void( T::*handle )( const UNetEvent* ) )
    {
        NetEventFunction function = std::bind( handle, object, std::placeholders::_1 );
        _event_function.Add( tpe, function );
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
    // socket
    UNetSocket* _net_socket = nullptr;

    // 网络时间
    TMap< uint32, NetEventFunction > _event_function;

    // 消息处理函数
    MessageFunction _message_function;
};
