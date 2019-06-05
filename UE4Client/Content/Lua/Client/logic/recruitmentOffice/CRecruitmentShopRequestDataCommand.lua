local CRecruitmentShopRequestDataCommand = class("CRecruitmentShopRequestDataCommand", CCommand)

function CRecruitmentShopRequestDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentShopRequestDataCommand.Execute(self, notification)
	print("CRecruitmentShopRequestDataCommand.Execute...")

	self:ToGetData()
end

function CRecruitmentShopRequestDataCommand.ToGetData(self)
	-- local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
	-- local tempServerTable = serverAuthProxy:GetServerTable()
    -- local ip = tempServerTable["ip"]
    -- local port = tempServerTable["port"]
	-- FToLuaGameInstance.TCPClientConnect(ip, port)
	-- g_Network:Connect(ip, port)

	-- --local dir = FToLuaPaths.ProjectContentDir()
	-- --local filePath = dir .. "Lua/LuaClient/logic/proto/FrameClientMessage.proto"
	-- local filePath = "FrameClientMessage.proto"
	-- protoc:loadfile(filePath)

	-- local localToken = serverAuthProxy:GetToken()
	-- local localAccountId = serverAuthProxy:GetAccountId()
	-- local MsgLoginReqData = 
	-- {
	--    token = localToken,
	--    accountid = localAccountId,
	--    version = "0.0.0.0"
	-- }
	-- --table.print(MsgLoginReqData)
	
	-- local str = pb.encode("KFMsg.MsgLoginReq", MsgLoginReqData)
	-- g_Network:Send(ProtobufEnum.MSG_LOGIN_REQ, str, #str)
end

return CRecruitmentShopRequestDataCommand