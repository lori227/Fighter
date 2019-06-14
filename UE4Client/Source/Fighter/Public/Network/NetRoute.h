// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FNetRoute
{
public:
    FNetRoute() = default;
    FNetRoute( uint64 serverid, uint64 sendid, uint64 recvid );

public:
    /**< 发送服务器Id */
    uint64 _server_id = 0u;

    /**< 发送者Id */
    uint64 _send_id = 0u;

    /**< 接受者Id */
    uint64 _recv_id = 0u;
};

#define __ROUTE_SEND_ID__ route._send_id
#define __ROUTE_RECV_ID__ route._recv_id
#define __ROUTE_SERVER_ID__ route._server_id
