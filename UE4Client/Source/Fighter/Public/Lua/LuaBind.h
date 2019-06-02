// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "LuaVar.h"
#include "LuaObject.h"
#include "LuaCppBinding.h"
#include "LuaCppBindingPost.h"

namespace slua
{
    class FLuaBind
    {
        LuaClassBody()
    public:
        // create
        static LuaOwnedPtr<FLuaBind> Create();
        
        // content path
        static FString ProjectContentDir();
        
        // net connect
        static void Connect( const char* ip, uint32 port );
    };
}

