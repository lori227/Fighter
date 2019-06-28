local CPVPMatchResponseMatchResultCommand = class("CPVPMatchResponseMatchResultCommand", CCommand)

function CPVPMatchResponseMatchResultCommand.ctor(self)
	CCommand.ctor(self)
end

function CPVPMatchResponseMatchResultCommand.Execute(self, notification)
	print("CPVPMatchResponseMatchResultCommand.Execute...")
	
	local body = notification:GetBody()
    local t = pbc.decode("KFMsg.MsgInformMatchResult", body["Data"], body["DataLength"])
    local time = t["time"]
    print("******************************time:" .. time)

    local m = CPVPMatchMediator:Get()
    m:SetTargetVisibility(m.uiPVPMatchingText_, 1)
    m:SetTargetVisibility(m.uiPVPMatchCancelButton_, 1)
    m:SetTargetVisibility(m.uiPVPMatchSuccessText_, 3)
    m:SetTargetVisibility(m.uiPVPMatchConfirmButton_, 4)
end

return CPVPMatchResponseMatchResultCommand