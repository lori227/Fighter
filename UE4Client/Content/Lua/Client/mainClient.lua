require "memory/memory"
require "core/core"
require "framework/framework"
require "fsm/fsm"
require "network/network"
require "logic/logic"



mainClient = {}
mainClient.isInitDone_ = false
mainClient.isClient_ = true


function mainClient.Update(deltatime)
	if mainClient.isInitDone_ then
		g_Network:ProcessReceiveMessage()
	end

	--collectgarbage("collect")
end

function mainClient.StartCheckVersion()
	print("mainClient.StartCheckVersion...")
	--启动游戏状态机
	g_GameFSM:Startup(GameFSMStateIdEnum.CHECK_VERSION)
end


function mainClient.Init()
	print(_VERSION)

	--网络初始化
	g_Network:Init()

	--初始化游戏状态机
	mainClient.InitGameState()

	--local dir = FToLuaPaths.ProjectContentDir()
	--local filePath = dir .. "Lua/LuaClient/logic/proto/FrameClientMessage.proto"
	local filePath = "FrameClientMessage.proto"
	protoc:loadfile(filePath)

	--注册所有的数据代理
	mainClient.RegisterProxyAll()

	--注册所有中介
	mainClient.RegisterMediatorAll()

	--初始化完成
	mainClient.isInitDone_ = true
	do 
		return
	end

	print(UICustomIdEnum.Login)
	print(type(CLoginMediator))
	g_Facade:RegisterUI(MediatorEnum.Login, CLoginMediator)
	--g_Facade:RegisterUI(define.UICustomID.Tips, CTipsMediator)
	--g_Facade:SendMessage(Notif_Enum.OPEN_LOGIN)
	--g_Facade:RemoveUI(UICustomID.Login)
	--g_MediatorManager:RemoveMediator(UICustomID.Login)
	--g_Facade:SendMessage(Notif_Enum.OPEN_TEST)
	--g_Facade:DoCmd("NoCmd")
end

function mainClient.InitGameState()

	--游戏状态
	g_GameFSM:AddState(CCheckVersionState.New(GameFSMStateIdEnum.CHECK_VERSION))
	g_GameFSM:AddState(CBatchUpdateState.New(GameFSMStateIdEnum.BATCH_UPDATE))
	g_GameFSM:AddState(CServerAuthState.New(GameFSMStateIdEnum.SERVER_AUTH))
	g_GameFSM:AddState(CLoginState.New(GameFSMStateIdEnum.LOGIN))
	g_GameFSM:AddState(CMainCampsiteState.New(GameFSMStateIdEnum.MAIN_CAMPSITE))
	g_GameFSM:AddState(CPVPMatchState.New(GameFSMStateIdEnum.PVP_MATCH))

	--游戏状态转换
	g_GameFSM:AddTransition(GameFSMStateIdEnum.CHECK_VERSION, GameFSMStateIdEnum.BATCH_UPDATE)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.CHECK_VERSION, GameFSMStateIdEnum.SERVER_AUTH)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.BATCH_UPDATE, GameFSMStateIdEnum.SERVER_AUTH)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.SERVER_AUTH, GameFSMStateIdEnum.LOGIN)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.MAIN_CAMPSITE, GameFSMStateIdEnum.PVP_MATCH)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.PVP_MATCH, GameFSMStateIdEnum.MAIN_CAMPSITE)

	g_GameFSM:AddTransition(GameFSMStateIdEnum.SERVER_AUTH, GameFSMStateIdEnum.MAIN_CAMPSITE)
end

--注册所有的数据代理
function mainClient.RegisterProxyAll()
	-------------------------------------通用提示-------------------------------------------------
	g_Facade:RegisterProxy(CCommonPromptProxy.New(ProxyEnum.COMMON_PROMPT))
	-------------------------------------通用提示-------------------------------------------------

	-------------------------------------檢測版本-------------------------------------------------
	g_Facade:RegisterProxy(CCheckVersionProxy.New(ProxyEnum.CHECK_VERSION))
	-------------------------------------檢測版本-------------------------------------------------

	-------------------------------------版本更新-------------------------------------------------
	g_Facade:RegisterProxy(CBatchUpdateProxy.New(ProxyEnum.BATCH_UPDATE))
	-------------------------------------版本更新-------------------------------------------------

	-------------------------------------服務器驗證-------------------------------------------------
	g_Facade:RegisterProxy(CServerAuthProxy.New(ProxyEnum.SERVER_AUTH))
	-------------------------------------服務器驗證-------------------------------------------------

	----------------------------------------登陸--------------------------------------------------
	g_Facade:RegisterProxy(CLoginProxy.New(ProxyEnum.LOGIN))
	----------------------------------------登陸--------------------------------------------------

	-------------------------------------1vs1PVP匹配--------------------------------------------------
	g_Facade:RegisterProxy(CPVPMatchProxy.New(ProxyEnum.PVP_MATCH))
	-------------------------------------1vs1PVP匹配-------------------------------------------------

	-------------------------------------游戏大厅--------------------------------------------------
	g_Facade:RegisterProxy(CMainCampsiteProxy.New(ProxyEnum.MAIN_CAMPSITE))
	--背包--
	g_Facade:RegisterProxy(CPackProxy.New(ProxyEnum.PACK))
	--招募所--
	g_Facade:RegisterProxy(CRecruitmentOfficeProxy.New(ProxyEnum.RECRUITMENT_OFFICE))
	-------------------------------------游戏大厅-------------------------------------------------

	-------------------------------------游戏设置-------------------------------------------------
	g_Facade:RegisterProxy(CGameSettingProxy.New(ProxyEnum.GAME_SETTING, ProxyEnum.GAME_SETTING))
	-------------------------------------游戏设置-------------------------------------------------

	-------------------------------------通用确认-------------------------------------------------
	g_Facade:RegisterProxy(CCommConfirmProxy.New(ProxyEnum.COMM_CONFIRM, ProxyEnum.COMM_CONFIRM))
	-------------------------------------通用确认-------------------------------------------------
