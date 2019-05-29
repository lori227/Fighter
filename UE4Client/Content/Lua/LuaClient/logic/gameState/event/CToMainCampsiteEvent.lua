local CToMainCampsiteEvent = class("CToMainCampsiteEvent", CFSMEvent)

function CToMainCampsiteEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToMainCampsiteEvent
