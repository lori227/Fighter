// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "Public/Tickable.h"
#include "Engine/GameInstance.h"
#include "FighterInstance.generated.h"

/**
 * @brief 游戏实例
 * 游戏全局的管理器
 */

class NetEvent;
class NetClient;

UCLASS( BlueprintType, Blueprintable )
class UFighterInstance : public UGameInstance, public FTickableGameObject
{
    GENERATED_UCLASS_BODY()

public:
    ~UFighterInstance();
    static UFighterInstance* GetInstance();

    /** Starts the GameInstance state machine running */
    virtual void StartGameInstance() override;

    // init
    virtual void Init() override;

    // shutdown
    virtual void Shutdown() override;

    // tick
    virtual void Tick( float DeltaTime ) override;
    inline bool IsTickable() const;
    inline TStatId GetStatId() const;


protected:
    // 连接成功时间
    void OnNetClientConnectOk( const NetEvent* event );

    // 连接失败
    void OnNetClientConnectFailed( const NetEvent* event );

    // 处理消息函数
    void HandleNetMessage( uint32 msgid, const int8* data, uint32 length );

protected:
    static UFighterInstance* _this;

    // 网络客户端
    NetClient* _net_client = nullptr;

    TStatId m_TStatId;

};