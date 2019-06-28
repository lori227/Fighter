local CPVPMatchMediator = class("CPVPMatchMediator", CMediator)

function CPVPMatchMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPVPMatchButton_ = nil
    self.uiPVPMatchingText_ = nil
    self.uiPVPMatchCancelButton_ = nil
    self.uiPVPMatchConfirmButton_ = nil
    self.uiPVPMatchSuccessText_ = nil
    self.uiPVPMatchEnterText_ = nil
    self.uiResultText_ = nil
end

function CPVPMatchMediator.OnInit(self)
    print("CPVPMatchMediator -->OnInit")
    CMediator.OnInit(self)
end

function CPVPMatchMediator.OnDestroyed(self)
    print("CPVPMatchMediator -->OnDestroyed")

    self.uiPVPMatchButton_ = nil
    self.uiPVPMatchingText_ = nil
    self.uiPVPMatchCancelButton_ = nil
    self.uiPVPMatchConfirmButton_ = nil
    self.uiPVPMatchSuccessText_ = nil
    self.uiPVPMatchEnterText_ = nil

    self:OnDestroyedUI()

    CMediator.OnDestroyed(self)
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

function CPVPMatchMediator.OnUnregisterCommand(self)
    print("CPVPMatchMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_PVP_MATCH_START)
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_PVP_MATCH_CANCEL)
    g_Facade:UnregisterCommand(NotifierEnum.REQUEST_PVP_MATCH_CONFIRM)

    g_Facade:UnregisterCommand(NotifierEnum.RESPONSE_MATCH_RESULT)
    g_Facade:UnregisterCommand(NotifierEnum.RESPONSE_BATTLE_REQ)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CPVPMatchMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CPVPMatchMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_UIPVPMatch.WB_UIPVPMatch')
    self.uiPVPMatchButton_ = self.userWidget_:FindWidget('ButtonPVPMatch')
    self.uiPVPMatchingText_ = self.userWidget_:FindWidget('TextMatching')
    self.uiPVPMatchCancelButton_ = self.userWidget_:FindWidget('ButtonPVPCancel')
    self.uiPVPMatchConfirmButton_ = self.userWidget_:FindWidget('ButtonPVPConfirm')
    self.uiPVPMatchSuccessText_ = self.userWidget_:FindWidget('TextMatchSuccess')
    self.uiPVPMatchEnterText_ = self.userWidget_:FindWidget('TextEnterPVPLevel')
    self.uiReturnBtn_ = self.userWidget_:FindWidget('ReturnBtn')
    self.uiResultText_ = self.userWidget_:FindWidget('ResultText')
    
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
    self:SetTargetVisibility(self.uiResultText_, 1) 
 end


function CPVPMatchMediator.OnDestroyedUI(self)
    print("CPVPMatchMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end


function CPVPMatchMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport(0)
end

function CPVPMatchMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
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