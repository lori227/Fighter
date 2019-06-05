local CToServerAuthEvent = class("CToServerAuthEvent", CFSMEvent)

function CToServerAuthEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToServerAuthEvent