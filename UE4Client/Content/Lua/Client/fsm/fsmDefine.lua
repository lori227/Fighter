--有限状态机定义的常量

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

--当前游戏模式状态枚举
FSMStateStatusEnum =
{
    NONE = "NONE",

    RUNNING = "RUNNING",
    TERMINATED = "TERMINATED",
}

SetErrorIndex(FSMStateStatusEnum)

--栈的操作枚举
FSMStackOpEnum =
{
    NONE = "NONE",

    SET = "SET",
    PUSH = "PUSH",
    POP = "POP",
}
SetErrorIndex(FSMStackOpEnum)

