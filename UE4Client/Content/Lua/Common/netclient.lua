local M = {}

-- 连接成功
local _connect_functions = {}

function M.AddConnect( name, callfunction )
    _connect_functions[ name ] = callfunction
end

function M.OnConnect( id, code )
    _log.LogInfo( "client=["..id.."] connect!" )

    for k, callfunction in pairs( _connect_functions ) do
        callfunction( id, code )
    end
end

-- 连接失败
local _failed_functions = {}
function M.AddFailed( name, callfunction )
    _failed_functions[ name ] = callfunction
end

function M.OnFailed( id, code )
    _log.LogError( "client=["..id.."] failed, code=["..code.."]!" )

    for k, callfunction in pairs( _failed_functions ) do
        callfunction( id, code )
    end
end

-- 断开连接
local _disconnect_functions = {}
function M.AddDisconenct( name, callfunction )
    _disconnect_functions[ name ] = callfunction
end

function M.OnDisconnect( id, code )
    _log.LogError( "client=["..id.."] disconnect, code=["..code.."]!" )

    for k, callfunction in pairs( _disconnect_functions ) do
        callfunction( id, code )
    end
end

-- 连接
function M.Connect( id, ip, port )
    FLuaBind.Connect( id, ip, port )
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