local CRecruitmentOfficeMediator = class("CRecruitmentOfficeMediator", CMediator, CUIItemContainerBase)

function CRecruitmentOfficeMediator.ctor(self, name)
    CMediator.ctor(self, name)
    CUIItemContainerBase.ctor(self)

    self.deviationText_ = nil
    self.progressBar_  = nil
    self.shopEmptyText_ = nil
    self.refreshText_ = nil
    self.nextTimeText_ = nil
    self.hasNewShopData_ = true
    self.hasNewDeviationData_ = true
    self.needRefreshShop_ = false
    self.curShopItem_ = nil
    self.leftMouseButtonDown_ = false
    self.gkeyDown_ = false
    self.refreshBtnDown_ = false
    self.downTime_ = 0
end

function CRecruitmentOfficeMediator.OnInit(self, ...)
    print("CRecruitmentOfficeMediator -->OnInit")
    CMediator.OnInit(self, ...)
end


function CRecruitmentOfficeMediator.OnDestroyed(self)
    print("CRecruitmentOfficeMediator -->OnDestroyed")

    self.deviationText_ = nil
    self.progressBar_  = nil
    self.shopEmptyText_ = nil
    self.refreshText_ = nil
    self.nextTimeText_ = nil
    self.hasNewShopData_ = true
    self.hasNewDeviationData_ = true 
    self.needRefreshShop_ = false 
    self.curShopItem_ = nil 
    self.leftMouseButtonDown_ = false 
    self.gKeyDown_ = false
    self.refreshBtnDown_ = false
    self.downTime_ = 0 

    CUIItemContainerBase.OnDestroyed(self)
    CMediator.OnDestroyed(self)
end


function CRecruitmentOfficeMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CRecruitmentOfficeMediator -->OnRegisterCommand")
    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_UPDATE_DATA, CRecruitmentShopResponseUpdateDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_RECRUIT_HERO, CRecruitmentShopRequestRecruitHeroCommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_REFRESH_RECRUIT, CRecruitmentShopRequestRefreshRecruitCommand)
    -------------------------------------注册Commond命令------------------------------------------------       
end


function CRecruitmentOfficeMediator.OnUnregisterCommand(self)
    print("CRecruitmentOfficeMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_UPDATE_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_RECRUIT_HERO)
    g_Facade:UnregisterCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_REFRESH_RECRUIT)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end

function CRecruitmentOfficeMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CRecruitmentOfficeMediator -->OnCreateUI")

    -- g_Facade:SendNotification(NotifierEnum.COMMON_REQUEST_ADD_DATA) 

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_RecruitmentOffice.WB_RecruitmentOffice') 
    self.uiItemParent_ = self.userWidget_:FindWidget("ShopList")
    self.refreshText_ = self.userWidget_:FindWidget("RefreshText")
    self.nextTimeText_ = self.userWidget_:FindWidget("NextTimeText")
    self.shopEmptyText_ = self.userWidget_:FindWidget("ShopEmptyText")
    self.progressBar_ = self.userWidget_:FindWidget("ProgressBar")
    self.deviationText_ = self.userWidget_:FindWidget("DeviationText")
    self.shopEmptyText_:SetText(g_UITextCfg["RECRUITMENT_HIRE_SELL_OUT"].Des)
    self.progressBar_:SetPercent(0)

    --右侧职业偏向按钮
    self.userWidget_:FindWidget('ChangeBtn').OnClicked:Add(function ()
        UIUtil.SetWidgetVisibility(self.userWidget_:FindWidget('RightPanel'), 1) 
        CDeviationMediator:Show()  
    end)
    --ESC按钮返回
    self.userWidget_:FindWidget('ReturnBtn').OnClicked:Add(function ()
        CRecruitmentOfficeMediator:Close()
        g_Facade:SendNotification(NotifierEnum.COMMON_REQUEST_ADD_DATA)
    end)
    --按键按下响应
    self.userWidget_.RecOfficeOnKeyDown:Add(function (geometry,keyEvent)
        --ESC按键返回
        if KismetInputLibrary.GetKey(keyEvent).KeyName == "Escape" then
            if not self.gKeyDown_ and not self.refreshBtnDown_ and not self.leftMouseButtonDown_ then 
                CRecruitmentOfficeMediator:Close()
            end
        --G招募响应  
        elseif KismetInputLibrary.GetKey(keyEvent).KeyName == "G" then 
            if not self.gKeyDown_ and not self.refreshBtnDown_ and not self.leftMouseButtonDown_ then 
                self.gKeyDown_ = true  
                g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
            end
        end
    end)
    --按键抬起响应
    self.userWidget_.RecOfficeOnKeyUp:Add(function (geometry,keyEvent)
        --G招募响应  
        if KismetInputLibrary.GetKey(keyEvent).KeyName == "G" then           
                self.gKeyDown_ = false       
        end
    end)
    --刷新按钮
    self.userWidget_:FindWidget('RefreshBtn').OnPressed:Add(function ()
        if not self.gKeyDown_ and not self.refreshBtnDown_ and not self.leftMouseButtonDown_ then 
            self.refreshBtnDown_ = true  
            g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        end    
    end)
    self.userWidget_:FindWidget('RefreshBtn').OnReleased:Add(function ()    
            self.refreshBtnDown_ = false   
    end)
    --全局捕获处理Shop相关鼠标左键事件
    self.userWidget_.RecOfficeOnMouseButtonUp:Add(function (geometry,mouseEvent)
        if KismetInputLibrary.PointerEvent_GetEffectingButton(mouseEvent).KeyName == "LeftMouseButton" then
            if self.leftMouseButtonDown_ ~= false then
                self.leftMouseButtonDown_ = false
            end
            if self.curShopItem_ ~= nil then
                self.curShopItem_.hirePanel_:SetVisibility(2)
                self.curShopItem_.backgroundImage_:SetVisibility(2)
                self.curShopItem_.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0) 
                self.curShopItem_ = nil
            end
        end
    end)

    local playerId = g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetPlayerId()
    local player_recruitcount = "player_recruitcount_" .. tostring(playerId)
    self:RegisterObserver(player_recruitcount, "HandleNotification")
