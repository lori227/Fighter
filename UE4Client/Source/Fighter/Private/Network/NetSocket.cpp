// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetSocket.h"
#include "Public/Network/NetConnect.h"
#include "Public/Network/NetSend.h"
#include "Public/Network/NetRecv.h"


NetSocket::NetSocket( uint32 headlength )
{
    _is_close = false;
    _is_connect = true;
    _message_head_length = headlength;
}

NetSocket::~NetSocket()
{
    __SAFE_DELETE__( _net_connect );
    __SAFE_DELETE__( _net_send );
    __SAFE_DELETE__( _net_recv );
}

void NetSocket::Init( const FString& name, uint32 sendqueuesize, uint32 recvqueuesize )
{
    _event_queue.InitQueue( 100 );

    _net_connect = NewObject<UNetConnect>();
    _net_connect->InitData( this );

    _net_send = NewObject<UNetSend>();
    _net_send->InitData( this, sendqueuesize );

    _net_recv = NewObject<UNetRecv>();
    _net_recv->InitData( this, recvqueuesize );
    _socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, name, false );
}

void NetSocket::Close()
{
    _is_close = true;
    _is_connect = false;
    _socket->Close();
}

void NetSocket::Shutdown()
{
    if ( _net_connect != nullptr )
    {
        _net_connect->EnsureCompletion();
    }

    if ( _net_send != nullptr )
    {
        _net_send->EnsureCompletion();
    }

    if ( _net_recv != nullptr )
    {
        _net_recv->EnsureCompletion();
    }

    __SAFE_DELETE_FUNCTION__( _socket, ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->DestroySocket );
}

void NetSocket::Tick( float DeltaTime )
{

}

void NetSocket::AddNetEvent( uint32 type, const FString& describe /* = TEXT( "" ) */, int32 code /* = 0 */, void* data /* = nullptr */ )
{
    auto event = NewObject< UNetEvent >();
    event->_type = type;
    event->_describe = describe;
    event->_code = code;
    event->_data = data;
    _event_queue.PushObject( event );
}

void NetSocket::StartConnect( const FString& ip, uint32 port )
{
    _net_connect->Connect( ip, port );
}
