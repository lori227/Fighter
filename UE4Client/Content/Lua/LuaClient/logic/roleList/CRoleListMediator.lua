local CRoleListMediator = class("CRoleListMediator", CMediator, CUIItemContainerBase)

function CRoleListMediator.ctor(self, name)
    CMediator.ctor(self, name)
    CUIItemContainerBase.ctor(self)

    self.show_ = false
    self.curItem_ = nil

    --角色列表
    self.hasNewRoleData_ = false
    self.needRefreshRoleList_ = false
    self.roleItemList_ = {}
    self.curRoleItem_ = nil
    self.roleListUI_ = nil
    self.leftMouseButtonDown_ = false
    

    --英雄数量
    self.playerRoleNum_ = 0
    self.roleMaxNum_ = 90

end

function CRoleListMediator.OnInit(self)
    print("CRoleListMediator -->OnInit")
    CMediator.OnInit(self)
end



function CRoleListMediator.OnDestroyed(self)
    print("CRoleListMediator -->OnDestroyed")
   
    self.show_ = false

    --角色列表
    self.hasNewRoleData_ = false
    self.needRefreshRoleList_ = false
    self.roleItemList_ = {}
    self.curRoleItem_ = nil
    self.roleListUI_ = nil
    self.leftMouseButtonDown_ = false
    

    --英雄数量
    self.playerRoleNum_ = 0
    self.roleMaxNum_ = 90
    CMediator.OnDestroyed(self)
end


function CRoleListMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CRoleListMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.ROLE_LIST_REFRESH_UI, CRoleListRefreshUICommand)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_LIST_REQUEST_DATA, CRoleListRequestDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_LIST_RESPONSE_DATA, CRoleListResponseDataCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CRoleListMediator.OnUnregisterCommand(self)
    print("CRoleListMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.ROLE_LIST_REFRESH_UI)
    g_Facade:UnregisterCommand(NotifierEnum.ROLE_LIST_REQUEST_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.ROLE_LIST_RESPONSE_DATA)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CRoleListMediator.OnCreateUI(self)
    print("CRoleListMediator -->OnCreateUI")
    CMediator.OnCreateUI(self)
    
    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleList/WB_RoleList.WB_RoleList') 
    print(self.userWidget_)
    self.uiItemParent_ = self.userWidget_:FindWidget('RoleList')
    self.uiText_ = self.userWidget_:FindWidget('Text')
    self.uiRoleNum_ = self.userWidget_:FindWidget('RoleNum')

    self.anim_ = self.userWidget_.OpenRoleList

    g_Facade:SendNotification(NotifierEnum.ROLE_LIST_RESPONSE_DATA)
    
end

function CRoleListMediator.OnDestroyedUI(self)
    print("CRoleListMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end



function CRoleListMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport(0)
end

function CRoleListMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
end

function CRoleListMediator.ListNotificationInterests(self)
    return {}
end

function CRoleListMediator.HandleNotification(self, notification)
    print("CRecruitmentOfficeMediator.HandleNotification...")
end

function CRoleListMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CRoleListMediator