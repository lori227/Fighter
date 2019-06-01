// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "Public/Headers.h"

class LuaModule
{
public:
    LuaModule();
    ~LuaModule();
    
    // int
    void Init( ENetType nettype );
    
    // startup
    void Startup();
    
    // tick
    void Tick( float deltatime );
    
    // shutdown
    void Shutdown();
    
public:
    // conenct ok
    void OnNetConnectOk( int32 code, void* data );
    
    // connect failed
    void OnNetFailed( int32 code, void* data );
    
    // disconnect
    void OnNetDisconnect( int32 code, void* data );
    
    // handle message
    void HandleNetMessage( uint32 msgid, const int8* data, uint32 length );
    
private:
    // state
    slua::LuaState _state;
    
    // main file
    std::string _main_file;
    
    // lua ok
    bool _is_lua_ok;
};
