local CRoleInformationRefreshUICommand = class("CRoleInformationRefreshUICommand", CCommand)

function CRoleInformationRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRoleInformationRefreshUICommand.Execute(self, notification)
	print("CRoleInformationRefreshUICommand.Execute...")

	-- self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	-- self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

	self:RefreshInformation()
end


function CRoleInformationRefreshUICommand.RefreshInformation(self)
	local roleInformationUI = slua.loadUI('/Game/Blueprints/UI/Widget/RoleInformation/WB_RoleInformation.WB_RoleInformation')
    roleInformationUI:AddToViewport(1) 
    --按钮关闭
    shutBtn_ = roleInformationUI:FindWidget('ShutBtn')
    shutBtn_.OnClicked:Add(function ()

    roleInformationUI:PlayAnimation(roleInformationUI.OpenRoleInformation, 0 , 1, 1 , 1)
    end)
end


return CRoleInformationRefreshUICommand
