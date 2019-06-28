
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

--UI界面前后枚举
UIViewZOrderEnum = 
{
    NONE = "NONE",

    BASE = 10000 * 1,       --基础层
    MIDDLE = 10000 * 2,     --中间层
    HIGH = 10000 * 3,       --高层
    PROMPT = 10000 * 4,     --提示层
    GUIDE = 10000 * 5,      --引导层

    Top = 10000 * 100,      --最高层级
}

SetErrorIndex(UIViewZOrderEnum)

