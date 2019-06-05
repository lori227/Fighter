local CCheckVersionProxy = class("CCheckVersionProxy", CProxy)

function CCheckVersionProxy.ctor(self, name)
    CProxy.ctor(self, name)
end

function CCheckVersionProxy.SetAccount(self, account)
	self.account_ = account
end

return CCheckVersionProxy