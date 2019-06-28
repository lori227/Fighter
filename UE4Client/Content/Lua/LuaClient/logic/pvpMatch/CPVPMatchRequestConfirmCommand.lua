local CPVPMatchRequestConfirmCommand = class("CPVPMatchRequestConfirmCommand", CCommand)

function CPVPMatchRequestConfirmCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchRequestConfirmCommand.Execute(self, notification)
	print("CPVPMatchRequestConfirmCommand.Execute...")

	local MsgAffirmMatchReqData = 
	{
	}
	
	local str = pbc.encode("KFMsg.MsgAffirmMatchReq", MsgAffirmMatchReqData)
	g_Network:Send(ProtobufEnum.MSG_AFFIRM_MATCH_REQ, str, #str)

	local m = CPVPMatchMediator:Get()
	m:SetTargetVisibility(m.uiPVPMatchConfirmButton_, 1)
	m:SetTargetVisibility(m.uiPVPMatchSuccessText_, 1)
	m:SetTargetVisibility(m.uiPVPMatchEnterText_, 3)
	m.uiPVPMatchEnterText_:SetText("等待其他玩家确认...")
end

return CPVPMatchRequestConfirmCommand