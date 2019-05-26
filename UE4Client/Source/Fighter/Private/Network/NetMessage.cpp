// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetMessage.h"

UNetMessage::UNetMessage( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}


UNetMessage::~UNetMessage()
{
    FreeData();
}

uint32 UNetMessage::HeadLength()
{
    return sizeof( ServerHead );
}

void UNetMessage::CopyData( const int8* data, uint32 length )
{
    _head._length = length;
    if ( length == 0u || data == nullptr )
    {
        return;
    }

    memcpy( _data, data, length );
}

UNetMessage* UNetMessage::Create( uint32 length )
{
    auto message = NewObject< UNetMessage >();
    message->MallocData( length );
    return message;
}

void UNetMessage::Release()
{
    FreeData();
}

void UNetMessage::CopyFrom( UNetMessage* message )
{
    _head = message->_head;
    if ( _head._length > 0u )
    {
        CopyData( message->_data, message->_head._length );
    }
}

void UNetMessage::CopyFrom( const NetRoute& route, uint32 msgid, const int8* data, uint32 length )
{
    _head._route = route;
    _head._msgid = msgid;
    CopyData( data, length );
}

void UNetMessage::MallocData( uint32 length )
{
    _head._length = length;
    if ( _head._length > 0u )
    {
        _data = ( int8* )malloc( length );
    }
}

void UNetMessage::FreeData()
{
    if ( _data != nullptr )
    {
        free( _data );
    }

    _data = nullptr;
    _head._length = 0;
}