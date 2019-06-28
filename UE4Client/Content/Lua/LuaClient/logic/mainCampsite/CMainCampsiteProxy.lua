local CMainCampsiteProxy = class("CMainCampsiteProxy", CProxy)

function CMainCampsiteProxy.ctor(self, name)
    CProxy.ctor(self, name)

	self.playerName_ = ""
	self.playerId_ = 0
	self.playerIconSrc_ = "" 
	self.money_ = 0
	self.heroDataMap_ = {}
end

function CMainCampsiteProxy.Init(self)
	local money = g_NetPlayerDataCtrl:GetMyPlayerDataValue_1("money")
	if money then
		self:SetMoney(money)
	end
	local playId = g_NetPlayerDataCtrl:GetMyPlayerDataValue_1("id")
	if playId then
		self:SetPlayerId(playId)
	end
	local playName = g_NetPlayerDataCtrl:GetMyPlayerDataValue_2(self.playerId_, "name")	
	if playName then
		self:SetPlayerName(playName)
	end

	local keyName = "player_money_" .. tostring(self:GetPlayerId())
	CRecruitmentOfficeMediator:Get():RegisterObserver(keyName, "HandleNotification")
end

function CMainCampsiteProxy.RemoveHeroData(self)
	
end

function CMainCampsiteProxy.AddHeroData(self, heroData)
	table.insert(self.heroDataMap_, heroData)
	--table.print(self.heroDataMap_)
end

function CMainCampsiteProxy.SetPlayerName(self, playerName)
	self.playerName_ = playerName
end

function CMainCampsiteProxy.GetPlayerName(self)
	return self.playerName_
end

function CMainCampsiteProxy.SetPlayerId(self, playerId)
	self.playerId_ = playerId
end

function CMainCampsiteProxy.GetPlayerId(self)
	return self.playerId_
end

function CMainCampsiteProxy.SetPlayerIconSrc(self, playerIconSrc)
	self.playerIconSrc_ = playerIconSrc
end

function CMainCampsiteProxy.GetPlayerIconSrc(self)
	return self.playerIconSrc_
end

function CMainCampsiteProxy.GetMoney(self)
	return self.money_
end

function CMainCampsiteProxy.SetMoney(self, money)
	self.money_ = money
end

return CMainCampsiteProxy