end

--注册所有中介
function mainClient.RegisterMediatorAll()
	-------------------------------------通用提示-------------------------------------------------
	g_Facade:RegisterMediator(CCommonPromptMediator.New(MediatorEnum.COMMON_PROMPT))
	-------------------------------------通用提示-------------------------------------------------

	-------------------------------------檢測版本-------------------------------------------------
	g_Facade:RegisterMediator(CCheckVersionMediator.New(MediatorEnum.CHECK_VERSION))
	-------------------------------------檢測版本-------------------------------------------------

	-------------------------------------版本更新-------------------------------------------------
	g_Facade:RegisterMediator(CBatchUpdateMediator.New(MediatorEnum.BATCH_UPDATE))
	-------------------------------------版本更新-------------------------------------------------

	-------------------------------------服務器驗證-------------------------------------------------
	g_Facade:RegisterMediator(CServerAuthMediator.New(MediatorEnum.SERVER_AUTH))
	-------------------------------------服務器驗證-------------------------------------------------

	----------------------------------------登陸--------------------------------------------------
	g_Facade:RegisterMediator(CLoginMediator.New(MediatorEnum.LOGIN))
	----------------------------------------登陸--------------------------------------------------

	-------------------------------------1vs1PVP匹配--------------------------------------------------
	g_Facade:RegisterMediator(CPVPMatchMediator.New(MediatorEnum.PVP_MATCH))
	-------------------------------------1vs1PVP匹配--------------------------------------------------

	-------------------------------------游戏大厅--------------------------------------------------
	g_Facade:RegisterMediator(CMainCampsiteMediator.New(MediatorEnum.MAIN_CAMPSITE))
	--背包--
	g_Facade:RegisterMediator(CPackMediator.New(MediatorEnum.PACK)) 
	--招募所--
	g_Facade:RegisterMediator(CRecruitmentOfficeMediator.New(MediatorEnum.RECRUITMENT_OFFICE)) 
	-------------------------------------游戏大厅--------------------------------------------------
	
	-------------------------------------游戏设置-------------------------------------------------
	g_Facade:RegisterMediator(CGameSettingMediator.New(MediatorEnum.GAME_SETTING, MediatorEnum.GAME_SETTING))
	-------------------------------------游戏设置-------------------------------------------------

	-------------------------------------通用确认-------------------------------------------------
	g_Facade:RegisterMediator(CCommConfirmMediator.New(MediatorEnum.COMM_CONFIRM, MediatorEnum.COMM_CONFIRM))
	-------------------------------------通用确认-------------------------------------------------
end

--[[
function mainClient.ProcessReceiveMessage(msgId, pbData, pdDataLength)
	string
	if msgId == ProtobufEnum.MSG_LOGIN_ACK then
		local t = pb.decode("KFMsg.MsgLoginAck", pbData)
        local playerId = t["playerid"]
        print("******************************playerId:" .. playerId)
		g_Facade:SendNotification(NotifierEnum.NET_MSG_LOGIN_ACK, {MsgId=msgId, Data=pbData, DataLength=pdDataLength})
	elseif msgId == ProtobufEnum.MSG_INFORM_MATCH_RESULT then
		local t = pb.decode("KFMsg.MsgInformMatchResult", pbData)
        local time = t["time"]
        print("******************************time:" .. time)
		g_Facade:SendNotification(NotifierEnum.NET_MSG_INFORM_MATCH_RESULT, {MsgId=msgId, Data=pbData, DataLength=pdDataLength})
	elseif msgId == ProtobufEnum.MSG_INFORM_BATTLE_REQ then
		local t = pb.decode("KFMsg.MsgInformBattleReq", pbData)
        local roomid = t["roomid"]
        local battleid = t["battleid"]
        local ip = t["ip"]    
        local port = t["port"]
        print("roomid:"..roomid.." battleid:"..battleid.." ip:"..ip.." port:"..port)
		g_Facade:SendNotification(NotifierEnum.NET_MSG_INFORM_BATTLE_REQ, {MsgId=msgId, Data=pbData, DataLength=pdDataLength})

	end

	return msgId
end
--]]


function mainClient.AdjustFrameRate()
	--UCWFuncLib:CWGConsoleCmd("t.MaxFPS 60.0f")
end

return 1