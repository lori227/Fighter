local CPVPMatchMediator = class("CPVPMatchMediator", CMediator)

function CPVPMatchMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.uiPVPMatchButton_ = nil
    self.uiPVPMatchingText_ = nil
    self.uiPVPMatchCancelButton_ = nil
    self.uiPVPMatchConfirmButton_ = nil
    self.uiPVPMatchSuccessText_ = nil
    self.uiPVPMatchEnterText_ = nil

end

function CPVPMatchMediator.Destroy(self)
    print("CPVPMatchMediator -->Destroy")

    self.uiPanel_ = nil
    self.uiPVPMatchButton_ = nil
    self.uiPVPMatchingText_ = nil
    self.uiPVPMatchCancelButton_ = nil
    self.uiPVPMatchConfirmButton_ = nil
    self.uiPVPMatchSuccessText_ = nil
    self.uiPVPMatchEnterText_ = nil

    CMediator.Destroy(self)
end

function CPVPMatchMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CPVPMatchMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_PVP_MATCH,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_PVP_MATCH,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CPVPMatchMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CPVPMatchMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令-------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_PVP_MATCH_START, CPVPMatchRequestStartCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_PVP_MATCH_CANCEL, CPVPMatchRequestCancelCommand)
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_PVP_MATCH_CONFIRM, CPVPMatchRequestConfirmCommand)

    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_MATCH_RESULT, CPVPMatchResponseMatchResultCommand)
    g_Facade:RegisterCommand(NotifierEnum.RESPONSE_BATTLE_REQ, CPVPMatchResponseBattleReqCommand)
    -------------------------------------注册Commond命令-------------------------------------------------
end

function CPVPMatchMediator.OnRemove(self)
    print("CPVPMatchMediator -->OnRemove")

    self.uiPanel_ = nil
    self.uiPVPMatchButton_ = nil
    self.uiPVPMatchingText_ = nil
    self.uiPVPMatchCancelButton_ = nil
    self.uiPVPMatchConfirmButton_ = nil
    self.uiPVPMatchSuccessText_ = nil
    self.uiPVPMatchEnterText_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_PVP_MATCH)
    self:RemoveObserver(NotifierEnum.CLOSE_PVP_MATCH)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_PVP_MATCH_START)
    g_Facade:RemoveCommand(NotifierEnum.REQUEST_PVP_MATCH_CANCEL)
    g_Facade:RemoveCommand(NotifierEnum.REQUEST_PVP_MATCH_CONFIRM)

    g_Facade:RemoveCommand(NotifierEnum.RESPONSE_MATCH_RESULT)
    g_Facade:RemoveCommand(NotifierEnum.RESPONSE_BATTLE_REQ)

    CMediator.OnRemove(self)
end

function CPVPMatchMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CPVPMatchMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end

function CPVPMatchMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UIPVPMatch.WB_UIPVPMatch')
    print(self.uiPanel_)
    self.uiPVPMatchButton_ = self.uiPanel_:FindWidget('ButtonPVPMatch')
    print("self.uiPVPMatchButton_:" .. tostring(self.uiPVPMatchButton_))
    self.uiPVPMatchingText_ = self.uiPanel_:FindWidget('TextMatching')
    print("self.uiPVPMatchingText_:" .. tostring(self.uiPVPMatchingText_))
    self.uiPVPMatchCancelButton_ = self.uiPanel_:FindWidget('ButtonPVPCancel')
    print("self.uiPVPMatchCancelButton_:" .. tostring(self.uiPVPMatchCancelButton_))
    self.uiPVPMatchConfirmButton_ = self.uiPanel_:FindWidget('ButtonPVPConfirm')
    print("self.uiPVPMatchConfirmButton_:" .. tostring(self.uiPVPMatchConfirmButton_))
    self.uiPVPMatchSuccessText_ = self.uiPanel_:FindWidget('TextMatchSuccess')
    print("self.uiPVPMatchSuccessText_:" .. tostring(self.uiPVPMatchSuccessText_))
    self.uiPVPMatchEnterText_ = self.uiPanel_:FindWidget('TextEnterPVPLevel')
    print("self.uiPVPMatchEnterText_:" .. tostring(self.uiPVPMatchEnterText_))
    self.uiReturnBtn_ = self.uiPanel_:FindWidget('ReturnBtn')
    
    self.uiPVPMatchButton_.OnClicked:Add(function ()             
        g_Facade:SendNotification(NotifierEnum.REQUEST_PVP_MATCH_START)
    end)

    self.uiPVPMatchCancelButton_.OnClicked:Add(function ()
        g_Facade:SendNotification(NotifierEnum.REQUEST_PVP_MATCH_CANCEL)
    end)

    self.uiPVPMatchConfirmButton_.OnClicked:Add(function ()
        g_Facade:SendNotification(NotifierEnum.REQUEST_PVP_MATCH_CONFIRM)
    end)
    self.uiReturnBtn_.OnClicked:Add(function ()
         --切换到主营地状态
        local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toMainCampsiteEvent)
    end)

    self:SetTargetVisibility(self.uiPVPMatchingText_, 1)
    self:SetTargetVisibility(self.uiPVPMatchCancelButton_, 1)
    self:SetTargetVisibility(self.uiPVPMatchConfirmButton_, 1)
    self:SetTargetVisibility(self.uiPVPMatchSuccessText_, 1)
    self:SetTargetVisibility(self.uiPVPMatchEnterText_, 1)
 end


function CPVPMatchMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end

function CPVPMatchMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CPVPMatchMediator.ListNotificationInterests(self)
    return { ProtobufEnum.MSG_INFORM_MATCH_RESULT, ProtobufEnum.MSG_INFORM_BATTLE_REQ }
end

function CPVPMatchMediator.HandleNotification(self, notification)
    print("CPVPMatchMediator.HandleNotification...")

    --local dir = FToLuaPaths.ProjectContentDir()
    --local filePath = dir .. "Lua/LuaClient/logic/proto/ClientMessage.proto"
    local filePath = "ClientMessage.proto"
    protoc:loadfile(filePath)

    local body = notification:GetBody()
    if body["MsgId"] == ProtobufEnum.MSG_INFORM_MATCH_RESULT then 

        g_Facade:SendNotification(NotifierEnum.RESPONSE_MATCH_RESULT, body)

    elseif body["MsgId"] == ProtobufEnum.MSG_INFORM_BATTLE_REQ then
        
        g_Facade:SendNotification(NotifierEnum.RESPONSE_BATTLE_REQ, body)
        
    end
end

function CPVPMatchMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CPVPMatchMediator