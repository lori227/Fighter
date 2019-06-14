#include "Public/Common/Thread.h"
#include "Event.h"
#include "RunnableThread.h"
#include "Public/Common/Macros.h"

FThread::FThread()
{
    _suspended_event = FPlatformProcess::GetSynchEventFromPool();
}

FThread::~FThread()
{
    __SAFE_DELETE__( _runable );
    __SAFE_DELETE_FUNCTION__( _suspended_event, FPlatformProcess::ReturnSynchEventToPool );
}

bool FThread::Init()
{
    _status = EThreadStatus::New;
    return true;
}

uint32 FThread::Run()
{
    _status = EThreadStatus::Runnable;

    do
    {
        ThreadBody();
        FPlatformProcess::Sleep( 0.02f );
    } while ( _loop );

    _status = EThreadStatus::Terminated;
    return 0u;
}

// int32 UThread::ThreadBody_Implementation()
void FThread::ThreadBody()
{

}

void FThread::Stop()
{
    _loop = false;
}

void FThread::Shutdown()
{
    Stop();
    if ( _runable != nullptr )
    {
        _runable->Kill( true );
    }
}

//bool UThread::IsFinished_Implementation()
bool FThread::IsFinished()
{
    return _status == EThreadStatus::Terminated;
}

void FThread::Start( const FString& name, bool loop )
{
    _name = name;
    _loop = loop;
    _runable = FRunnableThread::Create( this, *_name );
}

EThreadStatus FThread::GetThreadStatus()
{
    return _status;
}

void FThread::Suspend()
{
    _suspended_event->Wait();
    _status = EThreadStatus::Waiting;
}

void FThread::Resume()
{
    _suspended_event->Trigger();
    _status = EThreadStatus::Runnable;
}

void FThread::TaskSleep( float ParamSeconds )
{
    FPlatformProcess::Sleep( ParamSeconds );
}

