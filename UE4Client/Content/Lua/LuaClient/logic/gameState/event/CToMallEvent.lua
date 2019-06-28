local CToMallEvent = class("CMallEvent", CFSMEvent)

function CToMallEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToMallEvent