
local ToStr = function(value)
    if (type(value) == "string") then
        return "\"" .. value .. "\""
    end

    return tostring(value)
end

local SetErrorIndex = function(t)
    setmetatable(t, {
        __index = function(t, k)
            error("Can\'t index not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
        __newindex = function(t, k, v)
            error("Can\'t newindex not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
    })
end

--protobuf枚舉
ProtobufEnum = 
{
    NONE = "NONE",

    MSG_RESULT_DISPLAY      = 1,

    MSG_LOGIN_REQ           = 100,
    MSG_LOGIN_ACK           = 101,

    MSG_START_MATCH_REQ     = 3001,     --开始匹配 
    MSG_CANCEL_MATCH_REQ    = 3002,     --取消匹配
    MSG_INFORM_MATCH_RESULT = 3003,     --通知匹配结果
    MSG_AFFIRM_MATCH_REQ    = 3004,     --请求确认匹配
    MSG_INFORM_BATTLE_REQ   = 3005,     --服务器通知战场信息
    MSG_INFORM_BATTLE_ACK   = 3006,     --客户端确认战场信息
    MSG_FINISH_ROOM_REQ     = 3007,     --服务器通知战场房间结束
}

SetErrorIndex(ProtobufEnum)


