local CMainCampsiteMediator = class("CMainCampsiteMediator", CMediator)

function CMainCampsiteMediator.ctor(self, name)
    CMediator.ctor(self, name)
end

function CMainCampsiteMediator.OnInit(self)
    print("CMainCampsiteMediator -->OnInit")
    CMediator.OnInit(self)
end

function CMainCampsiteMediator.OnDestroyed(self)
    print("CMainCampsiteMediator -->OnDestroyed")

    self:OnDestroyedUI()

    CMediator.OnDestroyed(self)
end


function CMainCampsiteMediator.OnRegisterCommand(self)
    print("CMainCampsiteMediator -->OnRegisterCommand")
    CMediator.OnRegisterCommand(self)
    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_PACK_DATA, CMainCampsiteRequestPackDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA, CMainCampsiteRequestRecruitmentOfficeDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_ROLE_LIST_DATA, CMainCampsiteRequestRoleListDataCommand)

    g_Facade:RegisterCommand(NotifierEnum.COMMON_REQUEST_ADD_DATA, CMainCampsiteRequestAddDataCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CMainCampsiteMediator.OnUnregisterCommand(self)
    print("CMainCampsiteMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_PACK_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_ROLE_LIST_DATA)

    g_Facade:UnregisterCommand(NotifierEnum.COMMON_REQUEST_ADD_DATA) 
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CMainCampsiteMediator.OnCreateUI(self)
    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/MainCampsite/WB_MainCampsite.WB_MainCampsite')
    self.uiPlayerNameText_ = self.userWidget_:FindWidget('PlayerNameText')
    self.uiPlayerIdText_ = self.userWidget_:FindWidget('PlayerIdText')
    self.ui1vs1Btn_ = self.userWidget_:FindWidget('1VS1Btn')
    self.uiPackBtn_ = self.userWidget_:FindWidget('WarehouseBtn')
    self.uiRecruitmentOfficeBtn_ = self.userWidget_:FindWidget('RecruitmentOfficeBtn')
    self.uiRoleListBtn_ = self.userWidget_:FindWidget('RoleListBtn')
    self.uiTeamManagementBtn_ = self.userWidget_:FindWidget('TeamManagementBtn')
    self.userWidget_:FindWidget('MoneyText'):SetText(g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetMoney())

    self.uiPlayerNameText_:SetText(g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetPlayerName())
    self.uiPlayerIdText_:SetText("玩家ID : " .. g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetPlayerId())
    
    self.ui1vs1Btn_.OnClicked:Add(function ()
        --切换到PVP匹配状态
        local toPVPMatchEvent = CToPVPMatchEvent.New(GameFSMStateIdEnum.MAIN_CAMPSITE, GameFSMStateIdEnum.PVP_MATCH, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toPVPMatchEvent)
    end)

    self.uiPackBtn_.OnClicked:Add(function ()
        print("背包")
        --local mri = require("memory/MemoryReferenceInfo")
        --mri.m_cMethods.DumpMemorySnapshot("C:/Users/OP/Desktop/Memory", "1", -1)
        if g_View:HasShow(CPackMediator) then
            CPackMediator:Close()  
        else
            CPackMediator:Show()   
        end
        --mri.m_cMethods.DumpMemorySnapshot("C:/Users/OP/Desktop/Memory", "2", -1)
        --mri.m_cMethods.DumpMemorySnapshotComparedFile("C:/Users/OP/Desktop/Memory", "Compared", -1, "C:/Users/OP/Desktop/Memory/LuaMemRefInfo-All-[1].txt", "C:/Users/OP/Desktop/Memory/LuaMemRefInfo-All-[2].txt")
    end)
    
    self.uiRecruitmentOfficeBtn_.OnClicked:Add(function ()
        print("招募所")
        --g_Facade:SendNotification(NotifierEnum.REQUEST_RECRUITMENT_OFFICE_DATA)
        CRecruitmentOfficeMediator:Show()
    end)

    self.uiRoleListBtn_.OnClicked:Add(function ()
        print("角色列表")
        if g_View:HasShow(CRoleListMediator) then
            CRoleListMediator:Close()  
        else
            CRoleListMediator:Show()   
        end
    end)

    self.uiTeamManagementBtn_.OnClicked:Add(function ()
        print("队伍管理")
        CTeamManagementMediator:Show()
    end)
 end

function CMainCampsiteMediator.OnDestroyedUI(self)
    print("CMainCampsiteMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end

function CMainCampsiteMediator.OnShow(self)
    

    self:AddToViewport(0)
end

function CMainCampsiteMediator.OnClose(self)
   

    self:RemoveFromViewport()
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