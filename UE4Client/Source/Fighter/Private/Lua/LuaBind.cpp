
#include "Public/Lua/LuaBind.h"
#include "Public/Headers.h"
#include "FighterInstance.h"

namespace slua
{
    LuaOwnedPtr<FLuaBind> FLuaBind::Create()
    {
        return new FLuaBind();
    }
    
    void FLuaBind::Connect( const char* ip, uint32 port )
    {
        FString strip = UTF8_TO_TCHAR( ip );
        UFighterInstance::Instance()->Connect( strip, port );
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    DefLuaClass( FLuaBind )
        DefLuaMethod(Connect, &FLuaBind::Connect)
    EndDef( FLuaBind, &FLuaBind::Create )
}

