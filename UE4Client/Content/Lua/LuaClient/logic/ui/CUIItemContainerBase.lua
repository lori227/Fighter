local CUIItemContainerBase = class("CUIItemContainerBase")


function CUIItemContainerBase.ctor(self)
	self.uiItemParent_ = nil
 	self.items_ = {}
 	self.uniqueID_ = 0
end


function CUIItemContainerBase.AddItem(self, cls, data)
	local id = self:GenerateUniqueID()
	local item = cls.New(id)
	item:Init(data)
	item:OnCreateUI()
	if item.userWidget_ == nil then
		error("CUIItemContainerBase.AddItem..., item.userWidget_ == nil")
	end

	self.uiItemParent_:AddChild(item.userWidget_)
	self.items_[id] = item

	return item
end

function CUIItemContainerBase.RemoveItem(self, id)
	local item = self.items_[id]
	if item ~= nil then
		if item.userWidget_ ~= nil then
			item.userWidget_:RemoveFromParent()
		end
		item:OnDestroyedUI()
		item:Destroy()
	end

	self.items_[id] = nil
end

function CUIItemContainerBase.RefreshItem(self)
	if self.items_ then
		for k, v in pairs(self.items_) do
			v:OnRefreshItem()
		end
	end
end


function CUIItemContainerBase.GetItem(self, id)
	return self.items_[id]
end

function CUIItemContainerBase.GenerateUniqueID(self)
	self.uniqueID_ = self.uniqueID_ + 1
	return self.uniqueID_
end

function CUIItemContainerBase.OnDestroyedUI(self)
	for k, v in pairs(self.items_) do 
 		v:OnDestroyedUI()
 	end
end	

function CUIItemContainerBase.OnDestroyed(self)
	self.uiItemParent_ = nil
 	self.uniqueID_ = nil
 	for k, v in pairs(self.items_) do 
 		v:OnDestroyedUI()
 		v:Destroy()
 	end
end

return CUIItemContainerBase