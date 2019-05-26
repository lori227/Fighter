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
    // �߳��߼�
    virtual uint32 ThreadBody();

    // �Ƿ����
    virtual bool IsFinished();

private:
    /**< �߳��� */
    FString _name;

    // �Ƿ�ѭ��
    bool _loop;

    /**< �߳� */
    FRunnableThread* _runable;

    /**< �߳����Һͻ����¼� */
    FEvent* _suspended_event;

    /**< �߳�״̬ */
    EThreadStatus _status;
};