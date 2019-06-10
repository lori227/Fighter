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
local function RegisterFunction( functions, parentname, childname, cbfunc )
    local childdata = {}
    childdata.cbfunc = cbfunc

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
function CKernel:RegisterAddDataFunction( dataname, cbfunc )
    RegisterFunction( self._add_function, _define._kernel_name, dataname, cbfunc )
end

function CKernel:RegisterAddObjectFunction( parentname, childname, cbfunc )
    RegisterFunction( self._add_function, parentname, childname, cbfunc )
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

    childdata.cbfunc( key, data )
end
--------------------------------------------------------------------
-- 删除属性回调
function CKernel:RegisterRemoveDataFunction( dataname, cbfunc )
    RegisterFunction( self._remove_function, _define._kernel_name, dataname, cbfunc )
end

function CKernel:RegisterRemoveObjectFunction( parentname, childname, cbfunc )
    RegisterFunction( self._remove_function, parentname, childname, cbfunc )
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

    childdata.cbfunc( key, data )
end

--------------------------------------------------------------------
-- 更新属性回调
function CKernel:RegisterUpdateDataFunction( dataname, cbfunc )
    RegisterFunction( self._update_function, _define._kernel_name, dataname, cbfunc )
end

function CKernel:RegisterUpdateObjectFunction( parentname, childname, cbfunc )
    RegisterFunction( self._update_function, parentname, childname, cbfunc )
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

    childdata.cbfunc( key, oldvalue, newvalue )
end
--------------------------------------------------------------------
--------------------------------------------------------------------
local function ParseData( data, pbdata )
    for k, v in pairs( pbdata ) do
        if k == "pbobject" then
            for _, pbobject in pairs( v ) do
                data[ pbobject.key ] = {}
                ParseData( data[ pbobject.key ], pbobject.value )
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs( v ) do
                data[ pbrecord.key ] = {}

                for k, pbobjects in pairs( pbrecord.value ) do
                    for _, pbobject in pairs( pbobjects )do
                        data[ pbrecord.key ][ pbobject.key ] = {}
                        ParseData( data[ pbrecord.key ][ pbobject.key ], pbobject.value )
                    end
                end
            end
        elseif k == "pbarray" then
            for _, pbarray in pairs( v ) do
                data[ pbarray.key ] = {}
                for k, pbuint64s in pairs( pbarray.value )  do
                    for _, pbuint64 in pairs( pbuint64s ) do
                        data[ pbarray.key ][pbuint64.key] = pbuint64.value
                    end
                end
            end
        else
            for _, pbvalue in pairs( v ) do
                data[ pbvalue.key ] = pbvalue.value
            end
        end
    end
end

function CKernel:InitData( id, pbdata )
    self._id = id

    -- 解析数据
    ParseData( self._data, pbdata )
end

---------------------------------------------------------
local function UpdateData( dataname, datakey, data, pbdata )
    for k, v in pairs( pbdata ) do
        if k == "pbobject" then
            for _, pbobject in pairs( v ) do
                data[ pbobject.key ] = {}
                UpdateData( pbobject.key, 0, data[ pbobject.key ], pbobject.value )
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs( v ) do
                if data[ pbrecord.key ] == nil then
                    data[ pbrecord.key ] = {}
                end
                
                for k, pbobjects in pairs( pbrecord.value ) do
                    for _, pbobject in pairs( pbobjects ) do
                        local childdata = data[ pbrecord.key ][ pbobject.key ]
                        if childdata ~= nil then
                            UpdateData( pbrecord.key, pbobject.key, childdata, pbobject.value )
                        end
                    end
                end
            end
        elseif k == "pbarray" then
            for _, pbarray in pairs( v ) do
                data[ pbarray.key ] = {}
                for _, pbuint64 in pairs( pbarray.value ) do
                    local oldvalue = data[ pbarray.key ][pbuint64.key] or 0
                    data[ pbarray.key ][pbuint64.key] = pbuint64.value
                    
                    -- 回调逻辑
                    _kernel:CallUpdateFunction( dataname, pbarray.key, datakey, oldvalue, pbhnt64.value )
                end
            end
        else
            for _, pbvalue in pairs( v ) do
                local oldvalue = data[ pbvalue.key ] or 0
                data[ pbvalue.key ] = pbvalue.value

                -- 回调逻辑
                 _kernel:CallUpdateFunction( dataname, pbvalue.key, datakey, oldvalue, pbvalue.value )
            end   
        end
    end
