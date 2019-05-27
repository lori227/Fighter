// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetConnect.generated.h"

class UNetSocket;

UCLASS()
class UNetConnect : public UThread
{
    GENERATED_UCLASS_BODY()

public:
    ~UNetConnect();

    // start
    void StartService( UNetSocket* socket, const FString& ip, uint32 port );

    // ֹͣ
    void StopService();

protected:
    // body
    virtual void ThreadBody();

private:
    // socket
    UNetSocket* _net_socket = nullptr;

    // ip
    FString _ip;

    // port
    uint32 _port = 0u;
};
