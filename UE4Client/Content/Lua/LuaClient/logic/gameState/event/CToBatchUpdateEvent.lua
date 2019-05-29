local CToBatchUpdateEvent = class("CToBatchUpdateEvent", CFSMEvent)

function CToBatchUpdateEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToBatchUpdateEvent