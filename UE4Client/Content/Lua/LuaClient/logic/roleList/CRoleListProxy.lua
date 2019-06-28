local CRoleListProxy = class("CRoleListProxy", CProxy)

function CRoleListProxy.ctor(self, name)
    CProxy.ctor(self, name)
    --角色列表
    self.roleItemDataList_ = {}
    self.itemTotal_ = 20
    self.roleNum_ = 0
end

function CRoleListProxy.AddRoleItemData(self, roleItemData)
    table.insert(self.roleItemDataList_, roleItemData)
end

function CRoleListProxy.RemoveRoleItemData(self)
    --table.remove(self.roleList_, id)
end


function CRoleListProxy.GetItemTotal(self)
	return self.itemTotal_
end

function CRoleListProxy.SetItemTotal(self, gridSnum)
	self.itemTotal_ = itemTotal
end

function CRoleListProxy.GetRoleNum(self)
    return self.roleNum_
end

function CRoleListProxy.SetRoleNum(self, gridSnum)
    self.roleNum_ = roleNum
end


return CRoleListProxy