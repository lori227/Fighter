local CCheckVersionMediator = class("CCheckVersionMediator", CMediator)

function CCheckVersionMediator.ctor(self, name)
    CMediator.ctor(self, name)
end

function CCheckVersionMediator.OnInit(self)
    print("CCheckVersionMediator -->OnInit")
    CMediator.OnInit(self)
end

function CCheckVersionMediator.OnDestroyed(self)
    print("CCheckVersionMediator -->OnDestroyed")

    self:OnDestroyedUI()

    CMediator.OnDestroyed(self)
end


function CCheckVersionMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CCheckVersionMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_VRESION_JSON, CCheckVersionRequestVersionJsonCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CCheckVersionMediator.OnUnregisterCommand(self)
    print("CCheckVersionMediator -->OnUnregisterCommand")

    -------------------------------------移除注册Commond命令------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_VRESION_JSON)
    -------------------------------------移除注册Commond命令------------------------------------------------

    CMediator.OnUnregisterCommand(self)
end

function CCheckVersionMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CCheckVersionMediator -->OnCreateUI")

end

function CCheckVersionMediator.OnDestroyedUI(self)
    print("CCheckVersionMediator -->OnDestroyedUI")

    CMediator.OnDestroyedUI(self)
end



function CCheckVersionMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport()
end

function CCheckVersionMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
end

function CCheckVersionMediator.ListNotificationInterests(self)
    return {}
end

function CCheckVersionMediator.HandleNotification(self, notification)
    print("CCheckVersionMediator.HandleNotification...")
end

return CCheckVersionMediator