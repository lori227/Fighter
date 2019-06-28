local CRoleInformationBuffItemData = class("CRoleInformationBuffItemData")

function CRoleInformationBuffItemData.ctor(self, id, buffContent)
    self.id_ = id
    self.buffContent_ = buffContent
    self.imagePath_ = nil
end

function CRoleInformationBuffItemData.GetId(self)
	return self.id_
end

function CRoleInformationBuffItemData.SetId(self, id)
	self.id_ = id
end

function CRoleInformationBuffItemData.GetBuffContent(self)
	return self.buffContent_
end

function CRoleInformationBuffItemData.SetBuffContent(self, buffContent)
	self.buffContent_ = buffContent
end

function CRoleInformationBuffItemData.GetImagePath(self)
	return self.imagePath_
end

function CRoleInformationBuffItemData.SetImagePath(self, iamgePath)
	self.imagePath_ = iamgePath
end


return CRoleInformationBuffItemData