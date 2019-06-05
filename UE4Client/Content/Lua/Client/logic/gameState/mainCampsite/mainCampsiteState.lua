local CMainCampsiteState = class("CMainCampsiteState", CFSMState)


function CMainCampsiteState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end

function CMainCampsiteState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CMainCampsiteState.OnEnter...")

	g_Facade:SendNotification(NotifierEnum.OPEN_MAIN_CAMPSITE)
end

function CMainCampsiteState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)

end

function CMainCampsiteState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	g_Facade:SendNotification(NotifierEnum.CLOSE_MAIN_CAMPSITE)

	print("CMainCampsiteState.OnExit...")
end

function CMainCampsiteState.CanTranstion(self, event)
	return true
end

return CMainCampsiteState