local CView = class("CView")

function CView.ctor(self)
	self.mediatorMap_ ={}
	self.observerMap_ ={}
end

function CView.RegisterObserver(self, notificationName, observer)
	if notificationName == nil or notificationName == "" then
		error("CView.RegisterObserver, notificationName:", notificationName)
		return
	end

	if observer == nil then
		error("CView.RegisterObserver, observer:", observer)
		return
	end

	if not self.observerMap_[notificationName] then
		self.observerMap_[notificationName] = {}
	end

	local count = table.count(self.observerMap_[notificationName]) + 1
	table.insert(self.observerMap_[notificationName], count, observer)
end

function CView.NotifyObservers(self, notification)
	if notification == nil then
		error("CView.NotifyObservers, notification:", notification)
		return
	end

	local notificationName = notification:GetName()
	if notificationName == nil or notificationName == "" then
		error("CView.NotifyObservers, notificationName:", notificationName)
		return
	end

	if self.observerMap_[notificationName] then
		for key, value in pairs(self.observerMap_[notificationName]) do
			local observer = value
			observer:NotifyObserver(notification)
		end
	end
end

function CView.RemoveObserver(self, notificationName, notifyContext)
	if notificationName == nil or notificationName == "" then
		error("CView.RemoveObserver, notificationName:", notificationName)
		return
	end

	if notifyContext == nil then
		error("CView.RemoveObserver, notifyContext:", notifyContext)
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
function CView.RegisterMediator(self, mediator)
	if self.mediatorMap_[mediator:GetMediatorName()] then 
		return 
	end

	self.mediatorMap_[mediator:GetMediatorName()] = mediator

	------------------------------------------------------
	local interests = mediator:ListNotificationInterests()

	if #interests > 0 then
		local observer = CObserver.New("HandleNotification", mediator)
		for i=1, #interests do
			self:RegisterObserver(tostring(interests[i]), observer)
		end
	end
	------------------------------------------------------

	mediator:OnRegisterUI()
	mediator:OnRegisterCommand()
end

function CView.RetrieveMediator(self, mediatorName)
	return self.mediatorMap_[mediatorName]
end

function CView.RemoveMediator(self, mediatorName)
	local mediator = nil

	if not self.mediatorMap_[mediatorName] then 
		return 
	end

	mediator = self.mediatorMap_[mediatorName]

	------------------------------------------------------
	local interests = mediator:ListNotificationInterests()
	for i=1, #interests do
		self:RemoveObserver(interests[i], mediator)
	end
	------------------------------------------------------

	self.mediatorMap_[mediatorName] = nil

	if mediator then
 		mediator:OnRemove() 
 	end
	return mediator
end

function CView.HasMediator(self, mediatorName)
	return self.mediatorMap_[mediatorName] ~= nil
end

function CView.GetMediator(self, mediatorName)
	return self.mediatorMap_[mediatorName]
end

function CView.InitializeModel(self)
end

return CView