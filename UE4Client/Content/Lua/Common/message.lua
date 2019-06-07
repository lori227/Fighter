
local CMessage = class( "CMessage" )

function CMessage:ctor()
    self._functions = {}
end

-- 初始化协议
function CMessage:LoadProtocol( protofiles )
	local protodir = string.format( "%sLua/Protocol", FLuaBind.ContentDir() )
	for _, v in pairs( protofiles ) do
		local protofile = string.format( "%s/%s", protodir, v )
		_pbc.register_file(protofile)
	end
end

-- 添加消息处理
function CMessage:Add( msgid, msgname, callfunction )
    if self._functions[ msgid ] ~= nil then
        _log:LogError( "msgid = "..msgid.." already exist!" )
        return
    end

    local data = {}
    data.msgname = msgname
    data.callfunction = callfunction
    self._functions[ msgid ] = data
end

-- 删除消息处理
function CMessage:Remove( msgid )
    self._functions[ msgid ] = nil
end

-- 消息回调
function CMessage:Call( msgid, msgdata, msglength )
    local data = self._functions[ msgid ]
    if data == nil then
        _log:LogError( "msgid = "..msgid.." no function!" )
        return
    end

    -- 解析消息
    local msg, error = _pbc.decode( data.msgname, msgdata, msglength );
    if msg == false then
        _log:LogError( "msgname = "..data.msgname.." parse failed = "..error )
        return
    end

    -- 回调函数
    data.callfunction( msg )
end

-- 获得消息Id枚举
function CMessage:GetFrameClientMsgId( name )
    return _pbc.enum_id( "KFMsg.FrameClientProtocol", name )
end

function CMessage:GetClientMsgId( name )
    return _pbc.enum_id( "KFMsg.ClientProtocol", name )
end


return CMessage
