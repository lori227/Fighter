local CCommonPromptMediator = class("CCommonPromptMediator", CMediator)

function CCommonPromptMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.uiPromptText_ = nil
end

function CCommonPromptMediator.Destroy(self)
    print("CCommonPromptMediator -->Destroy")
    
    self.uiPanel_ = nil
    self.uiPromptText_ = nil

    CMediator.Destroy(self)
end

function CCommonPromptMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CCommonPromptMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_COMMON_PROMPT,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_COMMON_PROMPT,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CCommonPromptMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CCommonPromptMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_RESULT_DISPLAY, CCommonPromptResponseResultDisplayCommand)
    -------------------------------------注册Commond命令------------------------------------------------  
end

function CCommonPromptMediator.OnRemove(self)
    print("CCommonPromptMediator -->OnRemove")

    self.uiPanel_ = nil
    self.uiPromptText_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_LOGIN)
    self:RemoveObserver(NotifierEnum.CLOSE_LOGIN)

    g_Facade:RemoveCommand(NotifierEnum.RESPONSE_RESULT_DISPLAY)

    CMediator.OnRemove(self)
end

function CCommonPromptMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CCommonPromptMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CCommonPromptMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/Comm/WB_CommonPrompt.WB_CommonPrompt')
    print(self.uiPanel_)
    self.uiPromptText_ = self.uiPanel_:FindWidget('TextPrompt')
    print(self.uiPromptText_)

    local commonPromptProxy = g_Facade:RetrieveProxy(ProxyEnum.COMMON_PROMPT)
    local p = commonPromptProxy:GetPrompt()
    self.uiPromptText_:SetText(p)
 end

function CCommonPromptMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CCommonPromptMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CCommonPromptMediator.ListNotificationInterests(self)
    return { ProtobufEnum.MSG_RESULT_DISPLAY }
end

function CCommonPromptMediator.HandleNotification(self, notification)
    print("CCommonPromptMediator.HandleNotification...")

    local body = notification:GetBody()
    if body["MsgId"] == ProtobufEnum.MSG_RESULT_DISPLAY then 

        g_Facade:SendNotification(NotifierEnum.RESPONSE_RESULT_DISPLAY, notification)
        
    end
end

return CCommonPromptMediator