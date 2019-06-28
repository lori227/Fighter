local CMainCampsiteState = class("CMainCampsiteState", CFSMState)


function CMainCampsiteState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
end

function CMainCampsiteState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CMainCampsiteState.OnEnter...")

	g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):Init()
	g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE):Init()

	CMainCampsiteMediator:Show()
end

function CMainCampsiteState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end

function CMainCampsiteState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	--g_Facade:SendNotification(NotifierEnum.CLOSE_MAIN_CAMPSITE)
	--g_Facade:SendNotification(NotifierEnum.CLOSE_PACK)
	--g_Facade:SendNotification(NotifierEnum.CLOSE_RECRUITMENT_OFFICE)

	CMainCampsiteMediator:Close()
	print("CMainCampsiteState.OnExit...")
end

function CMainCampsiteState.CanTranstion(self, event)
	return true
end

return CMainCampsiteState