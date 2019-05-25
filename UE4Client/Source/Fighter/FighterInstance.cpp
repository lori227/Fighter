// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterInstance.h"

DECLARE_LOG_CATEGORY_CLASS( LogInstance, All, All );

UFighterInstance* UFighterInstance::s_This = nullptr;
UFighterInstance::UFighterInstance( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    s_This = this;
}

void UFighterInstance::StartGameInstance()
{
    Super::StartGameInstance();
}


inline bool UFighterInstance::IsTickable() const
{
	return m_EnableTick;
}

inline TStatId UFighterInstance::GetStatId() const
{
	return m_StatId;
}

void UFighterInstance::Init()
{
	m_Account = TEXT( "ssss" );
	m_AccountId = 1111;
	__LOG_INFO__( LogInstance, "UFighterInstance::Init..." );
}

void UFighterInstance::Shutdown()
{
}

void UFighterInstance::Tick( float DeltaTime )
{

}
