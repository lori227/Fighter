--游戏逻辑定义的常量

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


GameFSMStateIdEnum =
{
    NONE = "NONE",

    CHECK_VERSION = "CHECK_VERSION",        --检测版本
    BATCH_UPDATE = "BATCH_UPDATE",          --补丁更新
    SERVER_AUTH = "SERVER_AUTH",            --服务器验证
    LOGIN = "LOGIN",                        --登陆
    PVP_MATCH = "PVP_MATCH",                --PvP匹配
    MAIN_CAMPSITE = "MAIN_CAMPSITE",        --主营地
   
}
SetErrorIndex(GameFSMStateIdEnum)
