
local M = {}

-- 玩家id
local _id = {}

-- 数据信息
local _data = {}

-- 回调函数
local _add_function = {}
local _update_function = {}
local _remove_function = {}

--------------------------------------------------------------------
--------------------------------------------------------------------
local function RegisterFunction( functions, parentname, childname, callfunction )
    local childdata = {}
    childdata.callfunction = callfunction

    local parentdata = functions[ parentname ]
    if parentdata == nil then
        local data = {}
        data[ childname ] = childdata
        functions[ parentname ] = data
    else
        parentdata[ childname ] = childdata
    end
end

--------------------------------------------------------------------
-- 添加属性回调
function M.RegisterAddDataFunction( dataname, callfunction )
    RegisterFunction( _add_function, _define._kernel_name, dataname, callfunction )
end

function M.RegisterAddObjectFunction( parentname, childname, callfunction )
    RegisterFunction( _add_function, parentname, childname, callfunction )
end

function M.CallAddFunction( parentname, childname, key, data )
    local parentdata = _add_function[ parentname ]
    if parentdata == nil then
        return
    end

    local childdata = parentdata[ childname ]
    if childdata == nil then
        return
    end 

    childdata.callfunction( key, data )
end
--------------------------------------------------------------------
-- 删除属性回调
function M.RegisterRemoveDataFunction( dataname, callfunction )
    RegisterFunction( _remove_function, _define._kernel_name, dataname, callfunction )
end

function M.RegisterRemoveObjectFunction( parentname, childname, callfunction )
    RegisterFunction( _remove_function, parentname, childname, callfunction )
end

function M.CallRemoveFunction( parentname, childname, key, data )
    local parentdata = _remove_function[ parentname ]
    if parentdata == nil then
        return
    end

    local childdata = parentdata[ childname ]
    if childdata == nil then
        return
    end 

    childdata.callfunction( key, data )
end

--------------------------------------------------------------------
-- 更新属性回调
function M.RegisterUpdateDataFunction( dataname, callfunction )
    RegisterFunction( _update_function, _define._kernel_name, dataname, callfunction )
end

function M.RegisterUpdateObjectFunction( parentname, childname, callfunction )
    RegisterFunction( _update_function, parentname, childname, callfunction )
end

function M.CallUpdateFunction( parentname, childname, key, oldvalue, newvalue )
    local parentdata = _update_function[ parentname ]
    if parentdata == nil then
        return
    end

    local childdata = parentdata[ childname ]
    if childdata == nil then
        return
    end 

    childdata.callfunction( key, oldvalue, newvalue )
end
--------------------------------------------------------------------
--------------------------------------------------------------------
function M.InitData( id, data )
    M._id = id

    

end

return M