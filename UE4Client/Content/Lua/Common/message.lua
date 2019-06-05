
local M = {}

-- 函数列表
local functions = {}

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

function M.Remove( msgid )
    functions[ msgid ] = nil
end

function M.Call( msgid, msgdata, msglength )
    local data = functions[ msgid ]
    if data == nil then
        print( "msgid = "..msgid.." no function!" )
        return
    end

    -- 解析消息
    local msg = {};
    if msg == nil then
        print( "msgname = "..data.msgname.." parse failed!" )
        return
    end

    -- 回调函数
    data.callfunction( msg )
end

return M