
local M = {}

-- 函数列表
local functions = {}

-- 添加消息处理
function M.Add( msgid, msgname, callfunction )
    if functions[ msgid ] ~= nil then
        print( "msgid = "..msgid.." already exist!" )
        return
    end

    local data = {}
    data.msgname = msgname
    data.callfunction = callfunction
    functions[ msgid ] = data
end

-- 删除消息处理
function M.Remove( msgid )
    functions[ msgid ] = nil
end

-- 消息回调
function M.Call( msgid, msgdata, msglength )
    local data = functions[ msgid ]
    if data == nil then
        print( "msgid = "..msgid.." no function!" )
        return
    end

    -- 解析消息
    local msg, error = pbc.decode( data.msgname, msgdata, msglength );
    if msg == false then
        print( "msgname = "..data.msgname.." parse failed = "..error )
        return
    end

    -- 回调函数
    data.callfunction( msg )
end

-- 获得消息Id枚举
function M.GetFrameClientMsgId( name )
    return pbc.enum_id( "KFMsg.FrameClientProtocol", name )
end

function M.GetClientMsgId( name )
    return pbc.enum_id( "KFMsg.ClientProtocol", name )
end

return M