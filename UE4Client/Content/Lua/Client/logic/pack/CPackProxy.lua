local CPackProxy = class("CPackProxy", CProxy)

function CPackProxy.ctor(self, name)
    CProxy.ctor(self, name)
    --背包固定格子数
    self.gridsNum_ = 60
    --背包格子缓存
    self.gridsList_ = {}
    --背包当前选中状态
    self.curGridIndex_ = -1
    --背包物品列表
    self.goodsList_ = { 
                        [1] = CPackGoodItem.New(1, 9, "物品一"),
                        [2] = CPackGoodItem.New(2, 99, "物品二"),
                        [3] = CPackGoodItem.New(3, 999, "物品三"),
                        [4] = CPackGoodItem.New(4, 100, "物品四"),
                        [5] = CPackGoodItem.New(5, 9, "物品一"),
                        [6] = CPackGoodItem.New(6, 99, "物品二"),
                        [7] = CPackGoodItem.New(7, 999, "物品三"),
                        [8] = CPackGoodItem.New(15, 100, "物品四"),
                        [19] = CPackGoodItem.New(16, 9, "物品一"),
                        [20] = CPackGoodItem.New(17, 99, "物品二"),
                        [21] = CPackGoodItem.New(18, 999, "物品三"),
                        [22] = CPackGoodItem.New(19, 100, "物品四"),
                    }
end

--获取背包固定格子数
function CPackProxy.GetGridsNum(self)
	return self.gridsNum_
end

--设置背包固定格子数
function CPackProxy.SetGridsNum(self, gridsnum)
	self.gridsNum_ = gridsnum
end

--添加格子缓存
function CPackProxy.AddGrid(self,index, grid)
	table.insert(self.gridsList_, index, grid)
end

--通过Index获取缓存的格子对象
function CPackProxy.GetGridForIndex(self, index)
	return self.gridsList_[index]
end

--获取当前选中格子的Index
function CPackProxy.GetCurGrid(self)
	return self.curGridIndex_
end

--设置当前选中格子的Index
function CPackProxy.SetCurGrid(self, curgridindex)
	self.curGridIndex_ = curgridindex
end

--添加Good
function  CPackProxy.AddGood(self, id, good)
    table.insert(self.goodsList_, id, good)
end

--移除Good
function CPackProxy.RemoveGood(self, id)
    table.remove(self.goodsList_, id)
end

--获取Good
function CPackProxy.GetGood(self, id)
    return self.goodsList_[id]
end

return CPackProxy