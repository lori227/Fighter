local CShopItem = class("CShopItem")

function CShopItem.ctor(self, id, cost1, cost2, cost3)
	--ShopID
    self.id_ = id

    self.cost1_ = cost1
    self.cost2_ = cost2
    self.cost3_ = cost3

    self.imageSrc_ = nil
end

function CShopItem.GetId(self)
	return self.id_
end

function CShopItem.SetDeviationId(self, id)
	self.id_ = id
end

function CShopItem.GetCost1(self)
	return self.cost1_
end

function CShopItem.SetCost1(self, cost1)
	self.cost1_ = cost1
end

function CShopItem.GetCost2(self)
	return self.cost2_
end

function CShopItem.SetCost2(self, cost2)
	self.cost2_ = cost2
end

function CShopItem.GetCost3(self)
	return self.cost3_
end

function CShopItem.SetCost3(self, cost3)
	self.cost3_ = cost3
end

function CShopItem.GetImageSrc(self)
	return self.imageSrc_
end

function CShopItem.SetImageSrc(self, iamgesrc)
	self.imageSrc_ = iamgesrc
end

return CShopItem