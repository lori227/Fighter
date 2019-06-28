
local CUIPageBase = class("CUIPageBase", CUIUserWidget)

function CUIPageBase.ctor(self, id, index)
    CUIUserWidget.ctor(self)

    self.id_ = id
    self.index_ = index
end

function CUIPageBase.OnInit(self, ...)
    CUIUserWidget.OnInit(self, ...)
end

function CUIPageBase.OnDestroyed(self)
    CUIUserWidget.OnDestroyed(self)
end

function CUIPageBase.OnCPPConstruct(self)
	CUIUserWidget.OnCPPConstruct(self)
end

function CUIPageBase.OnCPPDestroyed(self)
	CUIUserWidget.OnCPPDestroyed(self)
end

function CUIPageBase.OnCreateUI(self)
	CUIUserWidget.OnCreateUI(self)
end

function CUIPageBase.OnDestroyedUI(self)
	CUIUserWidget.OnDestroyedUI(self)
end


function CUIPageBase.OnInitPage(self)

end

function CUIPageBase.OnShowPage(self, ...)

end

function CUIPageBase.OnClosePage(self)

end


function CUIItemBase.GetId(self)
	return self.id_
end


function CUIItemBase.GetIndex(self)
	return self.index_
end

return CUIPageBase