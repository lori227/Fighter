local CPackGridItem = class("CPackGridItem")

function CPackGridItem.ctor(self, gridobj)
    self.goodNum_ = 0
    self.goodObj_ = nil
    self.gridObj_ = gridobj
end

function CPackGridItem.GetGoodNum(self)
	return self.goodNum_
end

function CPackGridItem.SetGoodNum(self, goodnum)
	self.goodNum_ = goodnum
end

function CPackGridItem.GetGoodObj(self)
	return self.goodObj_
end

function CPackGridItem.SetGoodObj(self, goodobj)
	self.goodObj_ = goodobj
end

function CPackGridItem.GetGridObj(self)
	return self.gridObj_
end

function CPackGridItem.SetGridObj(self, gridobj)
	self.gridObj_ = gridobj
end

return CPackGridItem