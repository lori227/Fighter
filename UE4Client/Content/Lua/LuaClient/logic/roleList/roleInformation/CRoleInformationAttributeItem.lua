local CRoleInformationAttributeItem = class("CRoleInformationAttributeItem", CUIItemBase)

function CRoleInformationAttributeItem.ctor(self, roleItemData)
	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_AttributeItem.WB_AttributeItem')
	self.roleInformationAttributeItem_ = roleInformationAttributeItem

	self:Init()
end

--初始化
function CRoleInformationAttributeItem.Init(self)
	print("CRoleInformationAttributeItem.Init...")
	if self.userWidget_ ~= nil then

		self.attributeText_ = self.userWidget_:FindWidget('AttributeText')
		self.attributeValue_ = self.userWidget_:FindWidget('AttributeValue')

		self:ShowTips()	

	end
	if self.roleInformationAttributeItem_ ~= nil then

		self:ShowOrRefreshUI(self.roleInformationAttributeItemData_)
	end
end

--刷新
function CRoleInformationAttributeItem.ShowOrRefreshUI(self, roleItemData)
	self.roleInformationAttributeItemData_ = roleInformationAttributeItemData
	if self.roleInformationAttributeItemData_:GetAttributeText() ~= 0 and self.roleInformationAttributeItemData_:GetAttributeValue() then
		self.attributeText_:SetText(self.roleInformationAttributeItemData_:GetAttributeText())
		self.attributeValue_:SetText(self.roleInformationAttributeItemData_:GetAttributeValue())
	end
end

function CRoleInformationAttributeItem.ShowTips(self)
	self.attributeText_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "属性内容")
    end)
    self.attributeText_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "属性内容")
    end)
end

function CRoleInformationAttributeItem.RemoveItemUIFromParent(self)
	self.roleInformationAttributeItemData_ = nil
	self.userWidget_:RemoveFromParent()
end

function CRoleInformationAttributeItem.AddItemUIToParent(self, parentUI)
	parentUI:AddChild(self.userWidget_)
end
function CRoleInformationAttributeItem.GetRoleItemUI(self)
	return self.userWidget_
end

function CRoleInformationAttributeItem.GetRoleItemData(self)
	return self.roleInformationAttributeItemData_
end

return CRoleInformationAttributeItem