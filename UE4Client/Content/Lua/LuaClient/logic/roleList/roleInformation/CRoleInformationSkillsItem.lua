local CRoleInformationSkillsItem = class("CRoleInformationSkillsItem", CUIItemBase)

function CRoleInformationSkillsItem.ctor(self, roleItemData)
	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_SkillsItem.WB_SkillsItem')
	self.roleInformationSkillsItemData_ = roleInformationSkillsItemData

	self:Init()
end

--初始化
function CRoleInformationSkillsItem.Init(self)
	print("CRoleInformationSkillsItem.Init...")
	if self.userWidget_ ~= nil then

		self.activeSkillsIcon_ = self.userWidget_:FindWidget('ActiveSkillsIcon')
		self.talentIcon1_ = self.userWidget_:FindWidget('TalentIcon1')
		self.talentIcon2_ = self.userWidget_:FindWidget('TalentIcon2')
		self.probeSkillIcon1_ = self.userWidget_:FindWidget('ProbeSkillIcon1')
		self.probeSkillIcon2_ = self.userWidget_:FindWidget('ProbeSkillIcon2')

		self:ShowTips()	

	end
	if self.roleInformationSkillsItemData_ ~= nil then

		self:ShowOrRefreshUI(self.roleInformationSkillsItemData_)
	end
end

--刷新
function CRoleInformationSkillsItem.ShowOrRefreshUI(self, roleItemData)
	self.roleInformationSkillsItemData_ = roleInformationSkillsItemData
	if self.roleInformationSkillsItemData_:GetBuffImage() ~= 0 then
		self.buffImage_:SetText(self.roleInformationSkillsItemData_:GetBuffImage())
	end
end

function CRoleInformationSkillsItem.ShowTips(self)
	self.activeSkillsIcon_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "主动技能")
    end)
    self.activeSkillsIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "主动技能")
    end)

    self.talentIcon1_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "天赋1")
    end)
    self.talentIcon1_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "天赋1")
    end)

    self.talentIcon2_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "天赋2")
    end)
    self.talentIcon2_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "天赋2")
    end)

    self.probeSkillIcon1_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "探索技能1")
    end)
    self.probeSkillIcon1_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "探索技能1")
    end)

    self.probeSkillIcon2_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "探索技能2")
    end)
    self.probeSkillIcon2_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "探索技能2")
    end)
end

function CRoleInformationSkillsItem.RemoveItemUIFromParent(self)
	self.roleInformationSkillsItemData_ = nil
	self.userWidget_:RemoveFromParent()
end

function CRoleInformationSkillsItem.AddItemUIToParent(self, parentUI)
	parentUI:AddChild(self.userWidget_)
end
function CRoleInformationSkillsItem.GetRoleItemUI(self)
	return self.userWidget_
end

function CRoleInformationSkillsItem.GetRoleItemData(self)
	return self.roleInformationSkillsItemData_
end

return CRoleInformationSkillsItem