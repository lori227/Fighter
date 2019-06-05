
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

--职业偏向
DeviationEnum = 
{
    "偏向一：种族",
    "偏向二：行动方式",
    "偏向三：武器类型",
    "偏向四：无",
}

DeviationLockTextEnum = 
{
    "偏向一：招募所X级可解锁偏向",
    "偏向二：招募所X级可解锁偏向",
    "偏向三：招募所X级可解锁偏向",
    "偏向四：招募所X级可解锁偏向",
}

DeviationTextEnum = 
{
    {
        "无",
        "兽人",
        "人类",
        "精灵",
    },
    {  
        "无",
        "步行",
        "启程",
        "飞行",
    },                                                  
    {  
        "无",
        "剑",
        "斧",
    --    "枪",
    --    "弓",
    --    "仗",
    }, 
    {  
        "无",
        "无",
        "无",
        "无",
    --    "无",
    --    "无",
    --    "无",
    --    "无",
    }, 
}

SetErrorIndex(DeviationEnum)
SetErrorIndex(DeviationLockTextEnum)
SetErrorIndex(DeviationTextEnum)