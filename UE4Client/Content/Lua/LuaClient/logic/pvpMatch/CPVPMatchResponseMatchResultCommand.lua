local CPVPMatchResponseMatchResultCommand = class("CPVPMatchResponseMatchResultCommand", CCommand)

function CPVPMatchResponseMatchResultCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchResponseMatchResultCommand.Execute(self, notification)
	print("CPVPMatchResponseMatchResultCommand.Execute...")
	
	local body = notification:GetBody()
    local t = pb.decode("KFMsg.MsgInformMatchResult", body["Data"])
    local time = t["time"]
    print("******************************time:" .. time)

    local m = g_Facade:RetrieveMediator(MediatorEnum.PVP_MATCH)
    m:SetTargetVisibility(m.uiPVPMatchingText_, 1)
    m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 1)
    m:SetTargetVisibility(m.uiPVPMatchSuccessText_, 3)
    m:SetTargetVisibility(m.uiPVPMatchConfirmButton_, 4)
end

return CPVPMatchResponseMatchResultCommand