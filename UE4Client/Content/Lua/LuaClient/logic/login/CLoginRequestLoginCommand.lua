local CLoginRequestLoginCommand = class("CLoginRequestLoginCommand", CCommand)

function CLoginRequestLoginCommand.ctor(self)
	CCommand.ctor(self)
end

function CLoginRequestLoginCommand.Execute(self, notification)
	print("CLoginRequestLoginCommand.Execute...")

	self:RealLogin()
end

function CLoginRequestLoginCommand.RealLogin(self)
	local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
	local tempServerTable = serverAuthProxy:GetServerTable()
    local ip = tempServerTable["ip"]
    local port = tempServerTable["port"]

	if g_Network:IsNeedReset() then
		g_Network:Reset()
	end
	g_Network:Connect(ip, port)

	-- local dir = FToLuaPaths.ProjectContentDir()
	-- local filePath = dir .. "Lua/LuaClient/logic/proto/FrameClientMessage.proto"
	-- local filePath = "FrameClientMessage.proto"
	-- protoc:loadfile(filePath)

	local localToken = serverAuthProxy:GetToken()
	local localAccountId = serverAuthProxy:GetAccountId()
	local MsgLoginReqData = 
	{
	   token = localToken,
	   accountid = localAccountId,
	   version = "0.0.0.0"
	}
	--table.print(MsgLoginReqData)
	
	local str = pbc.encode("KFMsg.MsgLoginReq", MsgLoginReqData)
	g_Network:Send(ProtobufEnum.MSG_LOGIN_REQ, str, #str)
end

return CLoginRequestLoginCommand