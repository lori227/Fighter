// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Headers.h"
#include "Public/Tickable.h"
#include "Engine/GameInstance.h"
#include "FighterInstance.generated.h"

/**
 * @brief 游戏实例
 * 游戏全局的管理器
 */

class NetClient;
class LuaModule;
UCLASS( BlueprintType, Blueprintable )
class UFighterInstance : public UGameInstance, public FTickableGameObject
{
    GENERATED_UCLASS_BODY()

public:
    ~UFighterInstance();
    static UFighterInstance* Instance();

    /** Starts the GameInstance state machine running */
    virtual void StartGameInstance() override;

    // init
    virtual void Init() override;

    // shutdown
    virtual void Shutdown() override;

    //////////////////////////////////////////////////////////////////////////////

    // tick
    virtual TStatId GetStatId() const;
    virtual void Tick( float deltatime ) override;
    virtual ETickableTickType GetTickableTickType() const;
    
public:
    // net connect
    void Connect( FString& ip, uint32 port );
    
    // net send
    bool Send( uint32 msgid, const int8* data, uint32 length );
    
protected:

    // 连接成功
    void OnNetClientConnectOk( int32 code, void* data );

    // 连接失败
    void OnNetClientConnectFailed( int32 code, void* data );

    // 连接断开
    void OnNetClientDisconnect( int32 code, void* data );

    // 处理消息函数
    void HandleNetMessage( uint32 msgid, const int8* data, uint32 length );

public:    
    // 网络客户端
    NetClient* _net_client = nullptr;
    
    // lua
    LuaModule* _lua_module = nullptr;
    
protected:
    static UFighterInstance* _this;

private:

    TStatId _statid;

};
