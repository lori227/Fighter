local CLoginProxy = class("CLoginProxy", CProxy)

function CLoginProxy.ctor(self, name)
    CProxy.ctor(self, name)

    self.playerId_ = ""
    self.playerName_ = ""
end

function CLoginProxy.SetPlayerId(self, playerId)
	self.playerId_ = tostring(playerId)
	print(self.playerId_)
	print(type(self.playerId_))
end

function CLoginProxy.GetPlayerId(self)
	return self.playerId_
end

function CLoginProxy.SetPlayerName(self, playername)
	self.playerName_ = playername
end

function CLoginProxy.GetPlayerName(self)
	return self.playerName_
end

return CLoginProxy