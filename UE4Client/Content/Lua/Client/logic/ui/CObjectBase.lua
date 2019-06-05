
local CObjectBase = class("CObjectBase")

function CObjectBase.ctor(self)
    
end

function CObjectBase.Init(self)
    self:OnInit()
end

function CObjectBase.OnInit(self)
    
end

function CObjectBase.Destroy(self)
    self:OnDestroyed()
end

function CObjectBase.OnDestroyed(self)
    
end

return CObjectBase