// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetClient.h"
#include "Public/Network/NetMessage.h"

UNetClient::UNetClient( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetClient::~UNetClient()
{

}

void UNetClient::Init( const FString& name, uint32 sendqueuesize, uint32 recvqueuesize, uint32 headlength, bool disconnectsend )
{
    _net_socket = NewObject< UNetSocket >();
    _net_socket->Init( name, sendqueuesize, recvqueuesize, headlength, disconnectsend );
}

void UNetClient::Connect( const FString& ip, uint32 port )
{
    _net_socket->StartConnect( ip, port );
}

void UNetClient::Close()
{
    _net_socket->Close();
    _net_socket->Shutdown();
    _net_socket = nullptr;
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
    if ( _net_socket == nullptr )
    {
        return;
    }

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
    if ( _net_socket == nullptr )
    {
        return;
    }

    auto message = _net_socket->PopNetMessage();
    if ( message == nullptr )
    {
        return;
    }

    _message_function( message->_head._msgid, message->_data, message->_head._length );
}