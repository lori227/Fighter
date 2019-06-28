local CToLoginEvent = class("CToLoginEvent", CFSMEvent)

function CToLoginEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToLoginEvent