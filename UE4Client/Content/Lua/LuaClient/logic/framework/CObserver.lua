local CObserver = class("CObserver")


function CObserver.ctor(self, notifyMethod, notifyContext)
	self.notifyMethod_ = notifyMethod
	self.notifyContext_ = notifyContext
end


function CObserver.NotifyObserver(self, notification)
	--table.print(self.notifyContext_)
	--print("self.notifyMethod_:" .. self.notifyMethod_)
	self.notifyContext_[self.notifyMethod_](self.notifyContext_, notification)
end


function CObserver.CompareNotifyContext(self, obj)
	return self.notifyContext_ == obj
end


function CObserver.SetNotifyMethod(self, value)
	self.notifyMethod_ = value
end


function CObserver.GetNotifyMethod(self)
	return self.notifyMethod_
end


function CObserver.SetNotifyContext(self, value)
	self.notifyContext_ = value
end


function CObserver.GetNotifyContext(self)
	return self.notifyContext_
end


return CObserver
