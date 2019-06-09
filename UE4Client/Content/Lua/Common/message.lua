
local CMessage = class( "CMessage" )

function CMessage:ctor()
    self._functions = {}
end

-- 添加消息处理
function CMessage:Add( msgid, msgname, cbfunc )
    if self._functions[ msgid ] ~= nil then
        _log:LogError( "msgid = "..msgid.." already exist!" )
        return
    end

    local data = {}
    data.msgname = msgname
    data.cbfunc = cbfunc
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
    local msg = _protobuf:Decode( data.msgname, msgdata, msglength );
    if msg == nil then
        return
    end
    table.print( msg )

    -- 回调函数
    data.cbfunc( msg )
end

return CMessage
