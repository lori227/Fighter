local CNetwork = class("CNetwork")

function CNetwork.ctor(self)
    self.tcpSocket = nil
    self.tcpClient = nil
    self.IsConnected = false
    self.recvData = {}
    self.recvDataLen = 0
    self.msgHeadLen = 8
end

function CNetwork.Init(self)
    do
        FToLuaGameInstance.TCPClientInit()
        return
    end

    print(socket._VERSION)
    self.tcpSocket, err = socket.tcp()
    if self.tcpSocket == nil then
        print("Create Socket Fail..., err:"..err)
        return false
    end

    print("Create Socket Success...")
    return true
end

function CNetwork.IsNeedReset(self)
    do
        return FToLuaGameInstance.TCPClientIsNeedReset()
    end
end

function CNetwork.Reset(self)
    do
        return FToLuaGameInstance.TCPClientReset()
    end
end

function CNetwork.Connect(self, ip, port)
    do
        FToLuaGameInstance.TCPClientConnect(ip, port)
        return
    end
    
    if self.tcpSocket == nil then
        return false
    end
    local ret = self.tcpSocket:connect(ip, port)
    if not ret then
        print("Connect Server Failed...")
        return false
    else
        print("Connect Server Success...")
        self.tcpSocket:settimeout(0)
        self.IsConnected = true
        return true
    end
end

function CNetwork.Close(self)
    if self.tcpSocket ~= nil then
        self.tcpSocket:close()
    end
end

function CNetwork.Shutdown(self)
    do
        FToLuaGameInstance.TCPClientDestroy()
        return
    end

    if self.tcpSocket ~= nil then
        self.tcpSocket:shutdown()
        self.tcpSocket = nil
    end  
end

function CNetwork.Send(self, msgId, str, len)
    do
        FToLuaGameInstance.TCPClientSend(msgId, str, len)
        return
    end

    if self.tcpSocket == nil then
        return
    end

    local netHeadFmt = string.format("<I4I2I2c%d", len)
    local p = string.pack(netHeadFmt, len, msgId, 0, str)
    local sendLen = self.tcpSocket:send(p)
    if sendLen == nil then
        print("CNetwork.Send Fail, msgId:"..msgId .. " len:".. len .. " sendLen:nil")
    else
        print("CNetwork.Send Seccess, msgId:"..msgId .. " len:".. len .. " sendLen:"..sendLen)
    end
end

function CNetwork.ProcessReceiveMessage(self)
    if self.IsConnected == false then
        return
    end

    if self.tcpSocket == nil then
        return
    end

    local s, status, partial = self.tcpSocket:receive(5*1024)
    if s == nil and partial == nil then
        if status == "closed" then
            self.tcpSocket = nil
            self.IsConnected = false
            self.recvData = {}
            self.recvDataLen = 0
            print("Server Closed...")
            return
        elseif status == "timeout" then
            --self.recvData = {}
            --self.recvDataLen = 0
            --print("Server Timeout...")
            return
        end
    else
        local rc = nil
        if s ~= nil then
            rc = s
            --print("s:"..s)
        elseif partial ~= nil then
            rc = partial
            --print("partial:"..partial)
        else
            return
        end

        if rc == nil then
            return
        end

        --print("rc:"..rc)
        table.insert(self.recvData,rc)
        local data = table.concat(self.recvData)
        --print("data:"..data)
        self.recvDataLen = string.len(data)
        --print("~~~~~~~~~~~~~~~~~~~~~~ProcessReceiveMessage...   recvDataLen:"..self.recvDataLen)

        --[[
        local content = table.concat(self.recvData)
        local subContent = string.sub(content, 1, -1)
        local dataLen, msgId, child = string.unpack("<I4I2I2", subContent)
        print("dataLen:"..dataLen .. " msgId:" .. msgId.. " child:" ..child)
        local netHeadFmt = string.format("<I4I2I2c%d", dataLen)
        print("netHeadFmt:"..netHeadFmt)
        local dataLen, msgId, child, d = string.unpack(netHeadFmt, subContent)

        local t = pb.decode("KFMsg.MsgLoginAck", d)
        local playerId = t["playerid"]
        print("******************************playerId:" .. playerId)
        --]]

        --处理消息  
        self:ParseReceiveBuffToMessage()
    end
end

function CNetwork.ParseReceiveBuffToMessage(self)
    local pos = 1
    local isValid, dataLen = self:CheckReciveBuffValid(pos) 
    if not isValid then
        return
    end

    print("#################ParseReceiveBuffToMessage...")
    local content = table.concat(self.recvData)

    while self.recvDataLen >= pos - 1 + self.msgHeadLen + dataLen do
        local subContent = string.sub(content, pos, -1)
        local headDataLen, headMsgId = string.unpack("<I4I2", subContent)
        print("!!!!!!!!!recvDataLen:"..self.recvDataLen.." pos:"..pos.." msgHeadLen:"..self.msgHeadLen.." dataLen:"..dataLen.." headDataLen:"..headDataLen.." headMsgId:"..headMsgId)
        local msgId = 0
        local child = 0
        local data = ""
        if headDataLen > 0 then
            local netHeadFmt = string.format("<I4I2I2c%d", dataLen)
            dataLen, msgId, child, data = string.unpack(netHeadFmt, subContent)
            print("netHeadFmt:"..netHeadFmt.. " subContent:"..subContent.." data:"..tostring(data))
            if msgId == 3005 then
                local t = pbc.decode("KFMsg.MsgInformBattleReq", data)
                local roomid = t["roomid"]
                local battleid = t["battleid"]
                local ip = t["ip"]    
                local port = t["port"]
                print("roomid:"..roomid.." battleid:"..battleid.." ip:"..ip.." port:"..port)
            end
        end

        if msgId > 0 then
            g_Facade:SendNotification(tostring(msgId), {MsgId=msgId, Data=data, DataLength=dataLen})
        end

        local t = string.sub(content, pos + self.msgHeadLen + dataLen, -1)
        content = t
        self.recvDataLen = self.recvDataLen - self.msgHeadLen - dataLen
    end
    self.recvData = {}
end

function CNetwork.CheckReciveBuffValid(self, pos)
    --print("self.recvDataLen:"..self.recvDataLen)
    --print("pos:"..pos)
    --print("self.msgHeadLen:"..self.msgHeadLen)
    if self.recvDataLen < 8 then
        return false, 0
    end

    if self.recvDataLen >= 8 and self.recvDataLen <= pos + self.msgHeadLen then
        print("11111111111")
        local content = table.concat(self.recvData)
        local dataLen, msgId, child = string.unpack("<I4I2I2", content)
        print("1 dataLen:"..dataLen .. " msgId:" .. msgId.. " child:" ..child)
        if msgId == 0 or dataLen == 0 then
            self.recvData = {}
            self.recvDataLen = 0
            return false, 0
        else
            return false, 0    
        end
    end

    if self.recvData == nil then
        print("222222222222222")
        return false, 0
    end

    local content = table.concat(self.recvData)
    print("content:"..content)
    local dataLen, msgId, child = string.unpack("<I4I2I2", content)
    print("3 dataLen:"..dataLen .. " msgId:" .. msgId.. " child:" ..child)

    if msgId == 0 or dataLen == 0 then
        self.recvData = {}
        self.recvDataLen = 0
        return false, 0
    end

    --收到的消息长度有错误
    if dataLen > 1024 * 5 then
        self.recvData = {}
        self.recvDataLen = 0
        return false, 0
    end

    return true, dataLen 
end


return CNetwork