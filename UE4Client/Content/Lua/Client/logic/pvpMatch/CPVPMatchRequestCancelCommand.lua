local CPVPMatchRequestCancelCommand = class("CPVPMatchRequestCancelCommand", CCommand)

function CPVPMatchRequestCancelCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestCancelCommand.Execute(self, notification)
	print("CPVPMatchRequestCancelCommand.Execute...")
	
	--local dir = FToLuaPaths.ProjectContentDir()
	--local filePath = dir .. "Lua/LuaClient/logic/proto/ClientMessage.proto"
	local filePath = "ClientMessage.proto"
	protoc:loadfile(filePath)

	local MsgCancelMatchReqData = 
	{
	   matchid = 1,
	}
	--table.print(MsgCancelMatchReqData)
	
	local str = pb.encode("KFMsg.MsgCancelMatchReq", MsgCancelMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_CANCEL_MATCH_REQ, str, #str)

	local m = g_Facade:RetrieveMediator(MediatorEnum.PVP_MATCH)
	m:SetTargetVisibility(m.uiPVPMatchButton_, 4)
	m:SetTargetVisibility(m.uiPVPMatchingText_, 1)
	m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 1)
end

return CPVPMatchRequestCancelCommand