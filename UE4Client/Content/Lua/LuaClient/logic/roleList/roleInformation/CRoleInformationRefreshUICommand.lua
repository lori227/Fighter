local CRoleInformationRefreshUICommand = class("CRoleInformationRefreshUICommand", CCommand)

function CRoleInformationRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRoleInformationRefreshUICommand.Execute(self, notification)
	print("CRoleInformationRefreshUICommand.Execute...")

	self.roleInformationProxy_ = g_Facade:RetrieveProxy(ProxyEnum.ROLE_INFORMATION)
	self.roleInformationMediator_ = CRoleInformationMediator:Get()

	self:RefreshInformation()
end


function CRoleInformationRefreshUICommand.RefreshInformation(self)
	
end


return CRoleInformationRefreshUICommand
