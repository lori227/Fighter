// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetClient.h"
#include "Public/Network/NetMessage.h"

UNetClient::UNetClient( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetClient::~UNetClient()
{
    __SAFE_DELETE__( _net_socket );
}

void UNetClient::Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend )
{
    _net_socket = new NetSocket();
    _net_socket->Init( name, nettype, sendqueuesize, recvqueuesize, disconnectsend );
}

void UNetClient::Connect( const FString& ip, uint32 port )
{
    // 先关闭
    Close();

    // 创建新的连接
    _net_socket->StartConnect( ip, port );
}

void UNetClient::Close()
{
    _net_socket->Close();
}

bool UNetClient::SendNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    return _net_socket->SendNetMessage( msgid, data, length );
}

void UNetClient::Tick( float ParamDeltaTime )
{
    // 处理网络事件
    HandleNetEvent();

    // 处理网络消息
    HandleNetMessage();
}

void UNetClient::HandleNetEvent()
{
    auto event = _net_socket->PopNetEvent();
    if ( event == nullptr )
    {
        return;
    }

    auto function = _event_function.Find( event->_type );
    if ( function == nullptr )
    {
        __LOG_ERROR__( LogNetwork, "event type=[{}] error!", event->_type );
        return;
    }

    // 网络事件回调
    function->operator()( event );
}

void UNetClient::HandleNetMessage()
{
    auto message = _net_socket->PopNetMessage();
    if ( message == nullptr )
    {
        return;
    }

    _message_function( message->_head._msgid, message->_data, message->_head._length );
}