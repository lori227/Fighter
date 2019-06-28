local CUIPanleBase = class("CUIPanleBase", CUIUserWidget)


function CUIPanleBase.ctor(self)
	CUIUserWidget.ctor(self)

	self.ZOrder_ = UIViewZOrderEnum.MIDDLE
end


function CUIPanleBase.OnInit(self, ...)
	CUIUserWidget.OnInit(self, ...)
end


function CUIPanleBase.OnDestroyed(self)
	CUIUserWidget.OnDestroyed(self)
end

function CUIPanleBase.OnCPPConstruct(self)
	CUIUserWidget.OnCPPConstruct(self)
end

function CUIPanleBase.OnCPPDestroyed(self)
	CUIUserWidget.OnCPPDestroyed(self)
end

function CUIPanleBase.OnCreateUI(self)
	CUIUserWidget.OnCreateUI(self)
end

function CUIPanleBase.OnDestroyedUI(self)
	CUIUserWidget.OnDestroyedUI(self)
end

function CUIPanleBase.AddToViewport(self, zOrder)
	print("CUIPanleBase.AddToViewport...")
	if self.userWidget_ ~= nil then
		if zOrder == nil then
			zOrder = self.ZOrder_
		end
		self.userWidget_:AddToViewport(zOrder)
	end
end


function CUIPanleBase.RemoveFromViewport(self)
	print("CUIPanleBase.RemoveFromViewport...")
	if self.userWidget_ ~= nil then
		self.userWidget_:RemoveFromViewport()
	end
end


function CUIPanleBase.SetZOrder(self, zOrder)
	self.ZOrder_ = zOrder
end


function CUIPanleBase.GetZOrder(self)
	return self.ZOrder_
end


return CUIPanleBase
