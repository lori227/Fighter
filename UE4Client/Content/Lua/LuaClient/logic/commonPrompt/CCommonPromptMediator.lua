local CCommonPromptMediator = class("CCommonPromptMediator", CMediator)

function CCommonPromptMediator.ctor(self, name)
    CMediator.ctor(self, name)
    self.promptRichText_ = nil
end

function CCommonPromptMediator.OnInit(self)
    print("CCommonPromptMediator -->OnInit")
    CMediator.OnInit(self)
end

function CCommonPromptMediator.OnDestroyed(self)
    print("CCommonPromptMediator -->OnDestroyed")

    self.promptRichText_ = nil

    self:OnDestroyedUI()
    CMediator.OnDestroyed(self)
end


function CCommonPromptMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CCommonPromptMediator -->OnRegisterCommand")
    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_RESULT_DISPLAY, CCommonPromptResponseResultDisplayCommand)
    g_Facade:RegisterCommand(NotifierEnum.SOCKET_DISCONNECT, CCommonPromptPopupDisplayCommand)
    g_Facade:RegisterCommand(NotifierEnum.RESOURCES_NOT_ENOUGH, CCommonPromptPopupDisplayCommand) 
    -------------------------------------注册Commond命令------------------------------------------------  
end


function CCommonPromptMediator.OnUnregisterCommand(self)
    print("CCommonPromptMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.RESPONSE_RESULT_DISPLAY)
    g_Facade:UnregisterCommand(NotifierEnum.SOCKET_DISCONNECT)
    g_Facade:UnregisterCommand(NotifierEnum.RESOURCES_NOT_ENOUGH) 
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CCommonPromptMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CCommonPromptMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/Comm/WB_ComPrompt.WB_ComPrompt')
    self.promptRichText_ = self.userWidget_:FindWidget('PromptRichText')
    self.userWidget_:FindWidget('ConfirmButton').OnClicked:Add(function ()
        CCommonPromptMediator:Close()
    end)

end

function CCommonPromptMediator.OnRefreshUI(self)

    self.promptRichText_:SetText(g_Facade:RetrieveProxy(ProxyEnum.COMMON_PROMPT):GetPrompt())
end

function CCommonPromptMediator.OnDestroyedUI(self)
    print("CCommonPromptMediator -->OnDestroyedUI")

    CMediator.OnDestroyUI(self)
end


function CCommonPromptMediator.OnShow(self)

    self:OnRefreshUI()

    self:AddToViewport(UIViewZOrderEnum.Top)
end

function CCommonPromptMediator.OnClose(self)

    self:RemoveFromViewport()
end

function CCommonPromptMediator.ListNotificationInterests(self)
    return { ProtobufEnum.MSG_RESULT_DISPLAY }
end

function CCommonPromptMediator.HandleNotification(self, notification)
    print("CCommonPromptMediator.HandleNotification...")
    
    local body = notification:GetBody()
    if body["MsgId"] == ProtobufEnum.MSG_RESULT_DISPLAY then 

        g_Facade:SendNotification(NotifierEnum.RESPONSE_RESULT_DISPLAY, body)

    end
end

return CCommonPromptMediator