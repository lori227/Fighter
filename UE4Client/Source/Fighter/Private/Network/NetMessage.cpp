// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetMessage.h"

NetMessage::NetMessage( uint32 length )
{
    _head._length = length;
    MallocData( length );
}

NetMessage::~NetMessage()
{
    FreeData();
}

uint32 NetMessage::HeadLength()
{
    return sizeof( ServerHead );
}

void NetMessage::CopyData( const int8* data, uint32 length )
{
    _head._length = length;
    if ( length == 0u || data == nullptr )
    {
        return;
    }

    memcpy( _data, data, length );
}

NetMessage* NetMessage::Create( uint32 length )
{
    return new NetMessage( length );
}

void NetMessage::Release()
{
    FreeData();
}

void NetMessage::CopyFrom( NetMessage* message )
{
    _head = message->_head;
    if ( _head._length > 0u )
    {
        CopyData( message->_data, message->_head._length );
    }
}

void NetMessage::CopyFrom( uint32 msgid, const int8* data, uint32 length )
{
    _head._msgid = msgid;
    CopyData( data, length );
}

void NetMessage::CopyFrom( const NetRoute& route, uint32 msgid, const int8* data, uint32 length )
{
    _head._route = route;
    _head._msgid = msgid;
    CopyData( data, length );
}

void NetMessage::MallocData( uint32 length )
{
    _head._length = length;
    if ( _head._length > 0u )
    {
        _data = ( int8* )malloc( _head._length );
    }
}

void NetMessage::FreeData()
{
    if ( _data != nullptr )
    {
        free( _data );
    }

    _data = nullptr;
    _head._length = 0;
}