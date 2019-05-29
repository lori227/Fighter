local CServerAuthMediator = class("CBatchUpdateMediator", CMediator)

function CServerAuthMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.uiLoginButton_ = nil
    self.uiAccountEditText_ = nil
    self.uiListText1_ = nil
end

function CServerAuthMediator.Destroy(self)
    print("CServerAuthMediator -->Destroy")
    
    self.uiPanel_ = nil
    self.uiLoginButton_ = nil
    self.uiAccountEditText_ = nil
    self.uiListText1_ = nil

    CMediator.Destroy(self)
end

function CServerAuthMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CServerAuthMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_SERVER_AUTH,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_SERVER_AUTH,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CServerAuthMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CServerAuthMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_AUTH_INFO, CServerAuthRequestAuthInfoCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CServerAuthMediator.OnRemove(self)
    print("CServerAuthMediator -->OnRemove")

    self.uiPanel_ = nil
    self.uiLoginButton_ = nil
    self.uiAccountEditText_ = nil
    self.uiListText1_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_SERVER_AUTH)
    self:RemoveObserver(NotifierEnum.CLOSE_SERVER_AUTH)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_AUTH_INFO)

    CMediator.OnRemove(self)
end

function CServerAuthMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CServerAuthMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CServerAuthMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UIServerAuth.WB_UIServerAuth')
    print(self.uiPanel_)
    self.uiLoginButton_ = self.uiPanel_:FindWidget('ButtonLogin')
    self.uiRegisterButton_ = self.uiPanel_:FindWidget('ButtonRegister')

    print("self.uiLoginButton_:" .. tostring(self.uiLoginButton_))
    self.uiAccountEditText_ = self.uiPanel_:FindWidget('EditTextAccount')
    print("self.uiAccountEditText_:" .. tostring(self.uiAccountEditText_))
    self.uiPasswordEditText_ = self.uiPanel_:FindWidget('EditTextPassword')

    self.uiRegisterButton_.OnClicked:Add(function ()
        local count = math.random(10000,9999999)
        self.uiAccountEditText_:SetText(count)
        local password = math.random(10000,99999)
        self.uiPanel_.Password = password
    end)
 
    self.uiLoginButton_.OnClicked:Add(function()             
        g_Facade:SendNotification(NotifierEnum.REQUEST_AUTH_INFO)
    end)
    
    self.uiAccountEditText_.OnTextChanged:Add(CServerAuthMediator.OnUIEidtTextChanged)



    self.uiButton70_ = self.uiPanel_:FindWidget('Button_70')
    self.uiButton70_.OnClicked:Add(function ()
        --切换到主营地状态
        local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.SERVER_AUTH, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toMainCampsiteEvent)
    end)
 end

function CServerAuthMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CServerAuthMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
        g_GameFSM:DoEvent(toLoginEvent)
    end
end

function CServerAuthMediator.ListNotificationInterests(self)
    return {}
end

function CServerAuthMediator.HandleNotification(self, notification)
    print("CServerAuthMediator.HandleNotification...")
end

function CServerAuthMediator.OnUIEidtTextChanged(editText)
    if editText then
        --print("CServerAuthMediator.OnUIEidtTextChanged editText:%s", tostring(editText))

        local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
        serverAuthProxy:SetAccount(tostring(editText))
    end
end

return CServerAuthMediator