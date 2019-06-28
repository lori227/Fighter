local CDeviationRequestRemoveDataCommand = class("CDeviationRequestRemoveDataCommand", CCommand)

function CDeviationRequestRemoveDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CDeviationRequestRemoveDataCommand.Execute(self, notification)
	print("CDeviationRequestRemoveDataCommand.Execute...")

	self:SetData(notification)
end

function CDeviationRequestRemoveDataCommand.SetData(self, notification)
	local deviationTypes = notification:GetBody()
	local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	local allDeviationId = {}
	if deviationTypes.Id == nil then
		for k, v in pairs(deviationTypes) do
			if recruitmentOfficeProxy:HasDeviationData(v.Id) then
				table.insert(allDeviationId, v.Id)
			end
		end
	else
		if recruitmentOfficeProxy:HasDeviationData(deviationTypes.Id) then
			table.insert(allDeviationId, deviationTypes.Id)
		end
	end
	if table.count(allDeviationId) ~= 0 then
		local MsgDeviationReqData = 
		{
		   id = allDeviationId,
		}
		--table.print(MsgDeviationReqData)
		local str = pbc.encode("KFMsg.MsgRemoveDivisorReq", MsgDeviationReqData)
		g_Network:Send(ProtobufEnum.MSG_REMOVE_DIVISOR_REQ, str, #str)
	end
	--table.print(allDeviationId)
end

return CDeviationRequestRemoveDataCommand