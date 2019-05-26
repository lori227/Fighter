// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetSend.h"
#include "Public/Network/NetSocket.h"


UNetSend::UNetSend( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetSend::~UNetSend()
{
    _send_queue.ClearObject();
}

void UNetSend::InitData( NetSocket* socket, uint32 queuesize )
{
    Init();

    _net_socket = socket;
    _send_queue.Resize( queuesize );
}