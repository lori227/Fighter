// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetSocket.h"
#include "Public/Network/NetConnect.h"
#include "Public/Network/NetSend.h"
#include "Public/Network/NetRecv.h"


UNetSocket::UNetSocket( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    _is_close = false;
    _is_connect = true;
}

UNetSocket::~UNetSocket()
{

}

void UNetSocket::Init( const FString& name, uint32 sendqueuesize, uint32 recvqueuesize, uint32 headlength, bool disconnectsend )
{
    _net_connect = NewObject<UNetConnect>();

    _net_send = NewObject<UNetSend>();
    _net_send->StartService( this, sendqueuesize );

    _net_recv = NewObject<UNetRecv>();
    _net_recv->StartService( this, recvqueuesize );
    _socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, name, false );
}

void UNetSocket::Close()
{
    _is_close = true;
    _is_connect = false;
    _socket->Close();
}

void UNetSocket::Shutdown()
{
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

    __SAFE_DELETE_FUNCTION__( _socket, ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->DestroySocket );
}

void UNetSocket::StartConnect( const FString& ip, uint32 port )
{
    // 开启连接服务
    _net_connect->StartService( this, ip, port );
}

void UNetSocket::PushNetEvent( uint32 type, const FString& describe /* = TEXT( "" ) */, int32 code /* = 0 */, void* data /* = nullptr */ )
{
    auto event = NewObject< UNetEvent >();
    event->_type = type;
    event->_describe = describe;
    event->_code = code;
    event->_data = data;

    FScopeLock Lock( &_event_lock );
    _event_queue.Insert( event, 0 );
}

UNetEvent* UNetSocket::PopNetEvent()
{
    FScopeLock Lock( &_event_lock );
    auto size = _event_queue.Num();
    if ( size == 0 )
    {
        return nullptr;
    }

    return _event_queue.Pop();
}

bool UNetSocket::SendNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    if ( !_is_connect && !_is_disconnect_send )
    {
        return false;
    }

    return _net_send->SendNetMessage( msgid, data, length );
}

UNetMessage* UNetSocket::PopNetMessage()
{
    return _net_recv->PopMessage();
}