#include "Public/Common/Utility.h"

uint8* FUtility::ReadFile(IPlatformFile& platformfile, FString& path, uint32& len)
{
    auto handle = platformfile.OpenRead( *path );
    if ( handle == nullptr )
    {
        return nullptr;
    }
    
    len = (uint32)handle->Size();
    
    uint8* buf = new uint8[len];
    handle->Read(buf, len);

    delete handle;
    return buf;
}
