// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetRoute.h"

#pragma pack( 1 )

///////////////////////////////////////////////////////////////////////////////////////////
class NetHead
{
public:
    // 消息长度
    uint32 _length = 0u;

    // 消息类型
    uint16 _msgid = 0u;

    // 子消息个数( 包括自己 )
    uint16 _child = 0u;
};

// 客户端与服务器之间的消息头
class ClientHead : public NetHead
{
public:

};

// 服务器之间的消息头
class ServerHead : public NetHead
{
public:
    // 路由信息
    NetRoute _route;
};
///////////////////////////////////////////////////////////////////////////////////////////
// 消息类
class NetMessage
{
public:
    ~NetMessage();

    // 创建消息
    static NetMessage* Create( uint32 length );
    void Release();

    // 消息长度
    static uint32 HeadLength();
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    // 拷贝数据
    void CopyData( const int8* data, uint32 length );

    // 复制消息
    void CopyFrom( NetMessage* message );
    void CopyFrom( uint32 msgid, const int8* data, uint32 length );
    void CopyFrom( const NetRoute& route, uint32 msgid, const int8* data, uint32 length );
    ///////////////////////////////////////////////////////////////////////////////

protected:
    NetMessage( uint32 length );

    // 分配内存
    void MallocData( uint32 length );
    void FreeData();

public:
    // 消息头
    ServerHead _head;

    // 消息数据
    int8* _data = nullptr;
};

#pragma pack()