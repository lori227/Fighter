local CMainCampsiteRequestPackDataCommand = class("CMainCampsiteRequestPackDataCommand", CCommand)

function CMainCampsiteRequestPackDataCommand.ctor(self)
	CCommand.ctor(self)
end


function CMainCampsiteRequestPackDataCommand.Execute(self, notification)
	print("CMainCampsiteRequestPackDataCommand.Execute...")
	
	self:RealPackData()
end

function CMainCampsiteRequestPackDataCommand.RealPackData(self)
	--请求服务器数据

	--打开Pack
	g_Facade:SendNotification(NotifierEnum.OPEN_PACK)
 
end

return CMainCampsiteRequestPackDataCommand