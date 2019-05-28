#pragma once

#include "Runnable.h"
#include "Public/Common/Define.h"

class Thread : public FRunnable
{
public:
    Thread();
    virtual ~Thread();

    // init
    virtual bool Init() override;

    // run
    virtual uint32 Run() override;

    // stop
    virtual void Stop() override;

public:
    // start
    void Start( const FString& name, bool loop );

    // shutdown
    void Shutdown();

    void Suspend();
    void Resume();
    EThreadStatus GetThreadStatus();
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