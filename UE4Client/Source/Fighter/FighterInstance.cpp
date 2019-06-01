// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterInstance.h"
#include "Public/Network/NetClient.h"
#include "Public/Lua/LuaModule.h"
#include "Public/Protocol/Protocol.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Fighter, "Fighter" );
DECLARE_LOG_CATEGORY_CLASS( LogInstance, All, All );

UFighterInstance* UFighterInstance::_this = nullptr;
UFighterInstance::UFighterInstance( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    _this = this;
}

UFighterInstance::~UFighterInstance()
{
    _this = nullptr;
    __SAFE_DELETE__( _net_client );
    __SAFE_DELETE__( _lua_module );
}

UFighterInstance* UFighterInstance::Instance()
{
    return _this;
}

void UFighterInstance::StartGameInstance()
{
    Super::StartGameInstance();
}

TStatId UFighterInstance::GetStatId() const
{
    return _statid;
}

ETickableTickType UFighterInstance::GetTickableTickType() const
{
    return HasAnyFlags( RF_ClassDefaultObject ) ? ETickableTickType::Never : ETickableTickType::Always;
}

void UFighterInstance::Init()
{
    Super::Init();
    __LOG_INFO__( LogInstance, "UFighterInstance::Init..." );
    
    // net work
    _net_client = new NetClient();
    _net_client->Init( TEXT( "client" ), ENetType::Client, 200, 200, false );
    _net_client->RegisterMessageFunction( this, &UFighterInstance::HandleNetMessage );
    _net_client->RegisterNetEventFunction( NetDefine::ConnectEvent, this, &UFighterInstance::OnNetClientConnectOk );
    _net_client->RegisterNetEventFunction( NetDefine::FailedEvent, this, &UFighterInstance::OnNetClientConnectFailed );
    _net_client->RegisterNetEventFunction( NetDefine::DisconnectEvent, this, &UFighterInstance::OnNetClientDisconnect );

    // lua
    _lua_module = new LuaModule();
    _lua_module->Init( ENetType::Client );
    _lua_module->Startup();
}

void UFighterInstance::Shutdown()
{
    // net
    if ( _net_client != nullptr )
    {
        _net_client->Shutdown();
        _net_client = nullptr;
    }
    
    // lua
    if ( _lua_module != nullptr )
    {
        _lua_module->Shutdown();
        _lua_module = nullptr;
    }

    Super::Shutdown();
}

void UFighterInstance::Tick( float deltatime )
{
    // net
    _net_client->Tick( deltatime );
    
    // lua
    _lua_module->Tick( deltatime );
}

/////////////////////////////////////////////////////////////////////////////////////
void UFighterInstance::Connect( FString& ip, uint32 port )
{
    _net_client->Connect( ip, port );
}

void UFighterInstance::OnNetClientConnectOk( int32 code, void* data )
{
    _lua_module->OnNetConnectOk( code ,data );
}

void UFighterInstance::OnNetClientConnectFailed( int32 code, void* data )
{
    _lua_module->OnNetFailed( code, data );
}

void UFighterInstance::OnNetClientDisconnect( int32 code, void* data )
{
    _lua_module->OnNetDisconnect( code, data );
}

void UFighterInstance::HandleNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    _lua_module->HandleNetMessage( msgid, data, length );
}
/////////////////////////////////////////////////////////////////////////////////////
