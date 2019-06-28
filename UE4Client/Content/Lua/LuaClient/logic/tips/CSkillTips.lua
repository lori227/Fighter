local CSkillTips = class("CSkillTips",CTips)

function CSkillTips.ctor(self)
	CTips.ctor(self, slua.loadUI("/Game/Blueprints/UI/Widget/Tips/WB_SkillTips.WB_SkillTips"))
end

function CSkillTips.CreateTips(self, data)	
	return self:CreateSkillTips(data)
end

function CSkillTips.CreateSkillTips(self, data) 
	self:SetWidgetText(self.tipsWidget_.TipsText, data)
	self:SetWidgetSize(self.tipsWidget_.Tips, 600, 300)
	return self.tipsWidget_
end

function CSkillTips.RemoveTips(self)
	CTips.RemoveTips(self)
end

return CSkillTips