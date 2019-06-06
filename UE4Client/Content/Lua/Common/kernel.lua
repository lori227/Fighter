
local M = {}

-- 数据信息
M._id = 0
M._name = ""
M._data = {}

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
---------------------------------------------------------

local function UpdateAllData( data )
end

function M.UpdateData( data )
    UpdateAllData( data )
end
---------------------------------------------------------

local function AddAllData( data )

end

function M.AddData( data )
    AddAllData( data )
end
---------------------------------------------------------

local function RemoveAllData( data )

end

local function RemoveData( parentdata, key )
    local childdata = parentdata[ key ]
    if childdata == nil then
        return
    end

    -- 回调函数
    M.CallRemoveFunction( parentdata.name, childdata.name, key, childdata )

    -- 删除数据
    parentdata[ key ]= nil
end

function M.RemoveData( data )
    RemoveAllData( data )
end

---------------------------------------------------------
---------------------------------------------------------
-- 查找属性
function M.FindData( childname )
    if childname == nil then
        return nil
    end

    return M._data[ childname ]
end

-- 获得属性值
function M.GetDataValue( childname )
    local data = M.FindData( childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置属性值
function M.SetDataValue( childname, value )
    if childname == nil then
        return
    end

    local data = M.FindData( childname )
    if data ~= nil then
        data.value = value
    else
        data = {}
        data.value = value
        M._data[ childname ] = data
    end
end

-- 查找对象属性
function M.FindObjectData( parentname, childname )
    local parentdata = M.FindData( parentname )
    if parentdata == nil then
        return nil
    end

    if childname == nil then
        return nil
    end

    return parentdata[ childname ]
end

-- 获得对象属性值
function M.GetObjectValue( parentname, childname )
    local data = M.FindObjectData( parentname, childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置对象属性值
function M.SetObjectValue( parentname, childname, value )
    if parentname == nil or childname == nil then
        return
    end
    
    local parentdata = M.FindData( parentname )
    if parentdata == nil then
        parentdata = {}
        M._data[ parentname ] = parentdata
    end

    local childdata = parentdata[ childname ]
    if childdata == nil then
        childdata = {}
        parentdata[ childname ] = childdata
    end

    childdata.value = value
end

-- 查找集合属性
function M.FindRecordData( parentname, key, childname )
    local parentdata = M.FindData( parentname )
    if parentdata == nil then
        return nil
    end

    local childdata = parentdata[ key ]
    if childdata == nil then
        return nil
    end

    if childname == nil then
        return childdata
    end

    return childdata[ childname ]
end

-- 获得集合属性值
function M.GetRecordValue( parentname, key, childname )
    local data = M.FindRecordData( parentname, key, childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置集合属性值
function M.SetRecordValue( parentname, key, childname, value )
    local data = M.FindRecordData( parentname, key, childname )
    if data == nil then
        return
    end

    data.value = value
end

return M