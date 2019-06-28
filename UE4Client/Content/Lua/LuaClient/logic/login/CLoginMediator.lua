local CLoginMediator = class("CLoginMediator", CMediator)

function CLoginMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiResultText_ = nil
    self.uiLoginSetName_ = nil
end

function CLoginMediator.OnInit(self)
    print("CLoginMediator -->OnInit")
    CMediator.OnInit(self)
end

function CLoginMediator.OnDestroyed(self)
    print("CLoginMediator -->OnDestroyed")
    
    self.uiResultText_ = nil
    self.uiLoginSetName_ = nil

    self:OnDestroyedUI()

    CMediator.OnDestroyed(self)
end


function CLoginMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CLoginMediator -->OnRegisterCommand")
    -------------------------------------注册Command命令-------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_LOGIN, CLoginRequestLoginCommand)
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_LOGIN, CLoginResponseLoginCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_SET_DATA, CLoginRequestSetDataCommand)
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_UPDATA_DATA, CLoginResponseUpdataDataCommand)
    -------------------------------------注册Command命令-------------------------------------------------
end

function CLoginMediator.OnUnregisterCommand(self)
    print("CLoginMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_LOGIN)
    g_Facade:UnregisterCommand(NotifierEnum.RESPONSE_LOGIN)
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_SET_DATA)
    g_Facade:UnregisterCommand(NotifierEnum.RESPONSE_UPDATA_DATA)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end

function CLoginMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CCheckVersionMediator -->OnCreateUI")
    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UILoginEx.WB_UILoginEx')
end

function CLoginMediator.OnDestroyedUI(self)
    print("CLoginMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end



function CLoginMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport()
end

function CLoginMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
end

function CLoginMediator.ListNotificationInterests(self)
    return { ProtobufEnum.MSG_LOGIN_ACK, ProtobufEnum.MSG_SYNC_UPDATE_DATA}
end

function CLoginMediator.HandleNotification(self, notification)
    print("CLoginMediator.HandleNotification...")

    local body = notification:GetBody()

    if body["MsgId"] == ProtobufEnum.MSG_LOGIN_ACK then 

        g_Facade:SendNotification(NotifierEnum.RESPONSE_LOGIN, body)    

    elseif body["MsgId"] == ProtobufEnum.MSG_SYNC_UPDATE_DATA then

        g_Facade:SendNotification(NotifierEnum.RESPONSE_UPDATA_DATA, body)

    end 
end


function CLoginMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CLoginMediator