local CNetPlayerData = class("CNetPlayerData")


function CNetPlayerData.ctor(self, playerId)
    self.id_ = playerId

    self.rootKey_ = "player"

    -- 数据
    self.data_ = {}
end


function CNetPlayerData.ParseData(self, dataname, datakey, data, pbdata, op)
    --table.print(pbdata)
    for k, v in pairs(pbdata) do
        if k == "pbobject" then
            for _, pbobject in pairs(v) do
                data[pbobject.key] = {}

                local new_dataname = string.format("%s_%s", dataname, tostring(pbobject.key))
                self:ParseData(new_dataname, self.id_, data[pbobject.key], pbobject.value, op)
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs(v) do
                data[pbrecord.key] = {}

                for k, pbobjects in pairs(pbrecord.value) do
                    for _, pbobject in pairs(pbobjects)do
                        data[pbrecord.key][pbobject.key] = {}

                        local new_dataname = string.format("%s_%s", dataname, tostring(pbrecord.key))
                        self:ParseData(new_dataname, pbobject.key, data[pbrecord.key][pbobject.key], pbobject.value, op)
                    end
                end
            end
        elseif k == "pbarray" then
            for _, pbarray in pairs(v) do
                data[pbarray.key] = {}
                for k, pbuint64s in pairs(pbarray.value)  do
                    for _, pbuint64 in pairs(pbuint64s) do
                        data[pbarray.key][pbuint64.key] = pbuint64.value

                        --通知
                        self:HandleSendNotificationArray(dataname, pbarray.key, pbuint64.key, datakey, pbuint64.value, op)
                    end
                end
            end
        else
            for _, pbvalue in pairs(v) do
                data[pbvalue.key] = pbvalue.value

                --通知
                self:HandleSendNotification(dataname, pbvalue.key, datakey, pbvalue.value, op)
            end
        end
    end
end


function CNetPlayerData.InitData(self, pbdata)
	print("CNetPlayerData.InitData...")
	self.data_ = {}
    --table.print(self.data_)
    -- 解析数据
    self:ParseData(self.rootKey_, self.id_, self.data_, pbdata, "Init")
end


function CNetPlayerData.SyncUpdateData(self, pbdata)
	print("CNetPlayerData.SyncUpdateData...")

	-- 更新数据
    self:UpdateData(self.rootKey_, self.id_, self.data_, pbdata)
end


function CNetPlayerData.SyncAddData(self, pbdata)
	print("CNetPlayerData.SyncAddData...")

    self:AddData(self.rootKey_, self.data_, pbdata)
end


function CNetPlayerData.SyncRemoveData(self, pbdata)
	print("CNetPlayerData.SyncRemoveData...")
	
    self:RemoveData(self.rootKey_, self.data_, pbdata)   
end


function CNetPlayerData.UpdateData(self, dataname, datakey, data, pbdata)
    print("CNetPlayerData.UpdateData...")
    --table.print(pbdata)
    for k, v in pairs(pbdata) do
        if k == "pbobject" then
            for _, pbobject in pairs(v) do
                data[pbobject.key] = {}

                local new_dataname = string.format("%s_%s", dataname, tostring(pbobject.key))
                self:UpdateData(new_dataname, self.id_, data[pbobject.key], pbobject.value)
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs(v) do
                if data[pbrecord.key] == nil then
                    data[pbrecord.key] = {}
                end
                
                for k, pbobjects in pairs(pbrecord.value) do
                    for _, pbobject in pairs(pbobjects) do
                        local childdata = data[pbrecord.key][pbobject.key]
                        if childdata ~= nil then

                            local new_dataname = string.format("%s_%s", dataname, tostring(pbrecord.key))
                            self:UpdateData(new_dataname, pbobject.key, childdata, pbobject.value)
                        end
                    end
                end
            end
        elseif k == "pbarray" then
            for _, pbarray in pairs(v) do
                data[pbarray.key] = {}
                for _, pbuint64 in pairs(pbarray.value) do
                    local oldvalue = data[pbarray.key][pbuint64.key]
                    data[pbarray.key][pbuint64.key] = pbuint64.value

                    --通知
                    self:HandleSendNotificationArray(dataname, pbarray.key, pbuint64.key, datakey, pbhnt64.value, "Update")
                end
            end
        else
            for _, pbvalue in pairs(v) do
                local oldvalue = data[pbvalue.key]
                data[pbvalue.key] = pbvalue.value

                --通知
                self:HandleSendNotification(dataname, pbvalue.key, datakey, pbvalue.value, "Update")
            end   
        end
    end
