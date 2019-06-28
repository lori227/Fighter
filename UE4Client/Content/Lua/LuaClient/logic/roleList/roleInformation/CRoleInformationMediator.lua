local CRoleInformationMediator = class("CRoleInformationMediator", CMediator)

function CRoleInformationMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.show_ = false

    --角色BUFF列表
    self.roleBuffList_ = {}
    self.roleBuffUI_ = nil
    self.hasNewRoleBuffData_ = false
    self.needRefreshBuff_ = false
    
end

function CRoleInformationMediator.OnInit(self)
    print("CRoleInformationMediator -->OnInit")
    CMediator.OnInit(self)
end

function CRoleInformationMediator.OnDestroyed(self)
    print("CRoleInformationMediator -->OnDestroyed")
   
    self.show_ = false

    --角色BUFF列表
    self.roleBuffList_ = {}
    self.roleBuffUI_ = nil
    self.hasNewBuffData_ = false
    self.needRefreshBuff_ = false
end


function CRoleInformationMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CRoleInformationMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.ROLE_INFORMATION_REFRESH_UI, CRoleInformationRefreshUICommand)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_INFORMATION_RESPONSE_DATA, CRoleInformationResponseDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_INFORMATION_BUFF_REFRESH_UI, CRoleInformationRefreshUICommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CRoleInformationMediator.OnRemoveCommand(self)
    print("CRoleInformationMediator -->OnRemoveCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:RemoveCommand(NotifierEnum.ROLE_INFORMATION_REFRESH_UI)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_INFORMATION_RESPONSE_DATA)
    g_Facade:RegisterCommand(NotifierEnum.ROLE_INFORMATION_BUFF_REFRESH_UI)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnRemoveCommand(self)
end


function CRoleInformationMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CRoleInformationMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_RoleInformation.WB_RoleInformation') 
    print(self.userWidget_)
    
    
    self.shutBtn_ = self.userWidget_:FindWidget('ShutBtn')
    self.lockBtn_ = self.userWidget_:FindWidget('LockBtn')
    self.fireBtn_ = self.userWidget_:FindWidget('FireBtn')
    self.genderIcon_ = self.userWidget_:FindWidget('GenderIcon')
    self.professionImage_ = self.userWidget_:FindWidget('ProfessionImage')
    self.weaponsImage_ = self.userWidget_:FindWidget('WeaponsImage')

   

    --按钮返回
    self.shutBtn_.OnClicked:Add(function ()
    CRoleInformationMediator:Close()
    end)

    --ESC返回  
    self.userWidget_.RoleInformationOnEscKeyDown:Add(function (geometry,keyEvent)
        local KismetInputLibrary = import("KismetInputLibrary")
        if KismetInputLibrary.GetKey(keyEvent).KeyName == "Escape" then
            CRoleInformationMediator:Close()
        end
    end)


    self.lockBtn_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "锁定说明")
    end)
    self.lockBtn_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "锁定说明")
    end)

    self.fireBtn_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "解雇说明")
    end)
    self.fireBtn_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "解雇说明")
    end)

    self.genderIcon_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "性别说明")
    end)
    self.genderIcon_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "性别说明")
    end)

    self.professionImage_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "职业说明")
    end)
    self.professionImage_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "职业说明")
    end)

    self.weaponsImage_.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
    end)
    self.weaponsImage_.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
    end)

    -- g_Facade:SendNotification(NotifierEnum.ROLE_INFORMATION_RESPONSE_DATA)
end

 function CRoleInformationMediator.OnDestroyedUI(self)
    print("CRoleInformationMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end

function CRoleInformationMediator.OnShow(self)
    print("CRoleInformationMediator -->OnShow")
    self.show_ = true
    g_Facade:SendNotification(NotifierEnum.ROLE_INFORMATION_REFRESH_UI)
    -- self.userWidget_:PlayAnimation(self.userWidget_.OpenRoleList, 0, 1, 3, 1) 
    self:AddToViewport(50)
end

function CRoleInformationMediator.Refresh(self)
    
end

function CRoleInformationMediator.OnClose(self)
    print("CRoleInformationMediator -->OnClose")
    self.show_ = false
    -- self.userWidget_:PlayAnimation(self.userWidget_.OpenRoleList, 0, 1, 1, 1)
    self:RemoveFromViewport()
end

function CRoleInformationMediator.ListNotificationInterests(self)
    return {}
end

function CRoleInformationMediator.HandleNotification(self, notification)
    print("CRecruitmentOfficeMediator.HandleNotification...")
end

function CRoleInformationMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CRoleInformationMediator