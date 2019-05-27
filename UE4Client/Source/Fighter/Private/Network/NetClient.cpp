// Fill out your copyright notice in the Description page of Project Settings.


#include "NetClient.h"

NetClient::NetClient()
{
}

NetClient::~NetClient()
{
}


//void NetSocket::HandleNetEvent()
//{
//    auto event = PopNetEvent();
//    if ( event == nullptr )
//    {
//        return;
//    }
//
//    auto function = _event_function.Find( event->_type );
//    if ( function == nullptr )
//    {
//        __LOG_ERROR__( LogNetwork, "event type=[{}] error!", event->_type );
//        return;
//    }
//
//    // 网络时间回调
//    function->operator()( event );
//}