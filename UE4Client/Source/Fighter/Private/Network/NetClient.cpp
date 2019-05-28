// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetClient.h"
#include "Public/Network/NetMessage.h"

NetClient::~NetClient()
{
    __SAFE_DELETE__( _net_socket );
}

void NetClient::Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend )
{
    _net_socket = new NetSocket();
    _net_socket->Init( name, nettype, sendqueuesize, recvqueuesize, disconnectsend );
}

void NetClient::Connect( const FString& ip, uint32 port )
{
    // 创建新的连接
    _net_socket->StartConnect( ip, port );
}

void NetClient::Close()
{
    _net_socket->Close();
}

bool NetClient::SendNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    return _net_socket->SendNetMessage( msgid, data, length );
}

void NetClient::Tick( float ParamDeltaTime )
{
    // 处理网络事件
    HandleNetEvent();

    // 处理网络消息
    HandleNetMessage();
}

void NetClient::HandleNetEvent()
{
    auto event = _net_socket->PopNetEvent();
    while ( event != nullptr )
    {
        auto function = _event_function.Find( event->_type );
        if ( function != nullptr )
        {
            // 网络事件回调
            function->operator()( event );
        }
        else
        {
            __LOG_ERROR__( LogNetwork, "event type=[{}] error!", event->_type );
        }

        event = _net_socket->PopNetEvent();
    }
}

void NetClient::HandleNetMessage()
{
    auto message = _net_socket->PopNetMessage();
    while ( message != nullptr )
    {
        _message_function( message->_head._msgid, message->_data, message->_head._length );
        message = _net_socket->PopNetMessage();
    }
}