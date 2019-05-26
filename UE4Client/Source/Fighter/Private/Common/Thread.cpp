#include "Public/Common/Thread.h"
#include "Event.h"
#include "RunnableThread.h"

UThread::UThread( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
    , _loop( false )
    , _runable( nullptr )
    , _status( EThreadStatus::New )
{
    _suspended_event = FPlatformProcess::GetSynchEventFromPool();
}

UThread::~UThread()
{
    __SAFE_DELETE__( _runable );
    __SAFE_DELETE_FUNCTION__( _suspended_event, FPlatformProcess::ReturnSynchEventToPool );
}

bool UThread::Init()
{
    _status = EThreadStatus::New;
    return true;
}

uint32 UThread::Run()
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
uint32 UThread::ThreadBody()
{
    return 0;
}

void UThread::Stop()
{
    _loop = false;
}

//bool UThread::IsFinished_Implementation()
bool UThread::IsFinished()
{
    return _status == EThreadStatus::Terminated;
}

void UThread::Start( const FString& name, bool loop /* = false */ )
{
    _name = name;
    _loop = loop;
    _runable = FRunnableThread::Create( this, *_name );
}

EThreadStatus UThread::GetThreadStatus()
{
    return _status;
}

void UThread::EnsureCompletion()
{
    if ( _runable != nullptr )
    {
        Stop();
        _runable->Kill( true );
        _runable->WaitForCompletion();
    }
}

void UThread::Suspend()
{
    _suspended_event->Wait();
    _status = EThreadStatus::Waiting;
}

void UThread::Resume()
{
    _suspended_event->Trigger();
    _status = EThreadStatus::Runnable;
}

void UThread::TaskSleep( float ParamSeconds )
{
    FPlatformProcess::Sleep( ParamSeconds );
}

