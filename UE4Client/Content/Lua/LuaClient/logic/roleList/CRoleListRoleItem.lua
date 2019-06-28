local CRoleListRoleItem = class("CRoleListRoleItem", CUIItemBase)

function CRoleListRoleItem.ctor(self, roleItemData, id)
	CUIItemBase.ctor(self, id)

	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleList/WB_RoleItem.WB_RoleItem')
	self.roleItemData_ = roleItemData
	self:Init()
end

--初始化
function CRoleListRoleItem.Init(self)
	print("CRoleListRoleItem.Init...")
	if self.userWidget_ ~= nil then

		self.roleImage_ = self.userWidget_:FindWidget('RoleImage')
		self.nameText_ = self.userWidget_:FindWidget('NameText')
		self.sanText_ = self.userWidget_:FindWidget('SanText')
		self.professionIcon_ = self.userWidget_:FindWidget('ProfessionIcon')
		self.professionText_ = self.userWidget_:FindWidget('ProfessionText') 
        self.weaponsIcon_ = self.userWidget_:FindWidget('WeaponsIcon')
		self.weaponsText_ = self.userWidget_:FindWidget('WeaponsText')
		self.levelIcon_ = self.userWidget_:FindWidget('LevelIcon')
		self.levelText_ = self.userWidget_:FindWidget('LevelText')
		self.lifeIcon_ = self.userWidget_:FindWidget('LifeIcon')
		self.lifeText_ = self.userWidget_:FindWidget('LifeText')
		self.backgroundImage_ = self.userWidget_:FindWidget('BackgroundImage')
      
		self:ProxyBinding()	
       
    end
	if self.roleItemData_ ~= nil then

		self:ShowOrRefreshUI(self.roleItemData_)
	end
end

--刷新
function CRoleListRoleItem.ShowOrRefreshUI(self, roleItemData)
	self.roleItemData_ = roleItemData
	-- if self.roleItemData_:GetSanValue() ~= 0 then
	-- 	self.sanText_:SetText(self.roleItemData_:GetSanValue())
	-- end
end

function CRoleListRoleItem.ProxyBinding(self)
	local roleListMediator = CRoleListMediator:Get()
	--鼠标进入
	self.userWidget_.roleItemOnMouseEnter:Add(function (geometry, mouseEvent)
		
		    self.backgroundImage_:SetVisibility(4)
		
	end)	 
	--鼠标离开
	self.userWidget_.roleItemOnMouseLeave:Add(function (mouseEvent)
		
		    self.backgroundImage_:SetVisibility(2)
		
	end)
    --鼠标按下
	self.userWidget_.RoleItemOnMouseButtonDown:Add(function (geometry, mouseEvent)
		local KismetInputLibrary = import("KismetInputLibrary")
		if KismetInputLibrary.PointerEvent_GetEffectingButton(mouseEvent).KeyName == "LeftMouseButton" then
		    roleListMediator.leftMouseButtonDown_ = true
			
			CRoleInformationMediator:Get().curItem_ = self
           
           	CRoleInformationMediator:Show()
      
        end
    end)

    --悬停信息
    self.professionIcon_.OnHovered:Add(function ()
    	print("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB")
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "角色位置")
    end)
    self.professionIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "角色位置")
    end)

    self.weaponsIcon_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
    end)
    self.weaponsIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
    end)

    self.levelIcon_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "当前经验值999")
    end)
    self.levelIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "当前经验值999")
    end)

    self.lifeIcon_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "当前生命值999")
    end)
    self.lifeIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "当前生命值999")
    end)

end



function CRoleListRoleItem.RemoveItemUIFromParent(self)
	self.roleItemData_ = nil
	self.userWidget_:RemoveFromParent()
end

function CRoleListRoleItem.AddItemUIToParent(self, parentUI)
	parentUI:AddChild(self.userWidget_)
end
function CRoleListRoleItem.GetRoleItemUI(self)
	return self.userWidget_
end

function CRoleListRoleItem.GetRoleItemData(self)
	return self.roleItemData_
end

return CRoleListRoleItem