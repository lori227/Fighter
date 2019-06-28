local CDeviationResponseUpdateDataCommand = class("CDeviationResponseUpdateDataCommand", CCommand)

function CDeviationResponseUpdateDataCommand.ctor(self)
    CCommand.ctor(self)
end

function CDeviationResponseUpdateDataCommand.Execute(self, notification)
    print("CDeviationResponseUpdateDataCommand.Execute...")

    self:UpdateData(notification)
end

function CDeviationResponseUpdateDataCommand.UpdateData(self, notification)
    local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)  
    local body = notification:GetBody()

    if body.Op == "Init" then
        recruitmentOfficeProxy:AddDeviationData(body.Value)

  	elseif body.Op == "Add" and recruitmentOfficeProxy:AddDeviationData(body.Value.id) then
    	CDeviationMediator:Get():RefreshItem()

  	elseif body.Op == "Remove" then
    	local id = string.sub(body.Key, 16, string.len(body.Key))
        if recruitmentOfficeProxy:RemoveDeviationData(id) then
        	CDeviationMediator:Get():RefreshItem()
        end
    end
    --table.print(recruitmentOfficeProxy.deviationData_)
end

return CDeviationResponseUpdateDataCommand