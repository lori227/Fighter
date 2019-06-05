local CNotification = class("CNotification")

function CNotification.ctor(self, name, body, type)
	self.name_ = name
	self.body_ = body
	self.type_ = type
end

function CNotification.GetName(self)
	return self.name_
end
		
function CNotification.GetBody(self)
	return self.body_
end

function CNotification.SetBody(self, value)
	self.body_ = value
end	

function CNotification.GetType(self)
	return self.type_
end

function CNotification.SetType(self, value)
	self.type_ = value
end

return CNotification