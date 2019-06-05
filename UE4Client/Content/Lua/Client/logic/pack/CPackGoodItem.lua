local CPackGoodItem = class("CPackGoodItem")

function CPackGoodItem.ctor(self, goodid, goodnum, goodname)
    self.goodId_ = goodid
    self.goodNum_ = goodnum
    self.gridName_ = goodname
end

function CPackGoodItem.GetGoodId(self)
	return self.goodId_
end

function CPackGoodItem.SetGoodId(self, goodid)
	self.goodId_ = goodid
end

function CPackGoodItem.GetGoodNum(self)
	return self.goodNum_
end

function CPackGoodItem.SetGoodNum(self, goodnum)
	self.goodNum_ = goodnum
end

function CPackGoodItem.GetGoodName(self)
	return self.gridName_
end

function CPackGoodItem.SetGoodName(self, goodname)
	self.gridName_ = goodname
end

return CPackGoodItem