local M = {}

-- 连接
function M.Connect( ip, port )
    FLuaBind.Connect( ip, port )
end

-- 删除消息处理
function M.Send( msgid, msgname, msgtable )
    if msgid == nil then
        _log.LogError( "msgname=["..msgname.."] msgid is nil!" )
        return false
    end

    local str = _pbc.encode( msgname, msgtable )
    if str == nil then
        _log.LogError( "msgname=["..msgname.."] encode failed!" )
        return false
    end

    local ok = FLuaBind.Send( msgid, str, #str )
    if ok == false then
        _log.LogError( "send msgid =["..msgid.."] failed!" )
        return false
    end

    return true
end

return M