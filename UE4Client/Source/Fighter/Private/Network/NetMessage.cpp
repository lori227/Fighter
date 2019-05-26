// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetMessage.h"

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
    _length = length;
    if ( length == 0u || data == nullptr )
    {
        return;
    }

    memcpy( _data, data, length );
}

NetMessage* NetMessage::Create( uint32 length )
{
    auto* message = new NetMessage();
    message->MallocData( length );
    return message;
}

void NetMessage::Release()
{
    FreeData();
}

void NetMessage::CopyFrom( NetMessage* message )
{
    _route = message->_route;
    _msgid = message->_msgid;
    _length = message->_length;
    _child = message->_child;
    if ( _length > 0u )
    {
        CopyData( message->_data, message->_length );
    }
}

void NetMessage::CopyFrom( const NetRoute& route, uint32 msgid, const int8* data, uint32 length )
{
    _route = route;
    _msgid = msgid;
    CopyData( data, length );
}

void NetMessage::MallocData( uint32 length )
{
    _length = length;
    if ( _length > 0u )
    {
        _data = ( int8* )malloc( length );
    }
}

void NetMessage::FreeData()
{
    if ( _data != nullptr )
    {
        free( _data );
    }

    _data = nullptr;
    _length = 0;
}