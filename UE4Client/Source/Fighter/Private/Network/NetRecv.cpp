// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetRecv.h"
#include "Public/Network/NetSocket.h"

UNetRecv::UNetRecv( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetRecv::~UNetRecv()
{
    free( _data_buff );
    _data_buff = nullptr;

    _recv_queue.ClearObject();
}

void UNetRecv::InitData( NetSocket* socket, uint32 queuesize )
{
    Init();

    _net_socket = socket;
    _recv_queue.InitQueue( queuesize );
    _data_buff = ( int8* )malloc( NetDefine::SerializeBuffLength );
}