end

function CRecruitmentOfficeMediator.OnRefreshUI(self)
    local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)

    if self.hasNewShopData_ then
        for k, v in pairs(self.items_) do
            self:RemoveItem(v.id_)
        end
        local recruitShopDataMap = recruitmentOfficeProxy:GetRecruitShopDataMap()
        if table.count(recruitShopDataMap) ~= 0 then
            self.shopEmptyText_:SetVisibility(2)
            for k, v in pairs(recruitmentOfficeProxy:GetRecruitShopDataMap()) do
                self:AddItem(CRecruitmentShopItem, v)
            end          
        else
            self.shopEmptyText_:SetVisibility(0)
        end
        self.hasNewShopData_ = false
    end

    if self.hasNewDeviationData_ then
        local str = ""
        local deviationDataMap = recruitmentOfficeProxy:GetDeviationDataMap()
        if table.count(deviationDataMap) ~= 0 then
            for k, v in pairs(deviationDataMap) do
                if k ~= 1 then
                    str = str .. ","
                end
                str = str .. g_UITextCfg[g_RecruitmentOfficeConfig:GetDeviationNameById(v)].Des
            end
        else
            str = "无"
        end
        self.deviationText_:SetText("<Orange>" .. str .. "</>")
        self.hasNewDeviationData_ = false
    end

    CRecruitmentOfficeMediator:Get():RefreshItem()
    self.refreshText_:SetText(string.format(g_UITextCfg["RECRUITMENT_FLASH_BUTTON"].Des, recruitmentOfficeProxy:GetRecruitCount()))
    self.nextTimeText_:SetText(string.format(g_UITextCfg["RECRUITMENT_FLASH_TIME"].Des, recruitmentOfficeProxy:GetRecruitTime()))
end


function CRecruitmentOfficeMediator.OnDestroyedUI(self)
    print("CRecruitmentOfficeMediator -->OnDestroyedUI")

    CUIItemContainerBase.OnDestroyedUI(self)
    CMediator.OnDestroyedUI(self)
end

function CRecruitmentOfficeMediator.OnShow(self)     
    self.needRefreshShop_ = true
    self:OnRefreshUI()

    self:AddToViewport()
    WidgetBlueprintLibrary.SetInputMode_UIOnly(GameplayStatics.GetPlayerController(self.userWidget_, 0), self.userWidget_, false)
end

function CRecruitmentOfficeMediator.OnClose(self)
    self.needRefreshShop_ = false 
    CDeviationMediator:Close()

    self:RemoveFromViewport()
end

function CRecruitmentOfficeMediator.ListNotificationInterests(self)
    return { "player_recruit", "player_hero", }
end

function CRecruitmentOfficeMediator.HandleNotification(self, notification)
    print("CRecruitmentOfficeMediator.HandleNotification...")
    local body = notification:GetBody()

    g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_UPDATE_DATA, body)    
end

function CRecruitmentOfficeMediator.TimeFunction(deltatime, timeId)
    local recruitmentOfficeMediator = CRecruitmentOfficeMediator:Get()
    if recruitmentOfficeMediator.gKeyDown_ or recruitmentOfficeMediator.refreshBtnDown_ then
        recruitmentOfficeMediator.downTime_ = recruitmentOfficeMediator.downTime_ + deltatime
    else
        recruitmentOfficeMediator.downTime_ = 0
        g_TimeCtrl:DelTimer(timeId)
    end
    local time =  recruitmentOfficeMediator.downTime_/2.5
    recruitmentOfficeMediator.progressBar_:SetPercent(time)   
    if time >= 1 then
        g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_REQUEST_REFRESH_RECRUIT)            
        recruitmentOfficeMediator.progressBar_:SetPercent(0)   
        recruitmentOfficeMediator.gKeyDown_ = false
        recruitmentOfficeMediator.refreshBtnDown_  = false
        recruitmentOfficeMediator.downTime_ = 0
        g_TimeCtrl:DelTimer(timeId)
    end         
end

return CRecruitmentOfficeMediator  
 
