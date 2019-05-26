// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetRoute.h"

NetRoute::NetRoute( uint64 serverid, uint64 sendid, uint64 recvid )
    : _server_id( serverid )
    , _send_id( sendid )
    , _recv_id( recvid )
{

}