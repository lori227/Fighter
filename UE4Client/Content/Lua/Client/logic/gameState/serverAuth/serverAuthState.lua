local CServerAuthState = class("CServerAuthState", CFSMState)

function CServerAuthState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end

function CServerAuthState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CServerAuthState.OnEnter...")

	g_Facade:SendNotification(NotifierEnum.OPEN_SERVER_AUTH)
end

function CServerAuthState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end

function CServerAuthState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	g_Facade:SendNotification(NotifierEnum.CLOSE_SERVER_AUTH)
	
	print("CServerAuthState.OnExit...")
end

function CServerAuthState.CanTranstion(self, event)
	return true
end

return CServerAuthState