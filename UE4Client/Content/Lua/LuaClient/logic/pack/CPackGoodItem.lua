local CPackGoodItem = class("CPackGoodItem")

function CPackGoodItem.ctor(self, goodId, goodNum, goodName)
    self.goodId_ = goodId
    self.goodNum_ = goodNum
    self.gridName_ = goodName
end

function CPackGoodItem.GetGoodId(self)
	return self.goodId_
end

function CPackGoodItem.SetGoodId(self, goodId)
	self.goodId_ = goodId
end

function CPackGoodItem.GetGoodNum(self)
	return self.goodNum_
end

function CPackGoodItem.SetGoodNum(self, goodNum)
	self.goodNum_ = goodNum
end

function CPackGoodItem.GetGoodName(self)
	return self.gridName_
end

function CPackGoodItem.SetGoodName(self, goodName)
	self.gridName_ = goodName
end

return CPackGoodItem