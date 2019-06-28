local CPVPMatchState = class("CPVPMatchState", CFSMState)


function CPVPMatchState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end


function CPVPMatchState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CPVPMatchState.OnEnter...")

	CPVPMatchMediator:Show()
end


function CPVPMatchState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end


function CPVPMatchState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	CPVPMatchMediator:Close()
	print("CPVPMatchState.OnExit...")
end


function CPVPMatchState.CanTranstion(self, event)
	return true
end



return CPVPMatchState