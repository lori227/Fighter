local CLoginState = class("CLoginState", CFSMState)


function CLoginState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end


function CLoginState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CLoginState.OnEnter...")

	CLoginMediator:Show()
	g_Facade:SendNotification(NotifierEnum.REQUEST_LOGIN)
end


function CLoginState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end


function CLoginState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	CLoginMediator:Close()
	print("CLoginState.OnExit...")
end


function CLoginState.CanTranstion(self, event)
	return true
end





return CLoginState