// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetConnect.generated.h"

class NetSocket;

UCLASS()
class UNetConnect : public UThread
{
    GENERATED_UCLASS_BODY()

public:
    ~UNetConnect();

    // start
    void StartService( NetSocket* socket, const FString& ip, uint32 port );

    // ֹͣ
    void StopService();

protected:
    // body
    virtual void ThreadBody();

private:
    // socket
    NetSocket* _net_socket = nullptr;

    // ip
    FString _ip;

    // port
    uint32 _port = 0u;
};
