local CMediator = class("CMediator", CUIPanleBase)


CMediator.NAME = "Mediator"
function CMediator.ctor(self, mediatorName)
	CUIPanleBase.ctor(self)
	if not mediatorName then 
		mediatorName = CMediator.NAME 
	end

	self.mediatorName_ = mediatorName
	self.observers_ = {}
	self.show_ = false
	self.group_ = ""		--組別
end


function CMediator.GetMediatorName(self)
	return self.mediatorName_
end


function CMediator.OnRegisterCommand(self)

end


function CMediator.OnUnregisterCommand(self)

end


function CMediator.OnInit(self, ...)
	print("CMediator.OnInit...")
    CUIPanleBase.OnInit(self, ...)

    g_View:RegisterMediator(self.classtype, self)
end


function CMediator.OnDestroyed(self)
	print("CMediator.OnDestroyed...")
	g_View:UnregisterMediator(self.classtype)

	for k, v in pairs(self.observers_) do
		self:UnregisterObserver(k)
	end

	CUIPanleBase.OnDestroyed(self)
end


function CMediator.OnCreateUI(self)
	print("CMediator.OnCreateUI...")
    CUIPanleBase.OnCreateUI(self)
end


function CMediator.OnDestroyedUI(self)
	print("CMediator.OnDestroyedUI...")
	
	g_View:UnregisterMediator(self.classtype)

    CUIPanleBase.OnDestroyedUI(self)
end


function CMediator.OnShow(self)
	print("CMediator.OnShow...")
end


function CMediator.OnClose(self)
	print("CMediator.OnClose...")
end

function CMediator.GetGroup(self)
	return self.group_
end


function CMediator.Show(cls, cb)
	print("CMediator.Show.."..cls.classname)
	return g_View:Show(cls, cb)
end


function CMediator.Get(cls)
	return g_View:RetrieveMediator(cls)
end


function CMediator.Close(cls)
	print("CMediator.Close.."..cls.classname)
	g_View:Close(cls)
end


function CMediator.ListNotificationInterests(self)
	-------------------------------------注册Response命令------------------------------------------------
	return {}
end


function CMediator.HandleNotification(self, notification)

end


return CMediator