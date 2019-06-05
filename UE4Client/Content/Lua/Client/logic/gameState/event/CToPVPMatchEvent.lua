local CToPVPMatchEvent = class("CToPVPMatchEvent", CFSMEvent)

function CToPVPMatchEvent.ctor(self, eventId, toStateId, stackOp)
	CFSMEvent.ctor(self, eventId, toStateId, stackOp)
end

return CToPVPMatchEvent