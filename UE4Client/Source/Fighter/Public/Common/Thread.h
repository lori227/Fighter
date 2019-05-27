﻿#pragma once

#include "Runnable.h"
#include "Public/Common/Define.h"
#include "Thread.generated.h"

UCLASS( Blueprintable )
class UThread : public UObject, public FRunnable
{
    GENERATED_UCLASS_BODY()
public:

    virtual ~UThread();

    // init
    virtual bool Init() override;

    // run
    virtual uint32 Run() override;

    // stop
    virtual void Stop() override;

public:
    // start
    void StartThread( const FString& name, bool loop );

    EThreadStatus GetThreadStatus();
    void Suspend();
    void Resume();
    void EnsureCompletion();

    void TaskSleep( float ParamSeconds );

protected:
    // 线程逻辑
    virtual void ThreadBody();

    // 是否完成
    virtual bool IsFinished();

private:
    /**< 线程名 */
    FString _name;

    // 是否循环
    bool _loop = false;

    /**< 线程 */
    FRunnableThread* _runable = nullptr;

    /**< 线程悬挂和唤醒事件 */
    FEvent* _suspended_event = nullptr;

    /**< 线程状态 */
    EThreadStatus _status = EThreadStatus::New;
};