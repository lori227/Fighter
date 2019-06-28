local CRecruitmentShopItem = class("CRecruitmentShopItem", CUIItemBase)

function CRecruitmentShopItem.ctor(self, id)
	CUIItemBase.ctor(self, id)
	self.shopItemData_ = nil
	self.backgroundImage_ = nil
	self.hirePanel_ = nil
	self.hireImage_ = nil
end

--初始化
function CRecruitmentShopItem.OnInit(self, data)
	self.shopItemData_ = data
end

function CRecruitmentShopItem.OnCreateUI(self)
	CUIItemBase.OnCreateUI(self)
	self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_ShopItem.WB_ShopItem')
	self.backgroundImage_ = self.userWidget_:FindWidget('BackgroundImage')
	self.hirePanel_ = self.userWidget_:FindWidget('HirePanel')
	self.hireImage_ = self.userWidget_:FindWidget('HireImage')

	if self.userWidget_ ~= nil and self.shopItemData_ ~= nil then
		if tonumber(self.shopItemData_.cost.money) <= 0 then
			self.userWidget_:FindWidget('CostPanel'):SetVisibility(2)
			self.userWidget_:FindWidget('CostFree'):SetVisibility(0)
		end
		self.userWidget_:FindWidget('RaceCareerText'):SetText(g_UITextCfg[g_RecruitmentOfficeConfig:GetRaceNameById(self.shopItemData_.race)].Des
											    	.. " + " .. g_UITextCfg[g_RecruitmentOfficeConfig:GetProfessionNameById(self.shopItemData_.profession)].Des)
		self.userWidget_:FindWidget('NameText'):SetText(self.shopItemData_.name)
	end

	local recruitmentOfficeMediator = CRecruitmentOfficeMediator:Get()
	--鼠标进入
	self.userWidget_.ShopItemOnMouseEnter:Add(function (geometry, mouseEvent)
		if recruitmentOfficeMediator.leftMouseButtonDown_ == false then
		    self.hirePanel_:SetVisibility(0)
		    self.backgroundImage_:SetVisibility(0)
		end 
	end)
	--鼠标离开
	self.userWidget_.ShopItemOnMouseLeave:Add(function (mouseEvent)
		if recruitmentOfficeMediator.leftMouseButtonDown_ == false then
		    self.hirePanel_:SetVisibility(2) 
		    self.backgroundImage_:SetVisibility(2)
		end
	end)
	--鼠标按下
	self.userWidget_.ShopItemOnMouseButtonDown:Add(function (geometry, mouseEvent)
		if KismetInputLibrary.PointerEvent_GetEffectingButton(mouseEvent).KeyName == "LeftMouseButton" then
			if not recruitmentOfficeMediator.leftMouseButtonDown_ and not recruitmentOfficeMediator.refreshBtnDown_ and not recruitmentOfficeMediator.gKeyDown_ then
			    recruitmentOfficeMediator.leftMouseButtonDown_ = true
				recruitmentOfficeMediator.curShopItem_ = self

				self.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0)   
				--招募2.5秒响应
		    	g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
	    	end
	    end
	end)
	--鼠标抬起
	self.userWidget_.ShopItemOnMouseButtonUp:Add(function (geometry, mouseEvent)
		if KismetInputLibrary.PointerEvent_GetEffectingButton(mouseEvent).KeyName == "LeftMouseButton" then
			recruitmentOfficeMediator.leftMouseButtonDown_ = false
			if self ~= recruitmentOfficeMediator.curShopItem_ and recruitmentOfficeMediator.curShopItem_ ~= nil then
				recruitmentOfficeMediator.curShopItem_.hirePanel_:SetVisibility(2)
		        recruitmentOfficeMediator.curShopItem_.backgroundImage_:SetVisibility(2)
		        recruitmentOfficeMediator.curShopItem_.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0)   
		        self.hirePanel_:SetVisibility(0)
			    self.backgroundImage_:SetVisibility(0)
		    end
		    self.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0)   
		    recruitmentOfficeMediator.curShopItem_ = nil
		end
	end)
end

function CRecruitmentShopItem.OnRefreshItem(self)
	CUIItemBase.OnRefreshItem(self)
	
	if tonumber(self.shopItemData_.cost.money) >= tonumber(g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetMoney())  then
		self.userWidget_:FindWidget('CostText_1'):SetText("<Cost_Not_Enough>" .. self.shopItemData_.cost.money .."</>")
		self.userWidget_:FindWidget('CostText_2'):SetText("<Cost_Not_Enough>" .. 0 .."</>")
		self.userWidget_:FindWidget('CostText_3'):SetText("<Cost_Not_Enough>" .. 0 .."</>")
	else
		self.userWidget_:FindWidget('CostText_1'):SetText("<Cost_Enough>" .. self.shopItemData_.cost.money .."</>")
		self.userWidget_:FindWidget('CostText_2'):SetText("<Cost_Enough>" .. 0 .."</>")
		self.userWidget_:FindWidget('CostText_3'):SetText("<Cost_Enough>" .. 0 .."</>")
	end

end

function CRecruitmentShopItem.TimeFunction(deltatime, timeId)
	local recruitmentOfficeMediator = CRecruitmentOfficeMediator:Get()
	if recruitmentOfficeMediator.leftMouseButtonDown_ then
        recruitmentOfficeMediator.downTime_ = recruitmentOfficeMediator.downTime_ + deltatime
    else
        recruitmentOfficeMediator.downTime_ = 0
        g_TimeCtrl:DelTimer(timeId)
    end
    if recruitmentOfficeMediator.curShopItem_ ~= nil then  
        local time =  recruitmentOfficeMediator.downTime_/2.5
        recruitmentOfficeMediator.curShopItem_.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', time)   
        if time >= 1 then
            g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_REQUEST_RECRUIT_HERO, recruitmentOfficeMediator.curShopItem_.shopItemData_.uuid)   
            recruitmentOfficeMediator.curShopItem_.hirePanel_:SetVisibility(2) 
            recruitmentOfficeMediator.curShopItem_.backgroundImage_:SetVisibility(2) 
            recruitmentOfficeMediator.curShopItem_.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0) 
            recruitmentOfficeMediator.curShopItem_ = nil
            recruitmentOfficeMediator.leftMouseButtonDown_ = false
            recruitmentOfficeMediator.downTime_ = 0
            g_TimeCtrl:DelTimer(timeId)
        end      
    end   
end

function CRecruitmentShopItem.OnDestroyedUI(self)
	CUIItemBase.OnDestroyedUI(self)
end

function CRecruitmentShopItem.OnDestroyed(self)
	self.shopItemData_ = nil
	self.backgroundImage_ = nil
	self.hirePanel_ = nil
	self.hireImage_ = nil
	
    CUIItemBase.OnDestroyed(self)
end

return CRecruitmentShopItem
