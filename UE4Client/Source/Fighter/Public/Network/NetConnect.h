// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Headers.h"

class FNetSocket;

class FNetConnect : public FThread
{
public:
    FNetConnect( FNetSocket* socket );

    // start
    void StartService( const FString& ip, uint32 port );

    // stop
    void StopService();

protected:
    // body
    virtual void ThreadBody();

private:
    // socket
    FNetSocket* _net_socket = nullptr;

    // ip
    FString _ip;

    // port
    uint32 _port = 0u;
};
