local CNetClient = class( "CNetClient" )

function CNetClient:ctor()
    -- 连接成功回调函数列表
    self._connect_functions = {}

    -- 连接失败回调函数列表
    self._failed_functions = {}

    -- 连接断开回调函数列表
    self._disconnect_functions = {}
end

-- 连接成功
function CNetClient:AddConnect( name, cbfunc )
    self._connect_functions[ name ] = cbfunc
end

function CNetClient:OnConnect( id, code )
    _log:LogInfo( "client=["..id.."] connect!" )

    for k, cbfunc in pairs( self._connect_functions ) do
        cbfunc( id, code )
    end
end

-- 连接失败
function CNetClient:AddFailed( name, cbfunc )
    self._failed_functions[ name ] = cbfunc
end

function CNetClient:OnFailed( id, code )
    _log:LogError( "client=["..id.."] failed, code=["..code.."]!" )

    for k, cbfunc in pairs( self._failed_functions ) do
        cbfunc( id, code )
    end
end

-- 断开连接
function CNetClient:AddDisconenct( name, cbfunc )
    self._disconnect_functions[ name ] = cbfunc
end

function CNetClient:OnDisconnect( id, code )
    _log:LogError( "client=["..id.."] disconnect, code=["..code.."]!" )

    for k, cbfunc in pairs( self._disconnect_functions ) do
        cbfunc( id, code )
    end
end

-- 连接
function CNetClient:Connect( id, ip, port )
    FLuaBind.Connect( id, ip, port )
end

-- 删除消息处理
function CNetClient:Send( msgid, msgname, msgtable )
    if msgid == nil then
        _log:LogError( "msgname=["..msgname.."] msgid is nil!" )
        return false
    end

    local str = _protobuf:Encode( msgname, msgtable )
    if str == nil then
        return false
    end

    local ok = FLuaBind.Send( msgid, str, #str )
    if ok == false then
        _log:LogError( "send msgid =["..msgid.."] failed!" )
        return false
    end

    return true
end

return CNetClient