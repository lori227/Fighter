local CPackGridItem = class("CPackGridItem")

function CPackGridItem.ctor(self, gridObj)
    self.goodNum_ = 0
    self.goodObj_ = nil
    self.gridObj_ = gridObj
end

function CPackGridItem.GetGoodNum(self)
	return self.goodNum_
end

function CPackGridItem.SetGoodNum(self, goodNum)
	self.goodNum_ = goodNum
end

function CPackGridItem.GetGoodObj(self)
	return self.goodObj_
end

function CPackGridItem.SetGoodObj(self, goodObj)
	self.goodObj_ = goodObj
end

function CPackGridItem.GetGridObj(self)
	return self.gridObj_
end

function CPackGridItem.SetGridObj(self, gridObj)
	self.gridObj_ = gridObj
end

return CPackGridItem