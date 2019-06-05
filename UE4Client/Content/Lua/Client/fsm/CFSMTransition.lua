local CFSMTransition = class("CFSMTransition")


function CFSMTransition.ctor(self, fromStateId, toStateId)
	self.fromStateId_ = fromStateId
    self.toStateId_ = toStateId
end


function CFSMTransition.GetFromStateId(self)
	return self.fromStateId_
end


function CFSMTransition.GetToStateId(self)
	return self.toStateId_
end


return CFSMTransition