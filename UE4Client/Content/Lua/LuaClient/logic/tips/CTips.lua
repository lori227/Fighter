local CTips = class("CTips")

function CTips.ctor(self, tipsWidget)
	self.tipsWidget_ = tipsWidget
	self:Init()
end

function CTips.Init(self)
	self.tipsWidget_.Tips:SetVisibility(1)
	self.tipsWidget_:AddToViewport(UIViewZOrderEnum.PROMPT)
end

function CTips.RemoveTips(self)
	self.tipsWidget_:RemoveFromViewport()
	self.tipsWidget_ = nil
end

function CTips.SetWidgetPosition(self)
	-- body
end

function CTips.SetWidgetSize(self, widget,sizeX, sizeY)
	local v2 = KismetMathLibrary.MakeVector2D(sizeX, sizeY) 
	widget.Slot:SetSize(v2)
end

function CTips.SetWidgetText(self, widget, data)
	widget:SetText(data)
end  

function CTips.SetFontSize(self)
	-- body
end

function CTips.SetFontColor(self)
	-- body
end

return CTips