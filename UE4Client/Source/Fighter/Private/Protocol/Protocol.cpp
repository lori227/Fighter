#include "Public/Protocol/Protocol.h"
#include "Public/Common/Macros.h"

DECLARE_LOG_CATEGORY_CLASS( LogProtocol, All, All );

bool Protocol::Parse( ::google::protobuf::Message* proto, const int8* data, uint32 length )
{
    if ( data == nullptr || length == 0 )
    {
        return true;
    }

    bool result = proto->ParseFromArray( data, length );
    if ( !result )
    {
        __LOG_ERROR__( LogProtocol, "message[{}] parse failed!", proto->GetTypeName() );
    }

    return result;
}