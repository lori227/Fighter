
local CUIItemBase = class("CUIItemBase", CUIUserWidget)

function CUIItemBase.ctor(self, id)
    CUIUserWidget.ctor(self)

    self.id_ = id
end

function CUIItemBase.OnInit(self, ...)
    CUIUserWidget.OnInit(self, ...)
end

function CUIItemBase.OnCreateUI(self)
	CUIUserWidget.OnCreateUI(self)
end

function CUIItemBase.OnRefreshItem(self)
	
end

function CUIItemBase.OnCPPConstruct(self)
	CUIUserWidget.OnCPPConstruct(self)
end

function CUIItemBase.OnCPPDestroyed(self)
	CUIUserWidget.OnCPPDestroyed(self)
end

function CUIItemBase.OnDestroyed(self)
	self.id_ = nil
	
    CUIUserWidget.OnDestroyed(self)
end

function CUIItemBase.OnDestroyedUI(self)
	CUIUserWidget.OnDestroyedUI(self)
end

function CUIItemBase.GetId(self)
	return self.id_
end

return CUIItemBase