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
    static UFighterInstance* _this;

    UPROPERTY( Transient )
    FString _account;

    UPROPERTY( Transient )
    uint32 _account_id = 0;

private:
    bool _enable_tick;
    TStatId _stat_id;
};