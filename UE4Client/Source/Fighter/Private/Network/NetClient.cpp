// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetClient.h"
#include "Public/Network/NetMessage.h"

FNetClient::~FNetClient()
{
    __SAFE_DELETE__( _net_socket );
}

void FNetClient::Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend )
{
    _net_socket = new FNetSocket();
    _net_socket->Init( name, nettype, sendqueuesize, recvqueuesize, disconnectsend );
}

void FNetClient::Connect( uint64 id, const FString& ip, uint32 port )
{
    _id = id;

    // 创建新的连接
    _net_socket->StartConnect( ip, port );
}

void FNetClient::Shutdown()
{
    _net_socket->Close();
}

bool FNetClient::SendNetMessage( uint32 msgid, google::protobuf::Message* message )
{
    auto strdata = message->SerializeAsString();
    return SendNetMessage( msgid, ( const int8* )strdata.data(), strdata.size() );
}

bool FNetClient::SendNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    return _net_socket->SendNetMessage( msgid, data, length );
}

void FNetClient::Tick( float deltatime )
{   // 处理网络事件
    HandleNetEvent();

    // 处理网络消息
    HandleNetMessage();
}

void FNetClient::HandleNetEvent()
{
    auto event = _net_socket->PopNetEvent();
    while ( event != nullptr )
    {
        auto function = _event_function.Find( event->_type );
        if ( function != nullptr )
        {
            // 网络事件回调
            function->operator()( _id, event->_code );
        }
        else
        {
            __LOG_ERROR__( LogNetwork, "event type=[{}] error!", event->_type );
        }

        event = _net_socket->PopNetEvent();
    }
}

void FNetClient::HandleNetMessage()
{
    // 发送ping消息
    _net_socket->SendPingMessage();

    auto message = _net_socket->PopNetMessage();
    while ( message != nullptr )
    {
        _message_function( message->_head._msgid, message->_data, message->_head._length );
        message = _net_socket->PopNetMessage();
    }
}
