local CMainCampsiteRequestRoleListDataCommand = class("CMainCampsiteRequestRoleListDataCommand", CCommand)

function CMainCampsiteRequestRoleListDataCommand.ctor(self)
	CCommand.ctor(self)
end


function CMainCampsiteRequestRoleListDataCommand.Execute(self, notification)
	print("CMainCampsiteRequestRoleListDataCommand.Execute...")
	
	self:RealPackData()
end

function CMainCampsiteRequestRoleListDataCommand.RealPackData(self)
	--请求服务器数据
	
	--打开RoleList
	CRoleListMediator:Show()
 
end

return CMainCampsiteRequestRoleListDataCommand