local CLoginResponseLoginCommand = class("CLoginResponseLoginCommand", CCommand)

function CLoginResponseLoginCommand.ctor(self)
	CCommand.ctor(self)
end

function CLoginResponseLoginCommand.Execute(self, notification)
	print("CLoginResponseLoginCommand.Execute...")

    self.mainCampsiteProxy = g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE)

	self:ToLogin(notification)
end

function CLoginResponseLoginCommand.ToLogin(self, notification)
    local filePath = "FrameDefineMessage.proto"  
    protoc:loadfile(filePath)

	local body = notification:GetBody()
    local t = pbc.decode("KFMsg.MsgLoginAck", body["Data"], body["DataLength"])
    local playerId = t["playerid"]
    local playerData = t["playerdata"]
    local pbstring = playerData["pbobject"][1]["value"]["pbstring"]
    local playerName = nil
    if pbstring[1] ~= nil then
        playerName = pbstring[1]["value"]
    end    
    -- print("*****************************************************************************************************************************")
    --  table.print(t)
    -- print("*****************************************************************************************************************************")
    
    self.mainCampsiteProxy:SetPlayerId(tostring(playerId))

    if playerName ~= nil then 
        self.mainCampsiteProxy:SetPlayerName(tostring(playerName))
        --切换到主营地状态
        local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toMainCampsiteEvent)
    else
        local loginMediator = CLoginMediator:Get()
        if loginMediator.uiLoginSetName_ == nil then

            local loginSetNameUI = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_LoginSetName.WB_LoginSetName')
            local nameText = loginSetNameUI:FindWidget('NameText')
            local resultText = loginSetNameUI:FindWidget("ResultText")
            local confirmBtn = loginSetNameUI:FindWidget('ConfirmBtn')
            local retrunBtn  = loginSetNameUI:FindWidget('ReturnBtn') 
            
            nameText.OnTextChanged:Add(function (editText)
                if editText then 
                    g_Facade:RetrieveProxy(ProxyEnum.LOGIN):SetEmporaryPlayerName(tostring(editText))  
                    loginMediator:SetTargetVisibility(loginMediator.uiResultText_, 1)                
                end
            end)
            confirmBtn.OnClicked:Add(function ()
                g_Facade:SendNotification(NotifierEnum.REQUEST_SET_DATA)        
            end)
            retrunBtn.OnClicked:Add(function ()
                local MsgLogoutReq = {}   
                local str = pbc.encode("KFMsg.MsgLogoutReq", MsgLogoutReq)
                g_Network:Send(ProtobufEnum.MSG_LOGOUT_REQ, str, #str)
                g_Network:Shutdown()
                local toCheckVersionEvent = CToCheckVersionEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.CHECK_VERSION, FSMStackOpEnum.SET)
                g_GameFSM:DoEvent(toCheckVersionEvent)
                loginSetNameUI:RemoveFromViewport()
            end)

            loginMediator.uiResultText_ = resultText 
            loginMediator.uiLoginSetName_ = loginSetNameUI
            loginMediator:SetTargetVisibility(loginMediator.uiResultText_, 1) 
            loginMediator.uiLoginSetName_:AddToViewport(1)
        else
            loginMediator:SetTargetVisibility(loginMediator.uiResultText_, 1)
            loginMediator:SetTargetVisibility(loginSetNameUI, 4)  
            loginMediator.uiLoginSetName_:AddToViewport(1)
        end
    end
end


return CLoginResponseLoginCommand



 



 