local CServerAuthMediator = class("CServerAuthMediator", CMediator)

function CServerAuthMediator.ctor(self, name)
    CMediator.ctor(self, name)
end

function CServerAuthMediator.OnInit(self)
    print("CServerAuthMediator -->OnInit")
    CMediator.OnInit(self)
end

function CServerAuthMediator.OnDestroyed(self)
    print("CServerAuthMediator -->OnDestroyed")
    
    self:OnDestroyedUI()

    CMediator.OnDestroyed(self)
end


function CServerAuthMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CServerAuthMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_AUTH_INFO, CServerAuthRequestAuthInfoCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CServerAuthMediator.OnUnregisterCommand(self)
    print("CServerAuthMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_AUTH_INFO)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CServerAuthMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CServerAuthMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UIServerAuth.WB_UIServerAuth')
    self.uiLoginButton_ = self.userWidget_:FindWidget('ButtonLogin')
    self.uiRegisterButton_ = self.userWidget_:FindWidget('ButtonRegister')
    self.uiAccountEditText_ = self.userWidget_:FindWidget('EditTextAccount')
    self.uiPasswordEditText_ = self.userWidget_:FindWidget('EditTextPassword')

    self.uiRegisterButton_.OnClicked:Add(function ()
        local count = math.random(10000,9999999)
        self.uiAccountEditText_:SetText(count)
        local password = math.random(10000,99999)
        self.uiPasswordEditText_:SetText(password)
    end)
 
    self.uiLoginButton_.OnClicked:Add(function()             
        g_Facade:SendNotification(NotifierEnum.REQUEST_AUTH_INFO)
    end)
    
    self.uiAccountEditText_.OnTextChanged:Add(CServerAuthMediator.OnUIEidtTextChanged)
 end


function CServerAuthMediator.OnDestroyedUI(self)
    print("CServerAuthMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end

function CServerAuthMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport(0)
end

function CServerAuthMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
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