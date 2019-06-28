local CSubject = class("CSubject")


function CSubject.ctor(self)
	self.observerMap_ = {}
end


function CSubject.RegisterObserver(self, notificationName, observer)
	if notificationName == nil or notificationName == "" then
		error("CSubject.RegisterObserver, notificationName:", notificationName)
		return
	end

	if observer == nil then
		error("CSubject.RegisterObserver, observer:", observer)
		return
	end

	if not self.observerMap_[notificationName] then
		self.observerMap_[notificationName] = {}
	end

	local count = table.count(self.observerMap_[notificationName]) + 1
	table.insert(self.observerMap_[notificationName], count, observer)
end


function CSubject.NotifyObservers(self, notification)
	if notification == nil then
		error("CSubject.NotifyObservers, notification:", notification)
		return
	end

	local notificationName = notification:GetName()
	if notificationName == nil or notificationName == "" then
		error("CSubject.NotifyObservers, notificationName:", notificationName)
		return
	end

	if self.observerMap_[notificationName] then
		for key, value in pairs(self.observerMap_[notificationName]) do
			local observer = value
			observer:NotifyObserver(notification)
		end
	end
end


function CSubject.UnregisterObserver(self, notificationName, notifyContext)
	if notificationName == nil or notificationName == "" then
		error("CSubject.UnregisterObserver, notificationName:", notificationName)
		return
	end

	if notifyContext == nil then
		error("CSubject.UnregisterObserver, notifyContext:", notifyContext)
		return
	end

	local name = notificationName
	if self.observerMap_[name] then
		for key, value in pairs(self.observerMap_[name]) do
			local observer = value
			if (observer:CompareNotifyContext(notifyContext)) then
				table.remove(self.observerMap_[name], key)
				break
			end
		end
	end
end 


return CSubject