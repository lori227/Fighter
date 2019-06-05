local CMediator = class("CMediator", CNotifier)

CMediator.NAME = "Mediator"
function CMediator.ctor(self, mediatorName)
	CNotifier.ctor(self)
	if not mediatorName then 
		mediatorName = CMediator.NAME 
	end

	self.mediatorName_ = mediatorName
	self.observers_ = {}
	self.show_ = false
end

function CMediator.GetMediatorName(self)
	return self.mediatorName_
end

function CMediator.RegisterObserver(self, notifyName, notifyMethod)
	if notifyName == nil or notifyName == "" then
		error("CMediator.RegisterObserver, notifyName:", notifyName)
		return
	end

	if notifyMethod == nil then
		error("CMediator.RegisterObserver, notifyMethod:", notifyMethod)
		return
	end

	local observer = CObserver.New(notifyMethod, self)
	g_View:RegisterObserver(notifyName, observer)
	self.observers_[notifyName] = true
end

function CMediator.RemoveObserver(self, notifyName)
	if notifyName == nil or notifyName == "" then
		error("CMediator.RemoveObserver, notifyName:", notifyName)
		return
	end
	
	g_View:RemoveObserver(notifyName, self)
	self.observers_[notifyName] = nil
end


function CMediator.OnRegisterUI(self)

end

function CMediator.OnRegisterCommand(self)

end

function CMediator.Destroy(self)

end

function CMediator.OnRemove(self)
	for k, v in pairs(self.observers_) do
		self:RemoveObserver(k)
	end
end

function CMediator.ListNotificationInterests(self)
	-------------------------------------注册Response命令------------------------------------------------
	return {}
end

function CMediator.HandleNotification(self, notification)

end


return CMediator