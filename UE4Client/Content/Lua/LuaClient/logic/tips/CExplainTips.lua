local CExplainTips = class("CExplainTips",CTips)

function CExplainTips.ctor(self)
	CTips.ctor(self, slua.loadUI("/Game/Blueprints/UI/Widget/Tips/WB_ExplainTips.WB_ExplainTips"))
end

function CExplainTips.CreateTips(self, data)	
	return self:CreateExplainTips(data)
end

function CExplainTips.CreateExplainTips(self, data)
	-- local str1 = string.format("当前选择的职业偏向为：\n%s、%s、%s","sad","ad","das")
	-- print(str1)
	local str = "<green>" .. data .. "</>" 
 
	self:SetWidgetText(self.tipsWidget_.TipsText, str)
	self.tipsWidget_.TipsText:ForceLayoutPrepass()
	
	local v2 = self.tipsWidget_.TipsText:GetDesiredSize()
	self:SetWidgetSize(self.tipsWidget_.Tips, v2.X + 25, v2.Y + 25)
	return self.tipsWidget_
end

function CExplainTips.RemoveTips(self)
	CTips.RemoveTips(self)
end

return CExplainTips