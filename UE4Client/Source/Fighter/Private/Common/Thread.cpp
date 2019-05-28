#include "Public/Common/Thread.h"
#include "Event.h"
#include "RunnableThread.h"
#include "Public/Common/Macros.h"

Thread::Thread()
{
    _suspended_event = FPlatformProcess::GetSynchEventFromPool();
}

Thread::~Thread()
{
    __SAFE_DELETE__( _runable );
    __SAFE_DELETE_FUNCTION__( _suspended_event, FPlatformProcess::ReturnSynchEventToPool );
}

bool Thread::Init()
{
    _status = EThreadStatus::New;
    return true;
}

uint32 Thread::Run()
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
void Thread::ThreadBody()
{

}

void Thread::Stop()
{
    _loop = false;
}

void Thread::Shutdown()
{
    Stop();
    if ( _runable != nullptr )
    {
        _runable->Kill( true );
    }
}

//bool UThread::IsFinished_Implementation()
bool Thread::IsFinished()
{
    return _status == EThreadStatus::Terminated;
}

void Thread::Start( const FString& name, bool loop )
{
    _name = name;
    _loop = loop;
    _runable = FRunnableThread::Create( this, *_name );
}

EThreadStatus Thread::GetThreadStatus()
{
    return _status;
}

void Thread::Suspend()
{
    _suspended_event->Wait();
    _status = EThreadStatus::Waiting;
}

void Thread::Resume()
{
    _suspended_event->Trigger();
    _status = EThreadStatus::Runnable;
}

void Thread::TaskSleep( float ParamSeconds )
{
    FPlatformProcess::Sleep( ParamSeconds );
}

