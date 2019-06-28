local CLoginProxy = class("CLoginProxy", CProxy)

function CLoginProxy.ctor(self, name)
    CProxy.ctor(self, name)

    self.emporaryPlayerName_ = nil
end

function CLoginProxy.SetEmporaryPlayerName(self, emporaryPlayerName)
	self.emporaryPlayerName_ = emporaryPlayerName
end

function CLoginProxy.GetEmporaryPlayerName(self)
	return self.emporaryPlayerName_
end

return CLoginProxy