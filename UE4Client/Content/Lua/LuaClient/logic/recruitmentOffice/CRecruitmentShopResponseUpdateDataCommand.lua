local CRecruitmentShopResponseUpdateDataCommand = class("CRecruitmentShopResponseUpdateDataCommand", CCommand)

function CRecruitmentShopResponseUpdateDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentShopResponseUpdateDataCommand.Execute(self, notification)
	print("CRecruitmentShopResponseUpdateDataCommand.Execute...")

	self:UpdateData(notification)
end

function CRecruitmentShopResponseUpdateDataCommand.UpdateData(self, notification)
    local mainCampsiteProxy = g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE)
    local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
    local recruitmentOfficeMediator = CRecruitmentOfficeMediator:Get()

    local body = notification:GetBody()
    --table.print(body)

    if body.Op == "Update" then
        local key = "player_recruitcount_" .. tostring(mainCampsiteProxy:GetPlayerId())
        if body.Key == key then
           recruitmentOfficeProxy:SetRecruitCount(body.Value)
        end
        key = "player_money_" .. tostring(mainCampsiteProxy:GetPlayerId())
        if body.Key == key then
           mainCampsiteProxy:SetMoney(body.Value)
        end

    elseif body.Op == "Add" then
        if body.Key == "player_recruit" then
            local cost = json.decode(g_NetPlayerDataCtrl:GetMyPlayerDataValue_3("recruit", body.Value.uuid, "cost"))[1]
            local recruitShopData = {  
                uuid = body.Value.uuid,
                cost = cost,
                race = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", body.Value.uuid, "hero", "race"),
                profession = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", body.Value.uuid, "hero", "profession"),
                name = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", body.Value.uuid, "hero", "name"),
            }
            recruitmentOfficeProxy:AddRecruitShopData(recruitShopData)
            recruitmentOfficeMediator.hasNewShopData_ = true

            local keyName = "player_recruit_" .. tostring(body.Value.uuid)
            recruitmentOfficeMediator:RegisterObserver(keyName, "HandleNotification")
        
        elseif body.Key == "player_hero" and g_GameFSM:GetCurStateId() == GameFSMStateIdEnum.MAIN_CAMPSITE then
            local newHeroShowData = {uuid = body.Value.uuid, race = body.Value.race, profession = body.Value.profession, name = body.Value.name}
            mainCampsiteProxy:AddHeroData(body.Value)
            recruitmentOfficeProxy:AddNewHeroShowData(newHeroShowData)
            CNewHeroDisplayMediator:Show()
        end

    elseif body.Op == "Remove" then
        local key = string.sub(body.Key, 1, 15)
        if key == "player_recruit_" then
            local uuid = string.sub(body.Key, 16, string.len(body.Key))
            if uuid then
                recruitmentOfficeProxy:RemoveRecruitShopData(uuid) 
                recruitmentOfficeMediator:UnregisterObserver("player_recruit_" .. uuid)
                recruitmentOfficeMediator.hasNewShopData_ = true
            end          
        end 
    end
    
    if recruitmentOfficeMediator.needRefreshShop_ then
        recruitmentOfficeMediator:OnRefreshUI()
    end
end

return CRecruitmentShopResponseUpdateDataCommand