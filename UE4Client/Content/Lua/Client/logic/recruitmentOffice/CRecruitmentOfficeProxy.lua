local CRecruitmentOfficeProxy = class("CRecruitmentOfficeProxy", CProxy)

function CRecruitmentOfficeProxy.ctor(self, name)
    CProxy.ctor(self, name)
    --职业倾向表
    self.deviationList_ = {}
    --商店列表
    self.shopList_ = {}
end

function CRecruitmentOfficeProxy.AddDeviation(self, deviationitem)
    table.insert(self.deviationList_, deviationitem)
end

function CRecruitmentOfficeProxy.RemoveDeviation(self)
    --table.remove(self.deviationList_, id)
end

function CRecruitmentOfficeProxy.AddShopItem(self, shopitem)
    table.insert(self.shopList_, shopitem)
end

function CRecruitmentOfficeProxy.RemoveShopItem(self)
    --table.remove(self.shopList_, id)
end

return CRecruitmentOfficeProxy