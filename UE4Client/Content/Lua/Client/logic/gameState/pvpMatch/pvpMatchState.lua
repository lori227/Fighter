local CPVPMatchState = class("CPVPMatchState", CFSMState)


function CPVPMatchState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end


function CPVPMatchState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CPVPMatchState.OnEnter...")

	g_Facade:SendNotification(NotifierEnum.OPEN_PVP_MATCH)
end


function CPVPMatchState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end


function CPVPMatchState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	g_Facade:SendNotification(NotifierEnum.CLOSE_PVP_MATCH)
	print("CPVPMatchState.OnExit...")
end


function CPVPMatchState.CanTranstion(self, event)
	return true
end



return CPVPMatchState