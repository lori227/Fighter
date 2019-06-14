// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetMessage.h"

FNetMessage::FNetMessage( uint32 length )
{
    _head._length = length;
    MallocData( length );
}

FNetMessage::~FNetMessage()
{
    FreeData();
}

uint32 FNetMessage::HeadLength()
{
    return sizeof( FServerHead );
}

void FNetMessage::CopyData( const int8* data, uint32 length )
{
    _head._length = length;
    if ( length == 0u || data == nullptr )
    {
        return;
    }

    memcpy( _data, data, length );
}

FNetMessage* FNetMessage::Create( uint32 length )
{
    return new FNetMessage( length );
}

void FNetMessage::Release()
{
    FreeData();
}

void FNetMessage::CopyFrom( FNetMessage* message )
{
    _head = message->_head;
    if ( _head._length > 0u )
    {
        CopyData( message->_data, message->_head._length );
    }
}

void FNetMessage::CopyFrom( uint32 msgid, const int8* data, uint32 length )
{
    _head._msgid = msgid;
    CopyData( data, length );
}

void FNetMessage::CopyFrom( const FNetRoute& route, uint32 msgid, const int8* data, uint32 length )
{
    _head._route = route;
    _head._msgid = msgid;
    CopyData( data, length );
}

void FNetMessage::MallocData( uint32 length )
{
    _head._length = length;
    if ( _head._length > 0u )
    {
        _data = ( int8* )malloc( _head._length );
    }
}

void FNetMessage::FreeData()
{
    if ( _data != nullptr )
    {
        free( _data );
    }

    _data = nullptr;
    _head._length = 0;
}