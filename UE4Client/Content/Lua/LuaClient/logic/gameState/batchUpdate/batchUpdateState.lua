local CBatchUpdateState = class("CBatchUpdateState", CFSMState)


function CBatchUpdateState.ctor(self, stateId)
	CFSMState.ctor(self, stateId)
	
end


function CBatchUpdateState.OnEnter(self, event)
	CFSMState.OnEnter(self, event)
	print("CBatchUpdateState.OnEnter...")

	CBatchUpdateMediator:Show()
end


function CBatchUpdateState.Tick(self, deltaTime)
	CFSMState.Tick(self, deltaTime)
end


function CBatchUpdateState.OnExit(self)
	CFSMState.OnExit(self, deltaTime)

	CBatchUpdateMediator:Close()
	print("CBatchUpdateState.OnExit...")
end


function CBatchUpdateState.CanTranstion(self, event)
	return true
end



return CBatchUpdateState