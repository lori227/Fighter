local CRoleInformationProxy = class("CRoleInformationProxy", CProxy)

function CRoleInformationProxy.ctor(self, name)
    CProxy.ctor(self, name)
    --角色详情界面
    self.attributeDataList_ = {}
    self.roleBuffDataList_ = {}
    self.characterDataList_ = {}
    self.skillsDataList_ = {}
    self.roleName_ = "名字這麽長"
    self.roleImage_ = nil
    self.experienceValue_ = nil
    self.roleBuff_ = {}
    self.live_ = 100
    
end

function CRoleInformationProxy.AddAttributeItemData(self, attributeItemData)
    table.insert(self.attributeList_, attributeItemData)
end

function CRoleInformationProxy.RemoveAttributeItemData(self)
    --table.remove(self.roleList_, id)
end

function CRoleInformationProxy.AddBuffItemData(self, buffItemData)
    table.insert(self.roleBuffDataList_, buffItemData)
end

function CRoleInformationProxy.RemoveBuffItemData(self)
    --table.remove(self.roleList_, id)
end

function CRoleInformationProxy.AddcharacterItemData(self, characterItemData)
    table.insert(self.characterList_, characterItemData)
end

function CRoleInformationProxy.RemovecharacterItemData(self)
    --table.remove(self.roleList_, id)
end

function CRoleInformationProxy.AddskillsItemData(self, skillsItemData)
    table.insert(self.skillsList_, skillsItemData)
end

function CRoleInformationProxy.RemoveskillsItemData(self)
    --table.remove(self.roleList_, id)
end


function CRoleInformationProxy.GetItemTotal(self)
	return self.itemTotal_
end

function CRoleInformationProxy.SetItemTotal(self, gridSnum)
	self.itemTotal_ = itemTotal
end

function CRoleInformationProxy.GetRoleNum(self)
    return self.roleNum_
end

function CRoleInformationProxy.SetRoleNum(self, gridSnum)
    self.roleNum_ = roleNum
end


return CRoleInformationProxy