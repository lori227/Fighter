// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetRoute.h"

#pragma pack( 1 )

///////////////////////////////////////////////////////////////////////////////////////////
class NetHead
{
public:
    uint32 _length = 0u;	// ��Ϣ����
    uint16 _msgid = 0u;		// ��Ϣ����
    uint16 _child = 0u;		// ����Ϣ����( �����Լ� )
};

// �ͻ����������֮�����Ϣͷ
class ClientHead : public NetHead
{
public:

};

// ������֮�����Ϣͷ
class ServerHead : public NetHead
{
public:
    NetRoute _route;		// ·����Ϣ
};
///////////////////////////////////////////////////////////////////////////////////////////
// ��Ϣ����
class NetMessage : public ServerHead
{
public:
    ~NetMessage();

    // ������Ϣ
    static NetMessage* Create( uint32 length );
    void Release();

    // ��Ϣ����
    static uint32 HeadLength();
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    // ��������
    void CopyData( const int8* data, uint32 length );

    // ������Ϣ
    void CopyFrom( NetMessage* message );
    void CopyFrom( const NetRoute& route, uint32 msgid, const int8* data, uint32 length );
    ///////////////////////////////////////////////////////////////////////////////

protected:
    // �����ڴ�
    void MallocData( uint32 length );
    void FreeData();

public:
    int8* _data = nullptr;		// ��Ϣ����
};

#pragma pack()