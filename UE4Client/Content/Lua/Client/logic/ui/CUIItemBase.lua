
local CUIItemBase = class("CUIItemBase", CObjectBase)

function CUIItemBase.ctor(self)
    CObjectBase.ctor(self)
end

function CUIItemBase.OnInit(self)
    CObjectBase.OnInit(self)
end

function CUIItemBase.OnDestroyed(self)
    CObjectBase.OnDestroyed(self)
end

return CUIItemBase