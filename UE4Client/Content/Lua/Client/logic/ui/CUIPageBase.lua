
local CUIPageBase = class("CUIPageBase", CObjectBase)

function CUIPageBase.ctor(self)
    CObjectBase.ctor(self)
end

function CUIPageBase.OnInit(self)
    CObjectBase.OnInit(self)
end

function CUIPageBase.OnDestroyed(self)
    CObjectBase.OnDestroyed(self)
end

return CUIPageBase