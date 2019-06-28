local CPVPMatchRequestCancelCommand = class("CPVPMatchRequestCancelCommand", CCommand)

function CPVPMatchRequestCancelCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestCancelCommand.Execute(self, notification)
	print("CPVPMatchRequestCancelCommand.Execute...")
	
	local MsgCancelMatchReqData = 
	{
	   matchid = 1,
	}
	
	local str = pbc.encode("KFMsg.MsgCancelMatchReq", MsgCancelMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_CANCEL_MATCH_REQ, str, #str)

	local m = CPVPMatchMediator:Get()
	m:SetTargetVisibility(m.uiPVPMatchButton_, 4)
	m:SetTargetVisibility(m.uiPVPMatchingText_, 1)
	m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 1)
end

return CPVPMatchRequestCancelCommand