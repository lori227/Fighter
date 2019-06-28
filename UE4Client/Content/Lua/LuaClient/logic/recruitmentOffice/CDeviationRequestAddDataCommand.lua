local CdeviationTypeRequestAddDataCommand = class("CdeviationTypeRequestAddDataCommand", CCommand)

function CdeviationTypeRequestAddDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CdeviationTypeRequestAddDataCommand.Execute(self, notification)
	print("CdeviationTypeRequestAddDataCommand.Execute...")

	self:SetData(notification)
end

function CdeviationTypeRequestAddDataCommand.SetData(self, notification)
	local deviationType = notification:GetBody()
	local deviationProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	local maxCount = 0

	for k, v in pairs(g_RecruitmentOfficeConfig.divisorMap_) do
		if tonumber(v.Type) == tonumber(deviationType.Type) then	
			for k1, v1 in pairs(v.ChildTypes) do
				if deviationProxy:HasDeviationData(v1.Id) then
					maxCount = maxCount + 1
				end
			end
			break
		end
	end

	if maxCount < deviationType.MaxCount then
		local idTable = {}
		if not deviationProxy:HasDeviationData(deviationType.Id) then
			table.insert(idTable, deviationType.Id)

			local MsgdeviationTypeReqData = 
			{
			   id = idTable,
			}
			--table.print(MsgdeviationTypeReqData)
			local str = pbc.encode("KFMsg.MsgChooseDivisorReq", MsgdeviationTypeReqData)
			g_Network:Send(ProtobufEnum.MSG_CHOOSE_DIVISOR_REQ, str, #str)
		end
	end
	--table.print(idTable)
end

return CdeviationTypeRequestAddDataCommand