end



function CNetPlayerData.AddData(self, parentname, data, pbdata)
    print("CNetPlayerData.AddData...")
    --table.print(pbdata)
    for k, v in pairs(pbdata) do
        if k == "pbobject" then
            for _, pbobject in pairs(v) do
                if data[pbobject.key] == nil then
                    data[pbobject.key] = {}
                end

                local new_parentname = string.format("%s_%s", parentname, tostring(pbobject.key))
                self:AddData(new_parentname, data[pbobject.key], pbobject.value)
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs(v) do
                if data[pbrecord.key] == nil then
                    data[pbrecord.key] = {}
                end

                for k, pbobjects in pairs(pbrecord.value) do
                    for _, pbobject in pairs(pbobjects)do
                        local childdata = {}
                        self:ParseData(pbrecord.key, pbobject.key, childdata, pbobject.value, "Add")
                        data[pbrecord.key][pbobject.key] = childdata

                        --通知
                        self:HandleSendNotification(parentname, pbrecord.key, pbobject.key, childdata, "Add")
                    end
                end
            end
        end
    end
end



function CNetPlayerData.RemoveData(self, parentname, data, pbdata)
    print("CNetPlayerData.RemoveData...")
    --table.print(pbdata)
    for k, v in pairs (pbdata) do
        if k == "pbobject" then
            for _, pbobject in pairs(v) do
                if data[pbobject.key] ~= nil then

                    local new_parentname = string.format("%s_%s", parentname, tostring(pbobject.key))
                    self:RemoveData(new_parentname, data[pbobject.key], pbobject.value)
                end
            end
        elseif k == "pbrecord" then
            for _, pbrecord in pairs(v) do
                if data[pbrecord.key] ~= nil then
                    for k, pbobjects in pairs(pbrecord.value) do
                        for _, pbobject in pairs(pbobjects)do
                            local childdata = data[pbrecord.key][pbobject.key]
                            if childdata ~= nil then

                                --通知
                                data[pbrecord.key][pbobject.key] = nil

                                self:HandleSendNotification(parentname, pbrecord.key, pbobject.key, nil, "Remove") 
                            end

                        end
                    end
                end
            end
        end 
    end
end


function CNetPlayerData.HandleSendNotification(self, dataname, valuekey, datakey, value, op)
    
    local strKey = ""
    if op == "Add" then
        strKey = string.format("%s_%s", tostring(dataname), tostring(valuekey))
    else
        strKey = string.format("%s_%s_%s", tostring(dataname), tostring(valuekey), tostring(datakey))
    end
    print("CNetPlayerData.HandleSendNotification..., key:"..strKey .. " op:"..op)
    g_Facade:SendNotification(strKey, {Key=strKey, Op=op, Value=value})

end


function CNetPlayerData.HandleSendNotificationArray(self, dataname, valuekey, datakey, key, value, op)
    
    local strKey = ""
    if op == "Add" then
        strKey = string.format("%s_%s_%s", tostring(dataname), tostring(valuekey), tostring(datakey))
    else
        strKey = string.format("%s_%s_%s_%s", tostring(dataname), tostring(valuekey), tostring(datakey), tostring(key))
    end
    print("CNetPlayerData.HandleSendNotification..., key:"..strKey .. " op:"..op)
    g_Facade:SendNotification(strKey, {Key=strKey, Op=op, Value=value})

end



return CNetPlayerData