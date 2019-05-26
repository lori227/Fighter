// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterInstance.h"
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Fighter, "Fighter" );
DECLARE_LOG_CATEGORY_CLASS( LogInstance, All, All );

UFighterInstance* UFighterInstance::_this = nullptr;
UFighterInstance::UFighterInstance( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    _this = this;
}

void UFighterInstance::StartGameInstance()
{
    Super::StartGameInstance();
}


inline bool UFighterInstance::IsTickable() const
{
    return _enable_tick;
}

inline TStatId UFighterInstance::GetStatId() const
{
    return _stat_id;
}

void UFighterInstance::Init()
{
    _account = TEXT( "ssss" );
    _account_id = 1111;
    __LOG_INFO__( LogInstance, "UFighterInstance::Init..." );
}

void UFighterInstance::Shutdown()
{
}

void UFighterInstance::Tick( float DeltaTime )
{
    //ClientSocket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, TEXT( "default" ), false );

}
