
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

--数据代理的枚举名
ProxyEnum = 
{
    NONE = "NONE",

    COMMON_PROMPT = "COMMON_PROMPT",
    CHECK_VERSION = "CHECK_VERSION",
    BATCH_UPDATE = "BATCH_UPDATE",
    SERVER_AUTH = "SERVER_AUTH",
    LOGIN = "LOGIN",
    PVP_MATCH = "PVP_MATCH",
    MAIN_CAMPSITE = "MAIN_CAMPSITE",
    PACK = "PACK",
	RECRUITMENT_OFFICE = "RECRUITMENT_OFFICE",
	GAME_SETTING = "GAME_SETTING",
    COMM_CONFIRM = "COMM_CONFIRM",
    ROLE_LIST = "ROLE_LIST",
    ROLE_INFORMATION = "ROLE_INFORMATION",
}

SetErrorIndex(ProxyEnum)


