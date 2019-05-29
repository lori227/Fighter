#pragma once

#include "FrameDefineMessage.pb.h"
#include "FrameCodeMessage.pb.h"
#include "FrameEnumMessage.pb.h"
#include "FrameMessage.pb.h"
#include "FrameClientMessage.pb.h"
#include "FrameServerMessage.pb.h"

#include "CodeMessage.pb.h"
#include "EnumMessage.pb.h"
#include "DefineMessage.pb.h"
#include "ClientMessage.pb.h"
#include "ServerMessage.pb.h"

#include "google/protobuf/util/json_util.h"
#include "CoreMinimal.h"

///////////////////////////////////////////////////////////////////////////////////
#define __PROTO_PARSE__( msgtype ) \
    msgtype msg;\
    if ( !Protocol::Parse( &msg, data, length ) )\
    {\
        return;\
    }
///////////////////////////////////////////////////////////////////////////////////

class Protocol
{
public:
    // 解析消息
    static bool Parse( ::google::protobuf::Message* proto, const int8* data, uint32 length );
};

