local CRoleListRequestDataCommand = class("CRoleListRequestDataCommand", CCommand)

function CRoleListRequestDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CRoleListRequestDataCommand.Execute(self, notification)
	print("CRoleListRequestDataCommand.Execute...")

	self:GetData()
end

function CRoleListRequestDataCommand.GetData(self)

end

return CRoleListRequestDataCommand