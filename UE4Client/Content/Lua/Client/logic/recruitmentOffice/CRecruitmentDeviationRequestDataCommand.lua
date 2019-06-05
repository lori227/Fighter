local CRecruitmentDeviationRequestDataCommand = class("CRecruitmentDeviationRequestDataCommand", CCommand)

function CRecruitmentDeviationRequestDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentDeviationRequestDataCommand.Execute(self, notification)
	print("CRecruitmentDeviationRequestDataCommand.Execute...")

	self:ToGetData()
end

function CRecruitmentDeviationRequestDataCommand.ToGetData(self)
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

return CRecruitmentDeviationRequestDataCommand