local CNetPlayerDataCtrl = class("CNetPlayerDataCtrl", CSubject)


function CNetPlayerDataCtrl.ctor(self)
    CSubject.ctor(self)
    self.myNetPlayerData_ = nil
    self.myPlayerId_ = 0
end


function CNetPlayerDataCtrl.GetMyPlayerId()
    return self.myPlayerId_
end


-- 获得第一层key对应的值
function CNetPlayerDataCtrl.GetMyPlayerDataValue_1(self, key1)
    if key1 == nil then
        return nil
    end
    return self.myNetPlayerData_["data_"][key1]
end


-- 获得第二层key对应的值
function CNetPlayerDataCtrl.GetMyPlayerDataValue_2(self, key1, key2)
    local Value_1 = self:GetMyPlayerDataValue_1(key1)
    if Value_1 == nil then
        return nil
    end

    return Value_1[key2]
end


-- 获得第三层key对应的值
function CNetPlayerDataCtrl.GetMyPlayerDataValue_3(self, key1, key2, key3)
    local Value_2 = self:GetMyPlayerDataValue_2(key1, key2)
    if Value_2 == nil then
        return nil
    end

    return Value_2[key3]
end

-- 获得第四层key对应的值
function CNetPlayerDataCtrl.GetMyPlayerDataValue_4(self, key1, key2, key3, key4)
    local Value_3 = self:GetMyPlayerDataValue_3(key1, key2, key3)
    if Value_3 == nil then
        return nil
    end

    return Value_3[key4]
end



function CNetPlayerDataCtrl.HandleLoginAck(self, notification)
    print("CNetPlayerDataCtrl.HandleLoginAck...")
    local body = notification:GetBody()
    local msg = pbc.decode("KFMsg.MsgLoginAck", body["Data"], body["DataLength"])
    --table.print(msg)
    self.myPlayerId_ = msg.playerid

    self.myNetPlayerData_ = nil
    self.myNetPlayerData_ = CNetPlayerData.New(msg.playerid)
    self.myNetPlayerData_:InitData(msg.playerdata)
end


function CNetPlayerDataCtrl.HandleSyncUpdateData(self, notification)
    print("CNetPlayerDataCtrl.HandleSyncUpdateData...")
    if self.myNetPlayerData_ == nil then
        error("CNetPlayerDataCtrl.HandleSyncUpdateData, self.myNetPlayerData_ == nil.")
    end

    local body = notification:GetBody()
    local msg = pbc.decode("KFMsg.MsgSyncUpdateData", body["Data"], body["DataLength"])
    --table.print(msg)
    self.myNetPlayerData_:SyncUpdateData(msg.pbdata)
end 


function CNetPlayerDataCtrl.HandleSyncAddData(self, notification)
    print("CNetPlayerDataCtrl.HandleSyncAddData...")
    if self.myNetPlayerData_ == nil then
        error("CNetPlayerDataCtrl.HandleSyncAddData, self.myNetPlayerData_ == nil.")
    end

    local body = notification:GetBody()
    local msg = pbc.decode("KFMsg.MsgSyncAddData", body["Data"], body["DataLength"])
    --table.print(msg)
    self.myNetPlayerData_:SyncAddData(msg.pbdata)
end


function CNetPlayerDataCtrl.HandleSyncRemoveData(self, notification)
    print("CNetPlayerDataCtrl.HandleSyncUpdateData...")
    if self.myNetPlayerData_ == nil then
        error("CNetPlayerDataCtrl.HandleSyncRemoveData, self.myNetPlayerData_ == nil.")
    end

    local body = notification:GetBody()
    local msg = pbc.decode("KFMsg.MsgSyncRemoveData", body["Data"], body["DataLength"])
    self.myNetPlayerData_:SyncRemoveData(msg.pbdata)
end


return CNetPlayerDataCtrl