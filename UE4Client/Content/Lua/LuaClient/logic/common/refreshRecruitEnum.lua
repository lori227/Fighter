
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

--招募刷新枚举
RefreshRecruitEnum =
{
    UnknowRefresh   = 0,        --无效

    RefreshByFree   = 1,        --免费刷新
    RefreshByCount  = 2,        --使用次数刷新
    RefreshByCost   = 3,        --使用资源花费刷新
}

SetErrorIndex(RefreshRecruitEnum)
