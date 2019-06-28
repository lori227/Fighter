local CToCheckVersionEvent = class("CToCheckVersionEvent", CFSMEvent)

function CToCheckVersionEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToCheckVersionEvent