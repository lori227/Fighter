
#include "Public/Lua/LuaBind.h"
#include "Public/Lua/LuaModule.h"
#include "Public/Headers.h"
#include "FighterInstance.h"
#include "Paths.h"

namespace slua
{
    LuaOwnedPtr<FLuaBind> FLuaBind::Create()
    {
        return new FLuaBind();
    }
    
    FString FLuaBind::ProjectContentDir()
    {
        return FPaths::ProjectContentDir();
    }
    
    void FLuaBind::Connect( uint64 id, const char* ip, uint32 port )
    {
        FString strip = UTF8_TO_TCHAR( ip );
        UFighterInstance::Instance()->Connect( id, strip, port );
    }
    
    bool FLuaBind::Send( uint32 msgid, const char* data, uint32 length )
    {
        return UFighterInstance::Instance()->Send( msgid, (const int8*)data, length );
    }
    
    void FLuaBind::LogContent( uint32 level, const char* content )
    {
        switch( level )
        {
            case ELogVerbosity::Log:
                __LOG_INFO__( LogLua, "{}", content );
                break;
            case ELogVerbosity::Warning:
                __LOG_WARN__( LogLua, "{}", content );
                break;
            case ELogVerbosity::Error:
                __LOG_ERROR__( LogLua, "{}", content );
                break;
        }
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    DefLuaClass( FLuaBind )
        DefLuaMethod( ContentDir, &FLuaBind::ProjectContentDir )
        DefLuaMethod( Log, &FLuaBind::LogContent )
        DefLuaMethod( Connect, &FLuaBind::Connect )
        DefLuaMethod( Send, &FLuaBind::Send )
    EndDef( FLuaBind, &FLuaBind::Create )
}

