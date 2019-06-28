local CUIPageContainerBase = class("CUIPageContainerBase")


function CUIPageContainerBase.ctor(self)
	self.curShowPage_ = nil
 	self.pages_ = {}
 	self.uniqueID_ = 0
end


function CUIPageContainerBase.AddPage(self, cls)
	local index = table.count(self.pages_) + 1
	local id = self:GenerateUniqueID()
	local page = cls.New(id, index)
	page:OnInitPage()
	if page.userWidget_ == nil then
		error("CUIPageContainerBase.AddPage..., item.userWidget_ == nil")
	end

	self.pages_[index] = page

	return page
end


function CUIPageContainerBase.ShowPage(self, showPage, ...)
	if showPage == nil then
		return
	end

	if self.curShowPage_ ~= nil then
		if  self.curShowPage_:GetId() == showPage:GetId() then
			return
		end

		self.curShowPage_:OnClosePage()
	end

	for i, page in ipairs(self.pages_) do
		if page:GetId() == showPage:GetId() then
			page:OnShowPage(...)
			self.curShowPage_ = page
		end
	end
end


function CUIPageContainerBase.CloseAllPage(self)
	for i, page in ipairs(self.pages_) do
		page:OnClosePage()
	end
end


function CUIPageContainerBase.GetCurShowPage(self)
	return self.curShowPage_
end


function CUIPageContainerBase.ShowPageByIndex(self, index, ...)
	local page = self.pages_[index]
	self:ShowPage(page, ...)
end


function CUIPageContainerBase.GetPageByIndex(self, index)
	return self.pages_[index]
end


function CUIPageContainerBase.ShowPageById(self, id, ...)
	local page = self:GetPageById(id)
	if page ~= nil then
		self:ShowPage(page, ...)
	end
end


function CUIPageContainerBase.GetPageById(self, id)
	for i, page in ipairs(self.pages_) do
		if page:GetId() == id then
			return page
		end
	end

	return nil
end

function CUIPageContainerBase.GenerateUniqueID(self)
	self.uniqueID_ = self.uniqueID_ + 1
	return self.uniqueID_
end

return CUIPageContainerBase