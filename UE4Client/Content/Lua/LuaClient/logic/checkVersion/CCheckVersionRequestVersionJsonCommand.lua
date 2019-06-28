local CCheckVersionRequestVersionJsonCommand = class("CCheckVersionRequestVersionJsonCommand", CCommand)

function CCheckVersionRequestVersionJsonCommand.ctor(self)
	CCommand.ctor(self)
end

local l_jsonData = ""
local l_jsonLength = 0

local function collect(chunk)
	l_jsonData = ""
	if chunk ~= nil then
		l_jsonData = l_jsonData .. chunk
		l_jsonLength = #l_jsonData
	end
end

function CCheckVersionRequestVersionJsonCommand.Execute(self, notification)
	print("CCheckVersionRequestVersionJsonCommand.Execute...")
	local body, code, headers, status = http.request {
        method = "GET",
        url = g_Config:GetVersionJsonUrl(),
        headers = 
                {
                    ["Content-Type"] = "application/x-www-form-urlencoded"
                },
        sink = collect,
    }

    --print('url:' .. g_Config:GetVersionJsonUrl())
	--print('body:' .. tostring(body))
    --print('code:' .. tostring(code))
    --table.print(headers)
    --local jsonLength = headers["content-length"]
    --print('status:' .. tostring(status))
    --print('jsonLength:' .. jsonLength)
    --print('l_jsonLength:' .. l_jsonLength)
   	--print('l_jsonData type:' .. type(l_jsonData))
    --print(l_jsonData)
    --table.print(l_jsonData)

    self:HandleRequestVersionJsonResult(l_jsonData)
end

function CCheckVersionRequestVersionJsonCommand.HandleRequestVersionJsonResult(self, jsonData)
	if jsonData == nil or jsonData == "" then
		--出错提示
    	do 
    		return
    	end
    end
    local versionJsonData = json.decode(l_jsonData)
    local tempServerTargetVersion = versionJsonData["Info"]["TargetVersion"]
    if tempServerTargetVersion == nil then
    	--出错提示
    	do 
    		return
    	end
    end

    --比较本地基础版本
    local tempLocalClientBaseVersion = g_Config:GetClientBaseVersion()
	if tempLocalClientBaseVersion == tempServerTargetVersion then
		print(string.format("本地基础版本为:%s, 网络目标版本为:%s, 无需更新...", tempLocalClientBaseVersion, tempServerTargetVersion))
		--切换到服务器认证状态
		local toServerAuthEvent = CToServerAuthEvent.New(GameFSMStateIdEnum.CHECK_VERSION, GameFSMStateIdEnum.SERVER_AUTH, FSMStackOpEnum.SET)
		g_GameFSM:DoEvent(toServerAuthEvent)
		do 
			return
		end
	end

	--比较本地基础版本
	local tempLocalTargetVersion = self:GetLocalTargetVersionFromLocalVersionJson()
	if tempLocalTargetVersion ~= nil then
		if tempLocalTargetVersion == tempServerTargetVersion then
			print(string.format("本地目标版本为:%s, 网络目标版本为:%s, 无需更新...", tempLocalTargetVersion, tempServerTargetVersion))
			--切换到服务器认证状态
			local toServerAuthEvent = CToServerAuthEvent.New(GameFSMStateIdEnum.CHECK_VERSION, GameFSMStateIdEnum.SERVER_AUTH, FSMStackOpEnum.SET)
			g_GameFSM:DoEvent(toServerAuthEvent)
			do 
				return
			end
		end
	end
  
	--生成最终补丁路径
	local tempServerPatchPakUrl = g_Config:GetServerPatchPakUrl()
	local TempPatchPakFinalUrl = self:GeneratePatchPakFinalUrl(tempLocalClientBaseVersion, tempServerTargetVersion, tempServerPatchPakUrl)
	print(string.format("本地基础版本为:%s, 本地目标版本为:%s, 网络目标版本为:%s,  需要更新..., , tempServerPatchPakUrl:%s, patchPakFinalUrl:%s.", tempLocalClientBaseVersion, tempLocalTargetVersion, tempServerTargetVersion, tempServerPatchPakUrl, TempPatchPakFinalUrl))

	--切换到补丁更新状态
	local toBatchUpdateEvent = CToBatchUpdateEvent.New(GameFSMStateIdEnum.CHECK_VERSION, GameFSMStateIdEnum.BATCH_UPDATE, FSMStackOpEnum.SET)
	g_GameFSM:DoEvent(toBatchUpdateEvent)
end

function CCheckVersionRequestVersionJsonCommand.GetLocalTargetVersionFromLocalVersionJson(self)
	local tempPathFile = FToLuaPaths.ProjectContentDir() .. "Version.json"
	local f = io.open(tempPathFile, "r")
	if f then
		local c = f:read("*all")
		f:close()
		if c then
			local jsonData = json.decode(c)
			return jsonData["TargetVersion"]
		end
	end
end

function CCheckVersionRequestVersionJsonCommand.GeneratePatchPakFinalUrl(self, localClientBaseVersion, serverTargetVersion, serverPatchPakUrl)
	local tempClientBaseVersion = string.gsub(localClientBaseVersion, ".", "_")
	local tempServerTargetVersion = string.gsub(serverTargetVersion, ".", "_")
	local tempServerPatchPakUrl = serverPatchPakUrl .. "/" .. tempClientBaseVersion .. "_" .. tempServerTargetVersion .. "/Patch_0_P.pak"
	return tempServerPatchPakUrl
end

return CCheckVersionRequestVersionJsonCommand