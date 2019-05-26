#pragma once

#include "Runnable.h"
#include "Public/Common/Macros.h"
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
    void Start( const FString& name, bool loop = false );

    EThreadStatus GetThreadStatus();
    void Suspend();
    void Resume();
    void EnsureCompletion();

    void TaskSleep( float ParamSeconds );

protected:
    // 线程逻辑
    virtual uint32 ThreadBody();

    // 是否完成
    virtual bool IsFinished();

private:
    /**< 线程名 */
    FString _name;

    // 是否循环
    bool _loop;

    /**< 线程 */
    FRunnableThread* _runable;

    /**< 线程悬挂和唤醒事件 */
    FEvent* _suspended_event;

    /**< 线程状态 */
    EThreadStatus _status;
};