local CRoleListRoleItemData = class("CRoleListRoleItemData")

function CRoleListRoleItemData.ctor(self, id, sanValue)
    self.id_ = id
    self.level_ = level
    self.lifeValue_ = lifeValue
    self.maxLifeValue_ = maxLifeValue
    self.sanValue_ = sanValue
    self.roleName_ = roleName
    self.imagePath_ = nil
end

function CRoleListRoleItemData.GetId(self)
	return self.id_
end

function CRoleListRoleItemData.SetId(self, id)
	self.id_ = id
end

function CRoleListRoleItemData.GetLevel(self)
	return self.level_
end

function CRoleListRoleItemData.SetLevel(self, level)
	self.level_ = level
end

function CRoleListRoleItemData.GetLifeValue(self)
	return self.lifeValue_
end

function CRoleListRoleItemData.SetLifeValue(self, lifeValue)
	self.lifeValue_ = lifeValue
end

function CRoleListRoleItemData.GetMaxLifeValue(self)
	return self.maxLifeValue_
end

function CRoleListRoleItemData.SetMaxLifeValue(self, maxLifeValue)
	self.maxLifeValue_ = maxLifeValue
end

function CRoleListRoleItemData.GetSanValue(self)
	return self.sanValue_
end

function CRoleListRoleItemData.SetSanValue(self, sanValue)
	self.sanValue_ = sanValue
end

function CRoleListRoleItemData.GetRoleName(self)
	return self.roleName_
end

function CRoleListRoleItemData.SetRoleName(self, roleName)
	self.roleName_ = roleName
end

function CRoleListRoleItemData.GetImagePath(self)
	return self.imagePath_
end

function CRoleListRoleItemData.SetImagePath(self, iamgePath)
	self.imagePath_ = iamgePath
end


return CRoleListRoleItemData