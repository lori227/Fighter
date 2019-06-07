local pbc = require "../Common/pbc"
local CProtobuf = class( "CProtobuf" )

function CProtobuf:ctor()
    
end

-- 初始化协议
function CProtobuf:LoadProtocol( protopath, protofiles )
	local protodir = string.format( "%s%s", FLuaBind.ContentDir(), protopath )
	for _, v in pairs( protofiles ) do
		local protofile = string.format( "%s/%s", protodir, v )
		pbc.register_file( protofile )
	end
end

-- 获得枚举
function CProtobuf:GetEnumId( type, name )
    local id = pbc.enum_id( type, name )
    if id == nil then
        _log:LogError( "enum=["..type.."] name=["..name.."] can't find!" )
    end

    return id
end

-- 获得消息Id
local msgidtype = 
{
    "KFMsg.ClientProtocol",
    "KFMsg.FrameClientProtocol",
}

function CProtobuf:GetMsgId( name )
    for _, v in pairs( msgidtype ) do  
        local id = pbc.enum_id( v, name )
        if id ~= nil then
            return id
        end
    end

    _log:LogError( "msgid=["..name.."] can't find!" )
    return nil
end

function CProtobuf:Decode( msgname, msgdata, msglength )
    local msg, error = pbc.decode( msgname, msgdata, msglength );
    if msg == false then
        _log:LogError( "msgname = "..msgname.." parse failed = "..error )
        return nil
    end

    return msg
end

function CProtobuf:Encode( msgname, msgtable )
    local str = pbc.encode( msgname, msgtable )
    if str == nil then
        _log:LogError( "msgname=["..msgname.."] encode failed!" )
        return nil
    end

    return str
end

return CProtobuf