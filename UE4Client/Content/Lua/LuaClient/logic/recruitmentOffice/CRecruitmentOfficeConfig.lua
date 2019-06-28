CRecruitmentOfficeConfig = class("CRecruitmentOfficeConfig")

function CRecruitmentOfficeConfig.ctor(self)

	self.divisorMap_ = {}

	self:Init()
end

function CRecruitmentOfficeConfig.Init(self)
	print("CRecruitmentOfficeConfig   -->AnalysisConfig")

	self:AnalysisConfig()
end

--解析配置表
function CRecruitmentOfficeConfig.AnalysisConfig(self)
	for k, v in pairs(g_recruitDivisorCfg) do
		local go = 0
		if table.count(self.divisorMap_) ~= 0 then
			for k1, v1 in pairs(self.divisorMap_) do
				if v1.Type == v.Type then
					local childTypes = {Value = v.Value, Name = v.Name, Id = k, Type = v.Type, MaxCount = v.MaxCount}
					table.insert(self.divisorMap_[k1]["ChildTypes"], childTypes)
					break
				end 
				go = go + 1
			end
		end
		if go == table.count(self.divisorMap_) then
			local parentType = {TypeName = v.TypeName, Type = v.Type, ChildTypes = {}}
			local childTypes = {Value = v.Value, Name = v.Name, Id = k, Type = v.Type, MaxCount = v.MaxCount}
			table.insert(parentType["ChildTypes"], childTypes)
			table.insert(self.divisorMap_, parentType)
		end
	end
end

function CRecruitmentOfficeConfig.GetRaceNameById(self, id)
	for k, v in pairs(g_heroRaceCfg) do
		if tonumber(v.Id) == tonumber(id) then
			return v.PhyleName
		end
	end
	return false
end

function CRecruitmentOfficeConfig.GetProfessionNameById(self, id)
	for k, v in pairs(g_heroProfessionCfg) do
		if tonumber(v.Id) == tonumber(id) then
			return v.ClassName
		end
	end
	return false
end

function CRecruitmentOfficeConfig.GetDeviationNameById(self, id)
	for k, v in pairs(g_recruitDivisorCfg) do
		if tostring(k) == tostring(id) then
			return v.Name
		end
	end
end



return CRecruitmentOfficeConfig