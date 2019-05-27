#pragma once

#include "CoreMinimal.h"
#include "Define.generated.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

UENUM( BlueprintType )
enum class EThreadStatus : uint8
{
    New UMETA( DisplayName = "New" ),
    Runnable UMETA( DisplayName = "Runnable" ),
    Blocked UMETA( DisplayName = "Blocked" ),
    Waiting UMETA( DisplayName = "Waiting" ),
    TimedWaiting UMETA( DisplayName = 'TimedWaiting' ),
    Terminated UMETA( DisplayName = 'Terminated' )
};

UENUM( BlueprintType )
enum class ENetType : uint8
{
    Server UMETA( DisplayName = "Server" ),
    Client UMETA( DisplayName = "Client" ),
};