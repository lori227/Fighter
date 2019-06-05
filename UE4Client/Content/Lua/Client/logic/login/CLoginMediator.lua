local CLoginMediator = class("CLoginMediator", CMediator)

function CLoginMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.uiLoginningText_ = nil
end

function CLoginMediator.Destroy(self)
    print("CLoginMediator -->Destroy")
    
    self.uiPanel_ = nil
    self.uiLoginningText_ = nil
    self.uiLoginSetName_ = nil

    CMediator.Destroy(self)
end

function CLoginMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CLoginMediator -->OnRegisterUI")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_LOGIN,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_LOGIN,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CLoginMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CLoginMediator -->OnRegisterCommand")
    -------------------------------------注册Command命令-------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_LOGIN, CLoginRequestLoginCommand)
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_LOGIN, CLoginResponseLoginCommand)
    -------------------------------------注册Command命令-------------------------------------------------
end

function CLoginMediator.OnRemove(self)
    print("CLoginMediator -->OnRemove")

    self.uiPanel_ = nil
    self.uiLoginningText_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_LOGIN)
    self:RemoveObserver(NotifierEnum.CLOSE_LOGIN)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_LOGIN)
    g_Facade:RemoveCommand(NotifierEnum.RESPONSE_LOGIN)

    CMediator.OnRemove(self)
end

function CLoginMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CLoginMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CLoginMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UILoginEx.WB_UILoginEx')
    print(self.uiPanel_)
    self.uiLoginningText_ = self.uiPanel_:FindWidget('TextLoginning')
    print(self.uiLoginningText_)

    self:SetTargetVisibility(self.uiLoginningText_, 3)
 end

function CLoginMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CLoginMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CLoginMediator.ListNotificationInterests(self)
    return { ProtobufEnum.MSG_LOGIN_ACK }
end

function CLoginMediator.HandleNotification(self, notification)
    print("CLoginMediator.HandleNotification...")

    local body = notification:GetBody()
    
    if body["MsgId"] == ProtobufEnum.MSG_LOGIN_ACK then 
        g_Facade:SendNotification(NotifierEnum.RESPONSE_LOGIN, body)
    end
end

function CLoginMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CLoginMediator