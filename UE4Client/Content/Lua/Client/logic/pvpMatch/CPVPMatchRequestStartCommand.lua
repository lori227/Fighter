local CPVPMatchRequestStartCommand = class("CPVPMatchRequestStartCommand", CCommand)

function CPVPMatchRequestStartCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestStartCommand.Execute(self, notification)
	print("CPVPMatchRequestStartCommand.Execute...")
	
	--local dir = FToLuaPaths.ProjectContentDir()
	--local filePath = dir .. "Lua/LuaClient/logic/proto/ClientMessage.proto"
	local filePath = "ClientMessage.proto"
	protoc:loadfile(filePath)

	local serverId = FToLuaGameInstance.GetUEServerId()
	print(serverId)
	local MsgStartMatchReqData = 
	{
	   version = "0.0.0.0",
	   matchid = 1,
	   serverid = serverId
	}
	--table.print(MsgStartMatchReqData)
	
	local str = pb.encode("KFMsg.MsgStartMatchReq", MsgStartMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_START_MATCH_REQ, str, #str)

	local m = g_Facade:RetrieveMediator(MediatorEnum.PVP_MATCH)
	m:SetTargetVisibility(m.uiPVPMatchButton_, 1)
	m:SetTargetVisibility(m.uiPVPMatchingText_, 3)
	m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 4)
end

return CPVPMatchRequestStartCommand