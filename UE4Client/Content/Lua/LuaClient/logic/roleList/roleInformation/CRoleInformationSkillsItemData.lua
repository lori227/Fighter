local CRoleInformationSkillsItemData = class("CRoleInformationSkillsItemData")

function CRoleInformationSkillsItemData.ctor(self, id)
    self.id_ = id
    self.imagePath_ = nil
end

function CRoleInformationSkillsItemData.GetId(self)
	return self.id_
end

function CRoleInformationSkillsItemData.SetId(self, id)
	self.id_ = id
end


function CRoleInformationSkillsItemData.GetImagePath(self)
	return self.imagePath_
end

function CRoleInformationSkillsItemData.SetImagePath(self, iamgePath)
	self.imagePath_ = iamgePath
end


return CRoleInformationSkillsItemData