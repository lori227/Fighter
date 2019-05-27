// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Network/NetConnect.h"
#include "Public/Network/NetSocket.h"
#include "Public/Network/NetDefine.h"


UNetConnect::UNetConnect( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetConnect::~UNetConnect()
{
}

void UNetConnect::StartService( NetSocket* socket, const FString& ip, uint32 port )
{
    _ip = ip;
    _port = port;
    _net_socket = socket;

    // 开启线程
    StartThread( TEXT( "NetConnect" ), false );
}

void UNetConnect::StopService()
{
    EnsureCompletion();
}

void UNetConnect::ThreadBody()
{
    uint32 eventtype = 0u;
    __LOG_INFO__( LogNetwork, "start connect server=[{}:{}]!", TCHAR_TO_UTF8( *_ip ), _port );

    FIPv4Address address;
    FIPv4Address::Parse( _ip, address );

    // 创建addr存放IPv4地址和端口
    auto internetaddr = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateInternetAddr( address.Value, _port );
    if ( internetaddr->IsValid() )
    {
        auto ok = _net_socket->_socket->Connect( *internetaddr );
        if ( ok )
        {
            _net_socket->_is_connect = true;
            eventtype = NetDefine::ConnectEvent;
            __LOG_INFO__( LogNetwork, "connect server=[{}:{}] ok!", TCHAR_TO_UTF8( *_ip ), _port );
        }
        else
        {
            eventtype = NetDefine::FailedEvent;
            __LOG_ERROR__( LogNetwork, "connect server=[{}:{}] failed!", TCHAR_TO_UTF8( *_ip ), _port );
        }
    }
    else
    {
        eventtype = NetDefine::FailedEvent;
        __LOG_ERROR__( LogNetwork, "createinternetaddr failed!" );
    }

    // 添加网络事件
    _net_socket->PushNetEvent( eventtype );
}