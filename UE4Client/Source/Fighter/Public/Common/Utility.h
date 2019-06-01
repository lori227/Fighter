#pragma once

#include "CoreMinimal.h"

class FUtility
{
public:
    // read file, buff delete at call function
    static uint8* ReadFile( IPlatformFile& platformfile, FString path, uint32& len );
};
