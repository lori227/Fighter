local CBuffTips = class("CBuffTips",CTips)

function CBuffTips.ctor(self)
	CTips.ctor(self, slua.loadUI("/Game/Blueprints/UI/Widget/Tips/WB_BuffTips.WB_BuffTips"))
end

function CBuffTips.CreateTips(self, data)	
	return self:CreateBuffTips(data)
end

function CBuffTips.CreateBuffTips(self, data) 
	self:SetWidgetText(self.tipsWidget_.TipsText, data)
	self:SetWidgetSize(self.tipsWidget_.Tips, 250, 125)
	return self.tipsWidget_
end

function CBuffTips.RemoveTips(self)
	CTips.RemoveTips(self)
end

return CBuffTips