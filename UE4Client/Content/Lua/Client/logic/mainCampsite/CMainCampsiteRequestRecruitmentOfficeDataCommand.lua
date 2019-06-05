local CMainCampsiteRequestRecruitmentOfficeDataCommand = class("CMainCampsiteRequestRecruitmentOfficeDataCommand", CCommand)

function CMainCampsiteRequestRecruitmentOfficeDataCommand.ctor(self)
	CCommand.ctor(self)
end


function CMainCampsiteRequestRecruitmentOfficeDataCommand.Execute(self, notification)
	print("CMainCampsiteRequestRecruitmentOfficeDataCommand.Execute...")
	
	self:RealPackData()
end

function CMainCampsiteRequestRecruitmentOfficeDataCommand.RealPackData(self)
	--请求服务器数据

	--打开RecruitmentOffice
	g_Facade:SendNotification(NotifierEnum.OPEN_RECRUITMENT_OFFICE)
 
end

return CMainCampsiteRequestRecruitmentOfficeDataCommand