local CPVPMatchResponseBattleReqCommand = class("CPVPMatchResponseBattleReqCommand", CCommand)

function CPVPMatchResponseBattleReqCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchResponseBattleReqCommand.Execute(self, notification)
	print("CPVPMatchResponseBattleReqCommand.Execute...")
	
	local body = notification:GetBody()
        local t = pb.decode("KFMsg.MsgInformBattleReq", body["Data"])
        local roomid = t["roomid"]
        local battleid = t["battleid"]
        local ip = t["ip"]    
        local port = t["port"]
        print("roomid:"..roomid.." battleid:"..battleid.." ip:"..ip.." port:"..port)

        if ip == "" then
            print("ip:"..ip)
            return
        end

         if port == 0 then
            print("port:"..tostring(port))
            return
        end

        local pvpMatchProxy = g_Facade:RetrieveProxy(ProxyEnum.PVP_MATCH)
        pvpMatchProxy:SetRoomId(roomid)
        pvpMatchProxy:SetBattleId(battleid)
        pvpMatchProxy:SetIp(ip)
        pvpMatchProxy:SetPort(port)

        local MsgInformBattleAckData = 
        {
        }
        --table.print(MsgInformBattleAckData)
        
        local str = pb.encode("KFMsg.MsgInformBattleAck", MsgInformBattleAckData)
        g_Network:Send(ProtobufEnum.MSG_INFORM_BATTLE_ACK, str, #str)

        local loginProxy = g_Facade:RetrieveProxy(ProxyEnum.LOGIN)
        local pvpMatchProxy = g_Facade:RetrieveProxy(ProxyEnum.PVP_MATCH)
        local netPlayerId = loginProxy:GetPlayerId()
        local ip = pvpMatchProxy:GetIp()
        local port = pvpMatchProxy:GetPort()
        FToLuaGameInstance.ConnectPVPServer(ip, port, netPlayerId)
end

return CPVPMatchResponseBattleReqCommand