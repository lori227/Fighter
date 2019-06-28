local CRecruitmentOfficeProxy = class("CRecruitmentOfficeProxy", CProxy)

function CRecruitmentOfficeProxy.ctor(self, name)
    CProxy.ctor(self, name)
    --职业偏向列表
    self.deviationDataMap_ = {}
    --招募商店列表
    self.recruitShopDataMap_ = {}
    --招募次数
    self.recruitCount_ = nil
    --招募时间
    self.recruitTime_ = nil
    --需要展出的新英雄
    self.newHeroShowData_ = nil
end 

function CRecruitmentOfficeProxy.Init(self)
	local recruitCount = g_NetPlayerDataCtrl:GetMyPlayerDataValue_1("recruitcount")
	if recruitCount then
		self:SetRecruitCount(recruitCount)
	end

	local recruitTime = g_NetPlayerDataCtrl:GetMyPlayerDataValue_1("recruittime")
	if recruitTime then
    	self:SetRecruitTime(recruitTime)
    end
    
    local recruitData = g_NetPlayerDataCtrl:GetMyPlayerDataValue_1("recruit")
    if	recruitData then
	    for k, v in pairs(recruitData) do
	    	local cost = json.decode(g_NetPlayerDataCtrl:GetMyPlayerDataValue_3("recruit", v.uuid, "cost"))[1]
	    	local data = {	
	    		uuid = g_NetPlayerDataCtrl:GetMyPlayerDataValue_3("recruit", v.uuid, "uuid"),
	    		cost = cost,
	    		race = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", v.uuid, "hero", "race"),
	    		profession = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", v.uuid, "hero", "profession"),
	    		name = g_NetPlayerDataCtrl:GetMyPlayerDataValue_4("recruit", v.uuid, "hero", "name"),
	    	}
	    	self:AddRecruitShopData(data)
	    	local keyName = "player_recruit_" .. tostring(v.uuid)
	        CRecruitmentOfficeMediator:Get():RegisterObserver(keyName, "HandleNotification")
	    end
	end
    --table.print(self.recruitShopDataMap_)
end

function CRecruitmentOfficeProxy.GetNewHeroShowData(self)
	return self.newHeroShowData_
end

function CRecruitmentOfficeProxy.AddNewHeroShowData(self, heroData)
	self.newHeroShowData_ = nil
	self.newHeroShowData_ = heroData
end

function CRecruitmentOfficeProxy.RemoveNewHeroShowData(self)
	self.newHeroShowData_ = nil
end

function CRecruitmentOfficeProxy.AddDeviationData(self, id)
	local  index = self:HasDeviationData(id)
	if not index then
		table.insert(self.deviationDataMap_, id)
		return id
	end
	return false
end

function CRecruitmentOfficeProxy.RemoveDeviationData(self, id)
	local  index = self:HasDeviationData(id)
	if index then
		table.remove(self.deviationDataMap_, index)
		return id
	end
	return false
end


function CRecruitmentOfficeProxy.HasDeviationData(self, id)
	for k, v in pairs(self.deviationDataMap_) do
		if tostring(v) == tostring(id) then
			return k
		end
	end
	return false
end

function CRecruitmentOfficeProxy.GetDeviationDataMap(self)
	return self.deviationDataMap_
end

function CRecruitmentOfficeProxy.GetRecruitShopDataMap(self)
	return self.recruitShopDataMap_
end

function CRecruitmentOfficeProxy.AddRecruitShopData(self, recruitShopData)
	if not self:HasRecruitShopData(recruitShopData.uuid) then
    	table.insert(self.recruitShopDataMap_, recruitShopData)
    	return true
    end
    return false
    --table.print(self.recruitShopData_)
end

function CRecruitmentOfficeProxy.RemoveRecruitShopData(self, uuid)
    local k = self:HasRecruitShopData(uuid)
    if k then
    	table.remove(self.recruitShopDataMap_, k)
    	return k
	end
	return false
end

function CRecruitmentOfficeProxy.HasRecruitShopData(self, uuid)
	for k, v in pairs(self.recruitShopDataMap_) do
		if tostring(v.uuid)== tostring(uuid) then
			return k
		end
	end
	return false
end

function CRecruitmentOfficeProxy.GetRecruitShopHero(self, uuid)
	local k = self:HasRecruitShopData(uuid)
	if k then
		return self.recruitShopDataMap_[k]
	end
	return false
end

function CRecruitmentOfficeProxy.SetRecruitCount(self, count)
	if count >= 0 then
		self.recruitCount_ = count
	end
end

function CRecruitmentOfficeProxy.GetRecruitCount(self)
	return self.recruitCount_
end

function CRecruitmentOfficeProxy.SetRecruitTime(self, time)
	if time >= 0 then
		self.recruitTime_ = time
	end
end

function CRecruitmentOfficeProxy.GetRecruitTime(self)
	return self.recruitTime_
end

return CRecruitmentOfficeProxy