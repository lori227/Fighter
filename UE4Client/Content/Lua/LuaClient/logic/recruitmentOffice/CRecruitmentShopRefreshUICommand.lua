local CRecruitmentShopRefreshUICommand = class("CRecruitmentShopRefreshUICommand", CCommand)

function CRecruitmentShopRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentShopRefreshUICommand.Execute(self, notification)
	print("CRecruitmentShopRefreshUICommand.Execute...")

	self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

	self.uiPanel_ = self.recruitmentOfficeMediator_.uiPanel_
	if self.uiPanel_ == nil then
		return
	end

	if self.recruitmentOfficeMediator_.hasNewShopData_ == true then
		self:RefreshUI()
		self.recruitmentOfficeMediator_.hasNewShopData_ = false
	else
		self:OpenUI()
	end
end

function CRecruitmentShopRefreshUICommand.RefreshUI(self)
	--复用
	if #self.recruitmentOfficeMediator_.shopItemUIList_ == 0 then
		self:CreateUI(1)
	else
		self:ReSetUI()
	end	
end

function CRecruitmentShopRefreshUICommand.OpenUI(self)

end

function CRecruitmentShopRefreshUICommand.CreateUI(self, num) 
	--获取容器
	local shopList = self.uiPanel_:FindWidget('ShopList')
	--载入Item
	for k,v in pairs(self.recruitmentOfficeProxy_.shopList_) do
		if	k >= num then
			--获取控件
	        local shopItemUI = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_ShopItem.WB_ShopItem')
	        local hirePanel = shopItemUI:FindWidget('HirePanel')
	        local backgroundImage = shopItemUI:FindWidget('BackgroundImage')
	        local hireIamge = shopItemUI:FindWidget('HireImage')
	        --设置费用显示
		    if v:GetCost1() ~= 0 and v:GetCost2() ~= 0 and v:GetCost3() ~= 0 then
		    	shopItemUI:FindWidget('CostText_1'):SetText(v:GetCost1())
		        shopItemUI:FindWidget('CostText_2'):SetText(v:GetCost2())
		        shopItemUI:FindWidget('CostText_3'):SetText(v:GetCost3())
		    else
		        self.recruitmentOfficeMediator_:SetTargetVisibility(shopItemUI:FindWidget('CostPanel'), 1) 
		        self.recruitmentOfficeMediator_:SetTargetVisibility(shopItemUI:FindWidget('CostFree'), 4) 
		    end  
		    --绑定各种触发
		    shopItemUI.ShopItemOnMouseEnter:Add(function (geometry, mouseEvent)
		        if self.recruitmentOfficeMediator_.leftMouseButtonDown_ == false then
		            self.recruitmentOfficeMediator_:SetTargetVisibility(hirePanel, 4)
		            self.recruitmentOfficeMediator_:SetTargetVisibility(backgroundImage, 4)
		        end 
		    end)
		    shopItemUI.ShopItemOnMouseLeave:Add(function (mouseEvent)
		        if	self.recruitmentOfficeMediator_.leftMouseButtonDown_ == false then
		            self.recruitmentOfficeMediator_:SetTargetVisibility(hirePanel, 2) 
		            self.recruitmentOfficeMediator_:SetTargetVisibility(backgroundImage, 2) 
		        end
		    end)
	        shopItemUI.ShopItemOnMouseButtonDown:Add(function (geometry, mouseEvent)
	        	
		        -- local KismetInputLibrary = import("KismetInputLibrary")
		        -- if KismetInputLibrary.IsMouseButtonDown(mouseEvent, "LeftMouseButton") then
		        --    	print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
		        -- end

		        self.recruitmentOfficeMediator_.leftMouseButtonDown_ = true
		        self.recruitmentOfficeMediator_.curShopItem_ = v
		        self.recruitmentOfficeMediator_.curShopItemUI_ = shopItemUI
		        self.recruitmentOfficeMediator_:SetTargetVisibility(hireIamge, 4) 
---------------------------------------------------------------------------------------------------
		    	if self.recruitmentOfficeMediator_.curShopItem_ ~= nil then
		           	print(self.recruitmentOfficeMediator_.curShopItem_:GetId() .. "***")
		           	print("OnMouseButtonDown")
		        else
		           	print(self.recruitmentOfficeMediator_.curShopItem_)
		           	print("OnMouseButtonDown")
		        end
----------------------------------------------------------------------------------------------------
	        end)
			shopItemUI.ShopItemOnMouseButtonUp:Add(function (geometry, mouseEvent)
				self.recruitmentOfficeMediator_.leftMouseButtonDown_ = false
				if shopItemUI ~= self.recruitmentOfficeMediator_.curShopItemUI_ and self.recruitmentOfficeMediator_.curShopItemUI_ ~= nil then
					self.recruitmentOfficeMediator_:SetTargetVisibility(self.recruitmentOfficeMediator_.curShopItemUI_:FindWidget('HirePanel'), 2) 
	        		self.recruitmentOfficeMediator_:SetTargetVisibility(self.recruitmentOfficeMediator_.curShopItemUI_:FindWidget('BackgroundImage'), 2) 
	        		self.recruitmentOfficeMediator_:SetTargetVisibility(hirePanel, 4)
	            	self.recruitmentOfficeMediator_:SetTargetVisibility(backgroundImage, 4)
	        	end
	        	self.recruitmentOfficeMediator_.curShopItem_ = nil
	        	self.recruitmentOfficeMediator_.curShopItemUI_ = nil
	        	self.recruitmentOfficeMediator_:SetTargetVisibility(hireIamge, 2) 
--------------------测试新消息复用刷新---------------------------------------------------------------
	        	--self.recruitmentOfficeMediator_.needRefreshShop_ = true
    			--g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_DATA)    
----------------------------------------------------------------------------------------------------    
	        end)
			--加到容器里	
	        shopList:AddChild(shopItemUI)
	        --添加缓存复用
	     	table.insert(self.recruitmentOfficeMediator_.shopItemUIList_, shopItemUI)
	    end
	end	
end

function CRecruitmentShopRefreshUICommand.ReSetUI(self)
	for k,v in pairs(self.recruitmentOfficeProxy_.shopList_) do
		local shopItemUI = self.recruitmentOfficeMediator_.shopItemUIList_[k]
		if shopItemUI ~= nil then
        	--设置费用显示
	        if v:GetCost1() ~= 0 and v:GetCost2() ~= 0 and v:GetCost3() ~= 0 then
	        	shopItemUI:FindWidget('CostText_1'):SetText(v:GetCost1())
	        	shopItemUI:FindWidget('CostText_2'):SetText(v:GetCost2())
	        	shopItemUI:FindWidget('CostText_3'):SetText(v:GetCost3())
	        else
	        	self.recruitmentOfficeMediator_:SetTargetVisibility(shopItemUI:FindWidget('CostPanel'), 1) 
	        	self.recruitmentOfficeMediator_:SetTargetVisibility(shopItemUI:FindWidget('CostFree'), 4) 
	        end 
	    else
	    	self:CreateUI(k)
		end
	end
	if #self.recruitmentOfficeProxy_.shopList_ < #self.recruitmentOfficeMediator_.shopItemUIList_ then
		for k,v in pairs(self.recruitmentOfficeMediator_.shopItemUIList_) do
			if k > #self.recruitmentOfficeProxy_.shopList_ then
				v:RemoveFromParent()
			end
		end
	end	
end

return CRecruitmentShopRefreshUICommand