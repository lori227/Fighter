local CServerAuthRequestAuthInfoCommand = class("CServerAuthRequestAuthInfoCommand", CCommand)

function CServerAuthRequestAuthInfoCommand.ctor(self)
	CCommand.ctor(self)
end


function CServerAuthRequestAuthInfoCommand.Execute(self, notification)
	print("CServerAuthRequestAuthInfoCommand.Execute...")
	
	local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
    local account = serverAuthProxy:GetAccount()

	if account == nil or account == "" then
        print("account为空!")
        return
    end

    print("account:"..account)    
    local requestBody = {["channel"] = 1, ["account"] = account}
    local r = json.encode(requestBody)
    local responseBody = {}

    local body, code, headers, status = http.request {
        method = "POST",
        url = g_Config:GetServerPatchPakUrl(),
        headers = 
                {
                    ["Content-Type"] = "application/json; charset=utf-8";
                    ["Content-Length"] = #r;
                },
        sink = ltn12.sink.table(responseBody),
        source = ltn12.source.string(r),
    }
    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    print('body:' .. tostring(body))
    print('code:' .. tostring(code))
    table.print(headers)
    print('status:' .. tostring(status))
    table.print(responseBody)
    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    self:HandleRequestServerAuthResult(responseBody[1])
end


function CServerAuthRequestAuthInfoCommand.HandleRequestServerAuthResult(self, responseString)
	if responseString == nil then
		--出错提示
    	do
    		return
    	end
    end

    local serverAuthJsonData = json.decode(responseString)
    local tempRetcode = serverAuthJsonData["retcode"]
    local tempToken = serverAuthJsonData["token"]
    local tempAccountid = serverAuthJsonData["accountid"]
    local tempServerTable = serverAuthJsonData["zone"]
    

    --table.print(serverAuthJsonData)
    if tempRetcode ~= 1 then
		print(string.format("服务器授权Http请求失败, retcode:%d.", tempRetcode))
		--出错提示
		do
			return
		end
	end

	local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
	serverAuthProxy:SetToken(tempToken)
    serverAuthProxy:SetAccountId(tempAccountid)
    serverAuthProxy:SetServerTable(tempServerTable)

	print(string.format("服务器授权Http请求成功. tempToken:%s, tempAccountid:%d", tempToken, tempAccountid))
	--table.print(tempServerTable)

	--切换到登陆状态
	local toLoginEvent = CToLoginEvent.New(GameFSMStateIdEnum.SERVER_AUTH, GameFSMStateIdEnum.LOGIN, FSMStackOpEnum.SET)
	g_GameFSM:DoEvent(toLoginEvent)
end

return CServerAuthRequestAuthInfoCommand