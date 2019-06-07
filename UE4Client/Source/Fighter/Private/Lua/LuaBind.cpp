
#include "Public/Lua/LuaBind.h"
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
    
    void FLuaBind::Connect( const int8* ip, uint32 port )
    {
        FString strip = UTF8_TO_TCHAR( ip );
        UFighterInstance::Instance()->Connect( strip, port );
    }
    
    bool FLuaBind::Send( uint32 msgid, const int8* data, uint32 length )
    {
        return UFighterInstance::Instance()->Send( msgid, data, length );
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    DefLuaClass( FLuaBind )
        DefLuaMethod(ContentDir, &FLuaBind::ProjectContentDir)
        DefLuaMethod(Connect, &FLuaBind::Connect)
    EndDef( FLuaBind, &FLuaBind::Create )
}

