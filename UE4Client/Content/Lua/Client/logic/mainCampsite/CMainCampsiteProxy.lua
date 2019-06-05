local CMainCampsiteProxy = class("CMainCampsiteProxy", CProxy)

function CMainCampsiteProxy.ctor(self, name)
    CProxy.ctor(self, name)
	   
	self.playerName_ = "玩家名字七个字"
end

function CMainCampsiteProxy.SetPlayerName(self, playername)
	self.playerName_ = playername
end

function CMainCampsiteProxy.GetPlayerName(self)
	return self.playerName_
end

return CMainCampsiteProxy