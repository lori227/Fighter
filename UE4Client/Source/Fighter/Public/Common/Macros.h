// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Library/fmt/fmt.h"

#ifndef __FORMAT__
    #define __FORMAT__( myfmt, ... ) fmt::format( fmt(myfmt), ##__VA_ARGS__ )
#endif

#ifndef __LOG__
#define __LOG__( name, level, format, ... ) \
    {\
        auto temp = __FORMAT__( format, ##__VA_ARGS__ );\
        FString ftemp( temp.c_str() );\
        UE_LOG( name, level, TEXT( "%s" ), *ftemp );\
    }
#endif

#ifndef __LOG_INFO__
    #define  __LOG_INFO__( name, format, ... ) __LOG__( name, Log, format, ##__VA_ARGS__ )
#endif

#ifndef __LOG_WARN__
    #define  __LOG_WARN__( name, format, ... ) __LOG__( name, Warning, format, ##__VA_ARGS__ )
#endif

#ifndef __LOG_ERROR__
    #define  __LOG_ERROR__( name, format, ... ) __LOG__( name, Error, format, ##__VA_ARGS__ )
#endif
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SAFE_DELETE__
    #define  __SAFE_DELETE__( p ) if ( p != nullptr ){ delete p; p = nullptr;}
#endif

#ifndef __SAFE_DELETE_FUNCTION__
    #define  __SAFE_DELETE_FUNCTION__( p, function ) if ( p != nullptr ){ function( p ); p = nullptr;}
#endif