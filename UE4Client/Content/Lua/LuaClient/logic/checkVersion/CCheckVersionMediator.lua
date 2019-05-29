local CCheckVersionMediator = class("CCheckVersionMediator", CMediator)

function CCheckVersionMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
end

function CCheckVersionMediator.Destroy(self)
    print("CCheckVersionMediator -->Destroy")

    self.uiPanel_ = nil

    CMediator.Destroy(self)
end

function CCheckVersionMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CCheckVersionMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_CHECK_VERSION,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_CHECK_VERSION,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CCheckVersionMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CCheckVersionMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_VRESION_JSON, CCheckVersionRequestVersionJsonCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CCheckVersionMediator.OnRemove(self)
    print("CCheckVersionMediator -->OnRemove")

    self.uiPanel_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_CHECK_VERSION)
    self:RemoveObserver(NotifierEnum.CLOSE_CHECK_VERSION)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_VRESION_JSON)

    CMediator.OnRemove(self)
end

function CCheckVersionMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CCheckVersionMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CCheckVersionMediator.OnCreatePanel(self)
    
end

function CCheckVersionMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CCheckVersionMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CCheckVersionMediator.ListNotificationInterests(self)
    return {}
end

function CCheckVersionMediator.HandleNotification(self, notification)
    print("CCheckVersionMediator.HandleNotification...")
end

return CCheckVersionMediator