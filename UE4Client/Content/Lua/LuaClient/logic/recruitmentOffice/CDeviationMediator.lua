local CDeviationMediator = class("CDeviationMediator", CMediator, CUIItemContainerBase)

function CDeviationMediator.ctor(self, name)
    CMediator.ctor(self, name)
    CUIItemContainerBase.ctor(self)

    self.hasNewDeviationData_ = false
    self.needRefreshDeviation_ = false
    self.green_ = nil
    self.white_ = nil
end

function CDeviationMediator.OnInit(self, ...)
    print("CDeviationMediator -->OnInit")
    CMediator.OnInit(self, ...)
    self.green_ = KismetMathLibrary.MakeColor(0.040552, 0.708333, 0, 1)
    self.white_ = KismetMathLibrary.MakeColor(1, 1, 1, 1)
end

function CDeviationMediator.OnDestroyed(self)
    print("CDeviationMediator -->OnDestroyed")

    self.hasNewDeviationData_ = false
    self.needRefreshDeviation_ = false
    self.green_ = nil
    self.white_ = nil

    CUIItemContainerBase.OnDestroyed(self)
    CMediator.OnDestroyed(self)
end

function CDeviationMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CDeviationMediator -->OnRegisterCommand")
    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.DEVIATION_REQUEST_ADD_DATA, CDeviationRequestAddDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.DEVIATION_REQUEST_REMOVE_DATA, CDeviationRequestRemoveDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.DEVIATION_RESPONSE_UPDATE_DATA, CDeviationResponseUpdateDataCommand)
    -------------------------------------注册Commond命令------------------------------------------------  
end


function CDeviationMediator.OnUnregisterCommand(self)
    print("CDeviationMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.DEVIATION_REQUEST_ADD_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.DEVIATION_REQUEST_REMOVE_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.DEVIATION_RESPONSE_SET_DATA)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end

function CDeviationMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CDeviationMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_Deviation.WB_Deviation') 
    self.uiItemParent_ = self.userWidget_:FindWidget("DeviationList")
    self.anim_ = self.userWidget_.DeviationAnimation

    for k, v in pairs(g_RecruitmentOfficeConfig.divisorMap_) do  
        self:AddItem(CDeviationItem, v)
    end

    self.userWidget_:FindWidget("ReturnBtn").OnClicked:Add(function ()
        CRecruitmentOfficeMediator:Get().hasNewDeviationData_ = true
        CRecruitmentOfficeMediator:Get():OnRefreshUI()
        CDeviationMediator:Close()
    end)
end

function CDeviationMediator.OnDestroyedUI(self)
    print("CDeviationMediator -->OnDestroyedUI")

    CUIItemContainerBase.OnDestroyedUI(self)
    CMediator.OnDestroyedUI(self)
end

function CDeviationMediator.OnShow(self)     

    CDeviationMediator:Get():RefreshItem()

    self:AddToViewport(UIViewZOrderEnum.HIGH)
end

function CDeviationMediator.OnClose(self)

    local rightPanel = CRecruitmentOfficeMediator:Get().userWidget_:FindWidget('RightPanel')
    if rightPanel ~= nil then
        UIUtil.SetWidgetVisibility(rightPanel, 4) 
    end

    self:RemoveFromViewport()
end

function CDeviationMediator.ListNotificationInterests(self)
    return {
            "player_divisor_id_1", "player_divisor", "player_divisor_1",
            "player_divisor_id_2",                   "player_divisor_2",
            "player_divisor_id_3",                   "player_divisor_3",
            "player_divisor_id_4",                   "player_divisor_4",
            "player_divisor_id_5",                   "player_divisor_5",
            "player_divisor_id_6",                   "player_divisor_6",
            "player_divisor_id_7",                   "player_divisor_7",
            "player_divisor_id_8",                   "player_divisor_8",
            "player_divisor_id_9",                   "player_divisor_9",
            "player_divisor_id_10",                  "player_divisor_10",
            "player_divisor_id_11",                  "player_divisor_11",
            "player_divisor_id_12",                  "player_divisor_12",
           }
end

function CDeviationMediator.HandleNotification(self, notification)
    print("CDeviationMediator.HandleNotification...")
    local body = notification:GetBody()
    g_Facade:SendNotification(NotifierEnum.DEVIATION_RESPONSE_UPDATE_DATA, body)
end

return CDeviationMediator  