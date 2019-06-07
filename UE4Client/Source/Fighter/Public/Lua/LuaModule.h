// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "Public/Headers.h"

DECLARE_LOG_CATEGORY_CLASS( LogLua, All, All );

class LuaModule
{
public:
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
    
public:
    // lua path
    FString _lua_path;
private:
    // state
    slua::LuaState _state;
    
    // lua ok
    bool _is_lua_ok = false;
};
