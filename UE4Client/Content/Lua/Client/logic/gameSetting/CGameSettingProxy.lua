
local CLoginProxy = class("CLoginProxy", CProxy)

function CLoginProxy.ctor(self, name)
    CProxy.ctor(self, name)
end

function CProxy.OnRegister(self)
end

function CProxy.OnRemove(self)
end

return CLoginProxy