// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"

class NetSocket;

class NetConnect : public Thread
{
public:
    NetConnect( NetSocket* socket );

    // start
    void StartService( const FString& ip, uint32 port );

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
