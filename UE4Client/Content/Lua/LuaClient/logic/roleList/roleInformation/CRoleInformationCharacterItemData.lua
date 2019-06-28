local CRoleInformationCharacterItemData = class("CRoleInformationCharacterItemData")

function CRoleInformationCharacterItemData.ctor(self, id, characterType)
    self.id_ = id
    self.characterType_ = characterType
end

function CRoleInformationCharacterItemData.GetId(self)
	return self.id_
end

function CRoleInformationCharacterItemData.SetId(self, id)
	self.id_ = id
end

function CRoleInformationCharacterItemData.GetCharacterType(self)
	return self.characterType_
end

function CRoleInformationCharacterItemData.SetCharacterType(self, characterType)
	self.characterType_ = characterType
end


return CRoleInformationCharacterItemData