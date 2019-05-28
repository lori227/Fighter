// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetSocket.h"
#include "Public/Network/NetConnect.h"
#include "Public/Network/NetSend.h"
#include "Public/Network/NetRecv.h"

NetSocket::NetSocket()
{
    _is_close = false;
    _is_connect = false;
}

NetSocket::~NetSocket()
{
    __SAFE_DELETE__( _net_connect );
    __SAFE_DELETE__( _net_send );
    __SAFE_DELETE__( _net_recv );
    __SAFE_DELETE_FUNCTION__( _socket, ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->DestroySocket );
}

void NetSocket::Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend )
{
    _name = name;
    _is_disconnect_send = disconnectsend;
    _message_head_length = ( nettype == ENetType::Server ? sizeof( ServerHead ) : sizeof( ClientHead ) );

    _net_connect = new NetConnect( this );
    _net_send = new NetSend( this, sendqueuesize );
    _net_recv = new NetRecv( this, recvqueuesize );
}

void NetSocket::Close()
{
    _is_close = true;
    _is_connect = false;

    if ( _socket != nullptr )
    {
        _socket->Close();
        __SAFE_DELETE_FUNCTION__( _socket, ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->DestroySocket );
    }

    if ( _net_connect != nullptr )
    {
        _net_connect->StopService();
    }

    if ( _net_send != nullptr )
    {
        _net_send->StopService();
    }

    if ( _net_recv != nullptr )
    {
        _net_recv->StopService();
    }
}

void NetSocket::StartConnect( const FString& ip, uint32 port )
{
    Close();

    _is_close = false;
    if ( _socket == nullptr )
    {
        _socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, _name, false );
        if ( _socket == nullptr )
        {
            __LOG_ERROR__( LogNetwork, "create [{}] socket failed!", TCHAR_TO_UTF8( *_name ) );
            return PushNetEvent( NetDefine::FailedEvent );
        }
    }

    // 开启连接服务
    _last_recv_time = clock();
    _net_send->StartService();
    _net_recv->StartService();
    _net_connect->StartService( ip, port );
}

void NetSocket::PushNetEvent( uint32 type, int32 code /* = 0 */, void* data /* = nullptr */ )
{
    if ( _is_close )
    {
        return;
    }

    auto event = new NetEvent();
    event->_type = type;
    event->_code = code;
    event->_data = data;

    FScopeLock Lock( &_event_lock );
    _event_queue.push_back( event );
}

NetEvent* NetSocket::PopNetEvent()
{
    NetEvent* event = nullptr;
    {
        FScopeLock Lock( &_event_lock );
        if ( !_event_queue.empty() )
        {
            event = _event_queue.front();
            _event_queue.pop_front();
        }
    }

    if ( event == nullptr )
    {
        return nullptr;
    }

    static int8* _buff[ 56 ] = {};
    memcpy( _buff, event, sizeof( NetEvent ) );

    delete event;
    return ( NetEvent* )_buff;
}

bool NetSocket::SendNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    if ( !_is_connect && !_is_disconnect_send )
    {
        return false;
    }

    return _net_send->SendNetMessage( msgid, data, length );
}

NetMessage* NetSocket::PopNetMessage()
{
    auto message = _net_recv->PopMessage();
    if ( message != nullptr )
    {
        _last_recv_time = clock();

        // ping 消息
        if ( message->_head._msgid == 0u )
        {
            message = _net_recv->PopMessage();
        }
    }
    else
    {
        // 超过60秒没有消息,认为已经断线了,
        // 服务器没20秒发送一个ping消息
        if ( _is_connect )
        {
            if ( ( clock() - _last_recv_time ) > 60000 )
            {
                _is_connect = false;
                PushNetEvent( NetDefine::DisconnectEvent );
            }
        }
    }

    return message;
}