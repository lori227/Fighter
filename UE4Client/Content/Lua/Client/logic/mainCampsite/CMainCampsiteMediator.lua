local CMainCampsiteMediator = class("CMainCampsiteMediator", CMediator)

function CMainCampsiteMediator.ctor(self, name)
    CMediator.ctor(self, name)
    
    self.uiPanel_ = nil
end

function CMainCampsiteMediator.Destroy(self)
    print("CMainCampsiteMediator -->Destroy")
    
    self.uiPanel_ = nil

    CMediator.Destroy(self)
end

function CMainCampsiteMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CMainCampsiteMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_MAIN_CAMPSITE,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_MAIN_CAMPSITE,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CMainCampsiteMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CMainCampsiteMediator -->OnRegisterCommand")
    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_PACK_DATA, CMainCampsiteRequestPackDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA, CMainCampsiteRequestRecruitmentOfficeDataCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CMainCampsiteMediator.OnRemove(self)
    print("CMainCampsiteMediator -->OnRemove")

    self.uiPanel_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_MAIN_CAMPSITE)
    self:RemoveObserver(NotifierEnum.CLOSE_MAIN_CAMPSITE)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_PACK_DATA)
    g_Facade:RemoveCommand(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA)

    CMediator.OnRemove(self)
end

function CMainCampsiteMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CMainCampsiteMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CMainCampsiteMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/MainCampsite/WB_MainCampsite.WB_MainCampsite')
    self.uiPlayerNameText_ = self.uiPanel_:FindWidget('PlayerNameText')
    self.ui1vs1Btn_ = self.uiPanel_:FindWidget('1VS1Btn')
    self.uiPackBtn_ = self.uiPanel_:FindWidget('WarehouseBtn')
    self.uiRecruitmentOfficeBtn_ = self.uiPanel_:FindWidget('RecruitmentOfficeBtn')

    self.uiPlayerNameText_:SetText(g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetPlayerName())
    self.ui1vs1Btn_.OnClicked:Add(function ()
        --切换到PVP匹配状态
        local toPVPMatchEvent = CToPVPMatchEvent.New(GameFSMStateIdEnum.MAIN_CAMPSITE, GameFSMStateIdEnum.PVP_MATCH, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toPVPMatchEvent)
    end)

    self.uiPackBtn_.OnClicked:Add(function ()
        print("背包")
        --local mri = require("memory/MemoryReferenceInfo")
        --mri.m_cMethods.DumpMemorySnapshot("C:/Users/OP/Desktop/Memory", "1", -1)

        g_Facade:SendNotification(NotifierEnum.REQUEST_PACK_DATA)      

        --mri.m_cMethods.DumpMemorySnapshot("C:/Users/OP/Desktop/Memory", "2", -1)
        --mri.m_cMethods.DumpMemorySnapshotComparedFile("C:/Users/OP/Desktop/Memory", "Compared", -1, "C:/Users/OP/Desktop/Memory/LuaMemRefInfo-All-[1].txt", "C:/Users/OP/Desktop/Memory/LuaMemRefInfo-All-[2].txt")
    end)

    self.uiRecruitmentOfficeBtn_.OnClicked:Add(function ()
        print("招募所")
        g_Facade:SendNotification(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA)
    end)

    self.uiPanel_:AddToViewport(0)

 end

function CMainCampsiteMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CMainCampsiteMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CMainCampsiteMediator.ListNotificationInterests(self)
    return {}
end

function CMainCampsiteMediator.HandleNotification(self, notification)
    print("CMainCampsiteMediator.HandleNotification...")
end

function CMainCampsiteMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CMainCampsiteMediator