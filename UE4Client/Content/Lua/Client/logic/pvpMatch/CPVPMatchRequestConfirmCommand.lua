local CPVPMatchRequestConfirmCommand = class("CPVPMatchRequestConfirmCommand", CCommand)

function CPVPMatchRequestConfirmCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestConfirmCommand.Execute(self, notification)
	print("CPVPMatchRequestConfirmCommand.Execute...")
	
	--local dir = FToLuaPaths.ProjectContentDir()
	--local filePath = dir .. "Lua/LuaClient/logic/proto/ClientMessage.proto"
	local filePath = "ClientMessage.proto"
	protoc:loadfile(filePath)

	local MsgAffirmMatchReqData = 
	{
	}
	--table.print(MsgAffirmMatchReqData)
	
	local str = pb.encode("KFMsg.MsgAffirmMatchReq", MsgAffirmMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_AFFIRM_MATCH_REQ, str, #str)

	local m = g_Facade:RetrieveMediator(MediatorEnum.PVP_MATCH)
	m:SetTargetVisibility(m.uiPVPMatchConfirmButton_, 1)
	m:SetTargetVisibility(m.uiPVPMatchSuccessText_, 1)
	m:SetTargetVisibility(m.uiPVPMatchEnterText_, 3)
end

return CPVPMatchRequestConfirmCommand