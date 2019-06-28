local CRoleInformationBuffItem = class("CRoleInformationBuffItem", CUIItemBase)

function CRoleInformationBuffItem.ctor(self, roleItemData)
	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_BuffItem.WB_BuffItem')
	self.roleInformationBuffItemData_ = roleInformationBuffItemData

	self:Init()
end

--初始化
function CRoleInformationBuffItem.Init(self)
	print("CRoleInformationBuffItem.Init...")
	if self.userWidget_ ~= nil then

		self.buffImage_ = self.userWidget_:FindWidget('BuffImage')

		self:ShowTips()	

	end
	if self.roleInformationBuffItemData_ ~= nil then

		self:ShowOrRefreshUI(self.roleInformationBuffItemData_)
	end
end

--刷新
function CRoleInformationBuffItem.ShowOrRefreshUI(self, roleItemData)
	self.roleInformationBuffItemData_ = roleInformationBuffItemData
	if self.roleInformationBuffItemData_:GetBuffImage() ~= 0 then
		self.buffImage_:SetText(self.roleInformationBuffItemData_:GetBuffImage())
	end
end

function CRoleInformationBuffItem.ShowTips(self)
	self.buffImage_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "Buff内容")
    end)
    self.buffImage_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "Buff内容")
    end)
end

function CRoleInformationBuffItem.RemoveItemUIFromParent(self)
	self.roleInformationBuffItemData_ = nil
	self.userWidget_:RemoveFromParent()
end

function CRoleInformationBuffItem.AddItemUIToParent(self, parentUI)
	parentUI:AddChild(self.userWidget_)
end
function CRoleInformationBuffItem.GetRoleItemUI(self)
	return self.userWidget_
end

function CRoleInformationBuffItem.GetRoleItemData(self)
	return self.roleInformationBuffItemData_
end

return CRoleInformationBuffItem