end

function CKernel:SyncUpdateData( data )
    -- 更新数据
    UpdateData( _define._kernel_name, 0, self._data, data )
end
---------------------------------------------------------
local function AddData( parentname, data, pbdata )
    for k, v in pairs( pbdata ) do
        if k == "pbobject" then
            for _, pbobject in pairs( v ) do
                if data[ pbobject.key ] == nil then
                    data[ pbobject.key ] = {}
                end

                AddData( pbobject.key, data[ pbobject.key ], pbobject.value )
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs( v ) do
                if data[ pbrecord.key ] == nil then
                    data[ pbrecord.key ] = {}
                end

                for k, pbobjects in pairs( pbrecord.value ) do
                    for _, pbobject in pairs( pbobjects )do
                        local childdata = {}
                        ParseData( childdata, pbobject.value )
                        data[ pbrecord.key ][ pbobject.key ] = childdata

                        -- 回调函数
                        _kernel:CallAddFunction( parentname, pbrecord.key, pbobject.key, childdata ) 
                    end
                end
            end
        end
    end
end

function CKernel:SyncAddData( pbdata )
    AddData( _define._kernel_name, self._data, pbdata )
end
---------------------------------------------------------
local function RemoveData( parentname, data, pbdata )
    for k, v in pairs ( pbdata ) do
        if k == "pbobject" then
            for _, pbobject in pairs( v ) do
                if data[ pbobject.key ] ~= nil then
                    RemoveData( pbobject.key, data[ pbobject.key ], pbobject.value )
                end
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs( v ) do
                if data[ pbrecord.key ] ~= nil then
                    for k, pbobjects in pairs( pbrecord.value ) do
                        for _, pbobject in pairs( pbobjects )do
                            local childdata = data[ pbrecord.key ][ pbobject.key ]
                            if childdata ~= nil then
                                -- 回调函数
                                _kernel:CallRemoveFunction( parentname, pbrecord.key, pbobject.key, childdata ) 
                                data[ pbrecord.key ][ pbobject.key ] = nil
                            end

                        end
                    end
                end
            end
        end 
    end
end

function CKernel:SyncRemoveData( pbdata )
    RemoveData( _define._kernel_name, self._data, pbdata )    
end

---------------------------------------------------------
---------------------------------------------------------
-- 获得属性值
function CKernel:GetDataValue( childname )
    if childname == nil then
        return nil
    end

    return self._data[ childname ]
end

-- 设置属性值
function CKernel:SetDataValue( childname, value )
    if childname == nil then
        return
    end

    self._data[ childname ] = value
end

-- 获得对象属性值
function CKernel:GetObjectValue( parentname, childname )
    local parentdata = self:GetDataValue( parentname )
    if parentdata == nil then
        return nil
    end

    return parentdata[ childname ]
end

-- 设置对象属性值
function CKernel:SetObjectValue( parentname, childname, value )
    if parentname == nil or childname == nil then
        return
    end
    
    local parentdata = self:GetDataValue( parentname )
    if parentdata == nil then
        parentdata = {}
        self._data[ parentname ] = parentdata
    end

    parentdata[ childname ] = value
end

-- 获得集合属性值
function CKernel:GetRecordValue( parentname, key, childname )
    local parentdata = self:GetDataValue( parentname )
    if parentdata == nil then
        return nil
    end

    local childdata = parentdata[ key ]
    if childdata == nil then
        return nil
    end

    return childdata[ childname ]
end

-- 设置集合属性值
function CKernel:SetRecordValue( parentname, key, childname, value )
    local parentdata = self:GetDataValue( parentname )
    if parentdata == nil then
        return nil
    end

    local childdata = parentdata[ key ]
    if childdata == nil then
        return nil
    end

    childdata[ childname ] = value
end

return CKernel