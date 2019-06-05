local CFSMState = class("CFSMState")


function CFSMState.ctor(self, stateId)
    self.stateId_ = stateId
    self.status_ = FSMStateStatusEnum.NONE
end


function CFSMState.OnEnter(self, event)
    self.status_ = FSMStateStatusEnum.RUNNING
end


function CFSMState.Tick(self, deltaTime)
	return self.status_
end


function CFSMState.OnExit(self)
	self.status_ = FSMStateStatusEnum.NONE
end


function CFSMState.CanTranstion(self, event)
	return true
end


function CFSMState.GetStateId(self)
	return self.stateId_
end


function CFSMState.GetStatus(self)
	return self.status_
end

function CFSMState.DoEvent(self, event)
	
end

return CFSMState