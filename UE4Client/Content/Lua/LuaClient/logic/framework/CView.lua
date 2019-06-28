local CView = class("CView", CSubject)

function CView.ctor(self)
	CSubject.ctor(self)

	self.mediatorMap_ = {}
	self.showMediators_ = {}
end

function CView.RegisterObserver(self, notificationName, observer)
	CSubject.RegisterObserver(self, notificationName, observer)
end

function CView.NotifyObservers(self, notification)
	CSubject.NotifyObservers(self, notification)
end

function CView.UnregisterObserver(self, notificationName, notifyContext)
	CSubject.UnregisterObserver(self, notificationName, notifyContext)
end 

function CView.RegisterMediator(self, cls, mediator)
	print("CView.RegisterMediator..., cls.classname:"..cls.classname)
	if mediator == nil then
		error("CView.RegisterMediator... "..cls.classname .. " mediator is nil.")
		return
	end

	if self.mediatorMap_[cls.classname] then 
		error("CView.RegisterMediator... "..cls.classname .. " self.mediatorMap_[cls.classname] already has.")
		return 
	end

	self.mediatorMap_[cls.classname] = mediator

	------------------------------------------------------
	local interests = mediator:ListNotificationInterests()

	if #interests > 0 then
		local observer = CObserver.New("HandleNotification", mediator)
		for i=1, #interests do
			self:RegisterObserver(tostring(interests[i]), observer)
		end
	end
	------------------------------------------------------
	mediator:OnRegisterCommand()
end


function CView.UnregisterMediator(self, cls)
	print("CView.UnregisterMediator..., cls.classname:"..cls.classname)
	local mediator = nil

	if not self.mediatorMap_[cls.classname] then 
		self.showMediators_[cls.classname] = nil
		return 
	end

	mediator = self.mediatorMap_[cls.classname]

	------------------------------------------------------
	local interests = mediator:ListNotificationInterests()
	for i=1, #interests do
		self:UnregisterObserver(interests[i], mediator)
	end
	------------------------------------------------------

	self.mediatorMap_[cls.classname] = nil

	local m = self.showMediators_[cls.classname]
	if m ~= nil then
		m:OnClose()
	end
	self.showMediators_[cls.classname] = nil

	if mediator ~= nil then
		mediator:OnUnregisterCommand()
 	end
	return mediator
end


function CView.RetrieveMediator(self, cls)
	return self.mediatorMap_[cls.classname]
end


function CView.GetMediator(self, cls)
	return self.mediatorMap_[cls.classname]
end


function CView.HasMediator(self, cls)
	return self.mediatorMap_[cls.classname] ~= nil
end


function CView.CreateMediator(self, cls)
	local mediator = g_MediatorFactory:CreateMediator(cls)
	if mediator ~= nil then
		mediator:Init()
	end
	return mediator
end


function CView.DestroyMediator(self, cls)
	local mediator = self:GetMediator(cls)
	if mediator ~= nil then
		mediator:Destroy()
	end
end


function CView.Show(self, cls, cb)
	print(cls.classname.." Show")
	local mediator = self:GetMediator(cls)
	if mediator == nil then
		mediator = g_MediatorFactory:CreateMediator(cls)
	end

	self.showMediators_[cls.classname] = mediator

	if mediator.userWidget_ == nil then
		mediator:OnCreateUI()

		if mediator.anim_ ~= nil then
			mediator.anim_.OnAnimationStarted:Add(function()
				if mediator.userWidget_:IsAnimationPlayingForward(mediator.anim_) == true then
					mediator:OnShow()
				end
			end)

			mediator.anim_.OnAnimationFinished:Add(function()
				if mediator.userWidget_:IsAnimationPlayingForward(mediator.anim_) == false then
					mediator:OnClose()
				end
			end)
		end
	end

	if mediator.anim_ ~= nil then
		mediator.userWidget_:PlayAnimation(mediator.anim_, 0, 1, 3, 1)
	else
		mediator:OnShow()
	end

	if cb ~= nil then
		cb(mediator)
	end

	return mediator
end


function CView.ShowUI(inClassName, cb)
	if nil == inClassName or "" == inClassName then
		error(">> CView.ShowUI, inClassName is invalid!")
	end

	local cls = { classname = inClassName }
	local mediator = g_View.showMediators_[cls.classname]
	if mediator and nilmediator.userWidget_ then
		print(">> CView.ShowUI, mediator is opened!")
		return mediator
	end

	return g_View:Show(cls, cb)
end


function CView.Close(self, cls)
	print(cls.classname.." Close")

	local mediator = self.showMediators_[cls.classname]

	self.showMediators_[cls.classname] = nil

	if mediator then
		if mediator.anim_ ~= nil then
			mediator.userWidget_:PlayAnimation(mediator.anim_, 0, 1, 1, 1)
		else
			mediator:OnClose()
		end
	end
end


function CView.CloseUI(inClassName)
	if nil == inClassName or "" == inClassName then
		error(">> CView.CloseUI, inClassName is invalid!")
	end

	local cls = { classname = inClassName }
	return g_View:Close(cls)
end


function CView.HasShow(self, cls)
	return self.showMediators_[cls.classname] ~= nil
end


function CView.CloseGroup(self, group)
	for k, m in pairs(self.showMediators_) do
		if m:GetGroup() == group then
			self:Close(m.classtype)
		end
	end
end


function CView.CloseAll(self, listException)
	local list = {}
	if listException then
		listException = table.extend(listException, list)
	else
		listException = list
	end
	
	for k, v in pairs(self.showMediators_) do
		if table.index(listException, k) == nil then
			printc("CloseAll-->Close: ", k)
			self:Close(v.classtype)
		end
	end
end



function CView.InitializeModel(self)
end

return CView