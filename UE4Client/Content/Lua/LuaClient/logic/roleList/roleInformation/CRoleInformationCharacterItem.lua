local CRoleInformationCharacterItem = class("CRoleInformationCharacterItem", CUIItemBase)

function CRoleInformationCharacterItem.ctor(self, roleItemData)
	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_CharacterItem.WB_CharacterItem')
	self.roleInformationCharacterItemData_ = roleInformationCharacterItemData

	self:Init()
end

--初始化
function CRoleInformationCharacterItem.Init(self)
	print("CRoleInformationCharacterItem.Init...")
	if self.userWidget_ ~= nil then

		self.buffImage_ = self.userWidget_:FindWidget('BuffImage')

		self:ShowTips()	

	end
	if self.roleInformationCharacterItemData_ ~= nil then

		self:ShowOrRefreshUI(self.roleInformationCharacterItemData_)
	end
end

--刷新
function CRoleInformationCharacterItem.ShowOrRefreshUI(self, roleItemData)
	self.roleInformationCharacterItemData_ = roleInformationCharacterItemData
	if self.roleInformationCharacterItemData_:GetBuffImage() ~= 0 then
		self.buffImage_:SetText(self.roleInformationCharacterItemData_:GetBuffImage())
	end
end

function CRoleInformationCharacterItem.ShowTips(self)
	self.buffImage_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "性格说明")
    end)
    self.buffImage_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "性格说明")
    end)
end

function CRoleInformationCharacterItem.RemoveItemUIFromParent(self)
	self.roleInformationCharacterItemData_ = nil
	self.userWidget_:RemoveFromParent()
end

function CRoleInformationCharacterItem.AddItemUIToParent(self, parentUI)
	parentUI:AddChild(self.userWidget_)
end
function CRoleInformationCharacterItem.GetRoleItemUI(self)
	return self.userWidget_
end

function CRoleInformationCharacterItem.GetRoleItemData(self)
	return self.roleInformationCharacterItemData_
end

return CRoleInformationCharacterItem