local CRequestRefreshGetNewRoleCommand = class("CRequestRefreshGetNewRoleCommand", CCommand)

function CRequestRefreshGetNewRoleCommand.ctor(self)
	CCommand.ctor(self)
end

function CRequestRefreshGetNewRoleCommand.Execute(self, notification)
	print("CRequestRefreshGetNewRoleCommand.Execute...")

	self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

	self.uiPanel_ = self.recruitmentOfficeMediator_.uiPanel_

	--请求服务器数据
	
	-------------------------------------------------------------------------------------------------------------------------

	-------------------------------------------------------------------------------------------------------------------------
	

	if self.recruitmentOfficeMediator_.uiGetNewRole_ == nil then
		self:CreateUI()
	else
		self:OpenUI()
	end
end

function CRequestRefreshGetNewRoleCommand.CreateUI(self)
	--载入
	self.getNewRoleUI_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_GetNewRole.WB_GetNewRole')
    local passBtn = self.getNewRoleUI_:FindWidget('PassBtn')

    passBtn.OnClicked:Add(function ()
        self.recruitmentOfficeMediator_:SetTargetVisibility(self.getNewRoleUI_, 1)
    end)


    self.recruitmentOfficeMediator_.uiGetNewRole_ = self.getNewRoleUI_
    self.getNewRoleUI_:AddToViewport(1)    
       
end

function CRequestRefreshGetNewRoleCommand.OpenUI(self)
    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    self.recruitmentOfficeMediator_:SetTargetVisibility(self.recruitmentOfficeMediator_.uiGetNewRole_, 4)
end

return CRequestRefreshGetNewRoleCommand