// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class NetRoute
{
public:
    NetRoute() = default;
    NetRoute( uint64 serverid, uint64 sendid, uint64 recvid );

public:
    /**< ���ͷ�����Id */
    uint64 _server_id = 0u;

    /**< ������Id */
    uint64 _send_id = 0u;

    /**< ������Id */
    uint64 _recv_id = 0u;
};

#define __ROUTE_SEND_ID__ route._send_id
#define __ROUTE_RECV_ID__ route._recv_id
#define __ROUTE_SERVER_ID__ route._server_id
