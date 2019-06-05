local CLoginResponseLoginCommand = class("CLoginResponseLoginCommand", CCommand)

function CLoginResponseLoginCommand.ctor(self)
	CCommand.ctor(self)
end

function CLoginResponseLoginCommand.Execute(self, notification)
	print("CLoginResponseLoginCommand.Execute...")

	self:ToLogin(notification)
end

function CLoginResponseLoginCommand.ToLogin(self, notification)
	local body = notification:GetBody()
    local t = pb.decode("KFMsg.MsgLoginAck", body["Data"])
    local playerId = t["playerid"]
    print("******************************playerId:" .. playerId)

    local loginProxy = g_Facade:RetrieveProxy(ProxyEnum.LOGIN)
    local loginMediator = g_Facade:RetrieveMediator(ProxyEnum.LOGIN)
    loginProxy:SetPlayerId(playerId)

    if false then 
        --切换到主营地状态
        local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
        g_GameFSM:DoEvent(toMainCampsiteEvent)
    else
        if loginMediator.uiLoginSetName_ == nil then
            local loginSetNameUI = slua.loadUI('/Game/Blueprints/UI/Widget/Login/WB_LoginSetName.WB_LoginSetName')
            loginMediator.uiLoginSetName_ = loginSetNameUI
            local nameText = loginSetNameUI:FindWidget('NameText')
            local confirmBtn = loginSetNameUI:FindWidget('ConfirmBtn')
            
            nameText.OnTextChanged:Add(function (editText)
                if editText then
                    loginProxy:SetPlayerName(tostring(editText))
                    g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):SetPlayerName(tostring(editText))
                end
            end)
            confirmBtn.OnClicked:Add(function ()
                print(loginProxy:GetPlayerName())
                --切换到主营地状态
                local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
                g_GameFSM:DoEvent(toMainCampsiteEvent)
                loginMediator:SetTargetVisibility(loginSetNameUI, 1)  
            end)
            
            loginMediator.uiLoginSetName_:AddToViewport(1)
        else
            loginMediator:SetTargetVisibility(loginSetNameUI, 4)  
        end
    end
end

return CLoginResponseLoginCommand