local CUIUserWidget = class("CUIUserWidget", CObjectBase, CNotifier)

function CUIUserWidget.ctor(self)
	CObjectBase.ctor(self)
	CNotifier.ctor(self)

	self.userWidget_ = nil
	self.anim_ = nil

	self.cppcbc_ = function() self:OnCPPConstruct() end
	self.cppcbd_ = function() self:OnCPPDestroyed() end
end

function CUIUserWidget.OnInit(self, ...)
	print("CUIUserWidget -->OnInit")
    CObjectBase.OnInit(self, ...)
    --CNotifier.OnInit(self)
end

function CUIUserWidget.OnDestroyed(self)
	print("CUIUserWidget -->OnDestroyed")
	self.userWidget_ = nil
	self.anim_ = nil

	--CNotifier.OnDestroyed(self)
    CObjectBase.OnDestroyed(self)
end


function CUIUserWidget.OnCPPConstruct(self)

end

function CUIUserWidget.OnCPPDestroyed(self)
	self:OnDestroyed()
end

function CUIUserWidget.OnCreateUI(self)
	print("CUIUserWidget -->OnCreateUI")
	if self.userWidget_ ~= nil then
		if self.userWidget_.OnConstruct ~= nil then
	        self.userWidget_.OnConstruct:Add(self.cppcbc_)
	    end
	    if self.userWidget_.OnDestruct ~= nil then
	        self.userWidget_.OnDestruct:Add(self.cppcbd_)
	    end
	end
end

function CUIUserWidget.OnDestroyedUI(self)
	print("CUIUserWidget -->OnDestroyedUI")
	if self.userWidget_ ~= nil then
		if self.userWidget_.OnConstruct ~= nil then
	        self.userWidget_.OnConstruct:Remove(self.cppcbc_)
	    end
	    if self.userWidget_.OnDestruct ~= nil then
	        self.userWidget_.OnDestruct:Remove(self.cppcbd_)
	    end
	end
end
	

function CUIUserWidget.RegisterObserver(self, notifyName, notifyMethod)
	if notifyName == nil or notifyName == "" then
		error("CUIUserWidget.RegisterObserver, notifyName:", notifyName)
		return
	end

	if notifyMethod == nil then
		error("CUIUserWidget.RegisterObserver, notifyMethod:", notifyMethod)
		return
	end

	local observer = CObserver.New(notifyMethod, self)
	g_View:RegisterObserver(notifyName, observer)
end


function CUIUserWidget.UnregisterObserver(self, notifyName)
	if notifyName == nil or notifyName == "" then
		error("CUIUserWidget.UnregisterObserver, notifyName:", notifyName)
		return
	end
	
	g_View:UnregisterObserver(notifyName, self)
end

function CUIUserWidget.GetUserWidget(self)
    return self.userWidget_
end

return CUIUserWidget