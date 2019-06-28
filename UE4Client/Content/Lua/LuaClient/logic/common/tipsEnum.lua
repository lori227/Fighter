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

TipsEnum = 
{
    EQUIPMENT   = 1,        --装备
    SKILL       = 2,        --技能
    BUFF        = 3,        --BUFF
    EXPLAIN     = 4,        --说明
}

SetErrorIndex(TipsEnum)