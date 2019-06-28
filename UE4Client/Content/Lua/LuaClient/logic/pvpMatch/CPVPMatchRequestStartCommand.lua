local CPVPMatchRequestStartCommand = class("CPVPMatchRequestStartCommand", CCommand)

function CPVPMatchRequestStartCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestStartCommand.Execute(self, notification)
	print("CPVPMatchRequestStartCommand.Execute...")

	local serverId = FToLuaGameInstance.GetUEServerId()
	print(serverId)
	local MsgStartMatchReqData = 
	{
	   version = "0.0.0.0",
	   matchid = 1,
	   serverid = serverId
	}
	local str = pbc.encode("KFMsg.MsgStartMatchReq", MsgStartMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_START_MATCH_REQ, str, #str)

	local m = CPVPMatchMediator:Get()
	m:SetTargetVisibility(m.uiPVPMatchButton_, 1)
	m:SetTargetVisibility(m.uiPVPMatchingText_, 3)
	m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 1)
end

return CPVPMatchRequestStartCommand