local CFSMEvent = class("CFSMEvent")


function CFSMEvent.ctor(self, eventId, toStateId, stackOp)
	self.eventId_ = eventId
    self.toStateId_ = toStateId
    self.stackOp_ = stackOp
end


function CFSMEvent.GetEventId(self)
	return self.eventId_
end


function CFSMEvent.GetToStateId(self)
	return self.toStateId_
end


function CFSMEvent.GetStackOp(self)
	return self.stackOp_
end


return CFSMEvent