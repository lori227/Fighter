local CRoleInformationAttributeItemData = class("CRoleInformationAttributeItemData")

function CRoleInformationAttributeItemData.ctor(self, id, attributeType, attributeValue)
    self.id_ = id
    self.attributeType_ = attributeType
    self.attributeValue_ = 9999
end

function CRoleInformationAttributeItemData.GetId(self)
	return self.id_
end

function CRoleInformationAttributeItemData.SetId(self, id)
	self.id_ = id
end

function CRoleInformationAttributeItemData.GetAttributeType(self)
	return self.attributeType_
end

function CRoleInformationAttributeItemData.SetAttributeType(self, attributeType)
	self.attributeType_ = attributeType
end

function CRoleInformationAttributeItemData.GetAttributeValue(self)
	return self.attributeValue_
end

function CRoleInformationAttributeItemData.SetAttributeValue(self, attributeValue)
	self.attributeValue_ = attributeValue
end


return CRoleInformationAttributeItemData