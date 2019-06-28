local CLoginResponseUpdataDataCommand = class("CLoginResponseUpdataDataCommand", CCommand)

function CLoginResponseUpdataDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CLoginResponseUpdataDataCommand.Execute(self, notification)
	print("CLoginResponseUpdataDataCommand.Execute...")

	self:ToUpdataData(notification)
end

function CLoginResponseUpdataDataCommand.ToUpdataData(self, notification)

    local body = notification:GetBody()

    local t = pbc.decode("KFMsg.MsgSyncUpdateData", body["Data"], body["DataLength"])
    -- print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    --     table.print(t)
    -- print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

    --切换到主营地状态
    local curStateId = g_GameFSM:GetCurStateId()
    if curStateId == GameFSMStateIdEnum.LOGIN then
        
        local playerName = nil
        playerName = t["pbdata"]["pbobject"][1]["value"]["pbstring"][1]["value"]

        if playerName ~= nil then
            CLoginMediator:Get():SetTargetVisibility(CLoginMediator:Get().uiLoginSetName_, 1) 
            g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):SetPlayerName(playerName) 
            g_Facade:RetrieveProxy(ProxyEnum.LOGIN):SetEmporaryPlayerName(nil)
        
            local toMainCampsiteEvent = CToMainCampsiteEvent.New(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE, FSMStackOpEnum.SET)
            g_GameFSM:DoEvent(toMainCampsiteEvent)
        end
    end

end

return CLoginResponseUpdataDataCommand