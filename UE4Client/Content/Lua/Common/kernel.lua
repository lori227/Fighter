local CKernel = class( "CKernel" )

function CKernel:ctor()
    -- id
    self._id = 0

    -- name
    self._name = 0

    -- 数据
    self._data = {}

    -- 回调函数
    self._add_function = {}
    self._update_function = {}
    self._remove_function = {}
end

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
function CKernel:RegisterAddDataFunction( dataname, callfunction )
    RegisterFunction( self._add_function, _define._kernel_name, dataname, callfunction )
end

function CKernel:RegisterAddObjectFunction( parentname, childname, callfunction )
    RegisterFunction( self._add_function, parentname, childname, callfunction )
end

function CKernel:CallAddFunction( parentname, childname, key, data )
    local parentdata = self._add_function[ parentname ]
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
function CKernel:RegisterRemoveDataFunction( dataname, callfunction )
    RegisterFunction( self._remove_function, _define._kernel_name, dataname, callfunction )
end

function CKernel:RegisterRemoveObjectFunction( parentname, childname, callfunction )
    RegisterFunction( self._remove_function, parentname, childname, callfunction )
end

function CKernel:CallRemoveFunction( parentname, childname, key, data )
    local parentdata = self._remove_function[ parentname ]
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
function CKernel:RegisterUpdateDataFunction( dataname, callfunction )
    RegisterFunction( self._update_function, _define._kernel_name, dataname, callfunction )
end

function CKernel:RegisterUpdateObjectFunction( parentname, childname, callfunction )
    RegisterFunction( self._update_function, parentname, childname, callfunction )
end

function CKernel:CallUpdateFunction( parentname, childname, key, oldvalue, newvalue )
    local parentdata = self._update_function[ parentname ]
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
function CKernel:InitData( id, data )
    self._id = id

end
---------------------------------------------------------
function CKernel:SyncUpdateData( data )
    
end
---------------------------------------------------------
function CKernel:SyncAddData( data )
   
end
---------------------------------------------------------
function CKernel:RemoveData( parentdata, key )
    local childdata = parentdata[ key ]
    if childdata == nil then
        return
    end

    -- 回调函数
    self:CallRemoveFunction( parentdata.name, childdata.name, key, childdata )

    -- 删除数据
    parentdata[ key ]= nil
end

function CKernel:SyncRemoveData( data )
    
end

---------------------------------------------------------
---------------------------------------------------------
-- 查找属性
function CKernel:FindData( childname )
    if childname == nil then
        return nil
    end

    return self._data[ childname ]
end

-- 获得属性值
function CKernel:GetDataValue( childname )
    local data = self:FindData( childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置属性值
function CKernel:SetDataValue( childname, value )
    if childname == nil then
        return
    end

    local data = self:FindData( childname )
    if data ~= nil then
        data.value = value
    else
        data = {}
        data.value = value
        self._data[ childname ] = data
    end
end

-- 查找对象属性
function CKernel:FindObjectData( parentname, childname )
    local parentdata = self:FindData( parentname )
    if parentdata == nil then
        return nil
    end

    if childname == nil then
        return nil
    end

    return parentdata[ childname ]
end

-- 获得对象属性值
function CKernel:GetObjectValue( parentname, childname )
    local data = self:FindObjectData( parentname, childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置对象属性值
function CKernel:SetObjectValue( parentname, childname, value )
    if parentname == nil or childname == nil then
        return
    end
    
    local parentdata = self:FindData( parentname )
    if parentdata == nil then
        parentdata = {}
        self._data[ parentname ] = parentdata
    end

    local childdata = parentdata[ childname ]
    if childdata == nil then
        childdata = {}
        parentdata[ childname ] = childdata
    end

    childdata.value = value
end

-- 查找集合属性
function CKernel:FindRecordData( parentname, key, childname )
    local parentdata = self:FindData( parentname )
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
function CKernel:GetRecordValue( parentname, key, childname )
    local data = self:FindRecordData( parentname, key, childname )
    if data == nil then
        return nil
    end

    return data.value
end

-- 设置集合属性值
function CKernel:SetRecordValue( parentname, key, childname, value )
    local data = self:FindRecordData( parentname, key, childname )
    if data == nil then
        return
    end

    data.value = value
end

return CKernel