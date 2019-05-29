local CRecruitmentOfficeMediator = class("CRecruitmentOfficeMediator", CMediator)

function CRecruitmentOfficeMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.show_ = false

    --右侧职业偏向
    self.hasNewDeviationData_ = false
    self.needRefreshDeviation_ = false
    self.deviationItemUIList_ = {}

    --中间商品模块
    self.hasNewShopData_ = false
    self.needRefreshShop_ = false
    self.shopItemUIList_ = {}
    self.curShopItem_ = nil
    self.curShopItemUI_ = nil
    self.leftMouseButtonDown_ = false
    self.downTime_ = 0

    --获得新角色
    self.uiGetNewRole_ = nil
end

function CRecruitmentOfficeMediator.Destroy(self)
    print("CRecruitmentOfficeMediator -->Destroy")
   
    self.uiPanel_ = nil
    self.show_ = false

    CMediator.Destroy(self)
end

function CRecruitmentOfficeMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CRecruitmentOfficeMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_RECRUITMENT_OFFICE, "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_RECRUITMENT_OFFICE, "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CRecruitmentOfficeMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CRecruitmentOfficeMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENTT_DEVIATION_REFRESH_UI, CRecruitmentDeviationRefreshUICommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENTT_DEVIATION_REQUEST_DATA, CRecruitmentDeviationRequestDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENTT_DEVIATION_RESPONSE_DATA, CRecruitmentDeviationResponseDataCommand)

    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_REFRESH_UI, CRecruitmentShopRefreshUICommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_DATA, CRecruitmentShopRequestDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_DATA, CRecruitmentShopResponseDataCommand)

    g_Facade:RegisterCommand(NotifierEnum.REQUEST_REFRESH_Get_New_Role, CRequestRefreshGetNewRoleCommand)
    -------------------------------------注册Commond命令------------------------------------------------

    g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_DATA)    
    g_Facade:SendNotification(NotifierEnum.RECRUITMENTT_DEVIATION_RESPONSE_DATA)    
end

function CRecruitmentOfficeMediator.OnRemove(self)
    print("CRecruitmentOfficeMediator -->OnRemove")

    self.uiPanel_ = nil
    self.show_ = false

    self:RemoveObserver(NotifierEnum.OPEN_RECRUITMENT_OFFICE)
    self:RemoveObserver(NotifierEnum.CLOSE_RECRUITMENT_OFFICE)

    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENTT_DEVIATION_REFRESH_UI)
    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENTT_DEVIATION_REQUEST_DATA)
    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENTT_DEVIATION_RESPONSE_DATA)

    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENT_SHOP_REFRESH_UI)
    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENT_SHOP_REQUEST_DATA)
    g_Facade:RemoveCommand(NotifierEnum.RECRUITMENT_SHOP_RESPONSE_DATA)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_REFRESH_Get_New_Role) 
    
    CMediator.OnRemove(self)
end

function CRecruitmentOfficeMediator.Open(self)
    if self.show_ == false then
        if self.uiPanel_ == nil then
            self:OnCreatePanel()
        else
            self:Show()
        end
    else
        self:Hide()
    end
end

function CRecruitmentOfficeMediator.Close(self)
    if self.uiPanel_ then
       self.uiPanel_:RemoveFromViewport()   
    end
end

function CRecruitmentOfficeMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_RecruitmentOffice.WB_RecruitmentOffice') 

    --右侧职业偏向按钮
    self.uiRightPanel_ = self.uiPanel_:FindWidget('RightPanel')
    self.uiCareerOrientationBtn_ = self.uiPanel_:FindWidget('ChangeBtn')
    self.uiCareerOrientationBtn_.OnClicked:Add(function ()
        self:SetTargetVisibility(self.uiRightPanel_, 1) 
        g_Facade:SendNotification(NotifierEnum.RECRUITMENTT_DEVIATION_REFRESH_UI)    
    end)
    --按钮返回
    self.uiReturnBtn_ = self.uiPanel_:FindWidget('ReturnBtn')
    self.uiReturnBtn_.OnClicked:Add(function ()
        self:Open()
    end)
    --ESC返回  
    self.uiPanel_.RecOfficeOnEscKeyDown:Add(function (geometry,keyEvent)
        local KismetInputLibrary = import("KismetInputLibrary")
        if KismetInputLibrary.GetKey(keyEvent).KeyName == "Escape" then
            self:Open()
        end
    end)
    --全局捕获处理Shop相关鼠标左键事件
    self.uiPanel_.RecOfficeOnMouseButtonUp:Add(function (geometry,keyEvent)
        if self.leftMouseButtonDown_ ~= false then
            self.leftMouseButtonDown_ = false
        end
        if self.curShopItemUI_ ~= nil then
            self:SetTargetVisibility(self.curShopItemUI_:FindWidget('HirePanel'), 2) 
            self:SetTargetVisibility(self.curShopItemUI_:FindWidget('BackgroundImage'), 2) 
            self:SetTargetVisibility(self.curShopItemUI_:FindWidget('HireImage'), 2) 
            self.curShopItemUI_ = nil
        end
        if  self.curShopItem_ ~= nil then
            self.curShopItem_ = nil
        end
    end)
    --招募2.5秒响应
    self.uiPanel_.RecOfficeTick:Add(function (geometry, deltatime)
        if self.leftMouseButtonDown_ then
            self.downTime_ = self.downTime_ + deltatime
        else
            self.downTime_ = 0
        end
        if self.curShopItemUI_ ~= nil then  
            local time =  self.downTime_/2.5
            self.curShopItemUI_.HireImage:GetDynamicMaterial():SetScalarParameterValue('Progress', time)   
            if time >= 1 then
                print(self.curShopItem_:GetId() .. "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OK！")
                self:SetTargetVisibility(self.curShopItemUI_:FindWidget('HirePanel'), 2) 
                self:SetTargetVisibility(self.curShopItemUI_:FindWidget('BackgroundImage'), 2) 
                self:SetTargetVisibility(self.curShopItemUI_:FindWidget('HireImage'), 2)                         
                self.curShopItemUI_ = nil
                self.curShopItem_ = nil
                self.leftMouseButtonDown_ = false
                self.downTime_ = 0
                g_Facade:SendNotification(NotifierEnum.REQUEST_REFRESH_Get_New_Role)   
            end      
        end
    end)
    
    g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_REFRESH_UI)    

    self.uiPanel_:AddToViewport(1) 
    self:Open()

 end

function CRecruitmentOfficeMediator.Show(self)
    self.show_ = true
 
    if self.uiPanel_ then 
        self:SetTargetVisibility(self.uiPanel_, 4) 
        self.uiPanel_:SetFocus(self.uiPanel_)
    end
end

function CRecruitmentOfficeMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self:SetTargetVisibility(self.uiPanel_, 1)      
    end
end

function CRecruitmentOfficeMediator.ListNotificationInterests(self)
    return {}
end

function CRecruitmentOfficeMediator.HandleNotification(self, notification)
    print("CRecruitmentOfficeMediator.HandleNotification...")
end

function CRecruitmentOfficeMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CRecruitmentOfficeMediator