require "memory/memory"
require "core/core"
--require "framework/framework"
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
	g_TimeCtrl:Update(deltatime)
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

	--初始化网络玩家数据处理中心
	mainClient.InitNetPlayerDataCtrl()

	--初始化pb文件
	mainClient.InitPB()

	--初始化游戏状态机
	mainClient.InitGameState()

	--注册所有的数据代理
	mainClient.RegisterProxyAll()

	--注册所有中介
	mainClient.RegisterMediatorAll()

	--初始化完成
	mainClient.isInitDone_ = true
	do 
		return
	end
end

function mainClient.InitNetPlayerDataCtrl()

	local observer = CObserver.New("HandleLoginAck", g_NetPlayerDataCtrl)
	g_NetPlayerDataCtrl:RegisterObserver(tostring(ProtobufEnum.MSG_LOGIN_ACK), observer)
	
	observer = CObserver.New("HandleSyncUpdateData", g_NetPlayerDataCtrl)
	g_NetPlayerDataCtrl:RegisterObserver(tostring(ProtobufEnum.MSG_SYNC_UPDATE_DATA), observer)

	observer = CObserver.New("HandleSyncAddData", g_NetPlayerDataCtrl)
	g_NetPlayerDataCtrl:RegisterObserver(tostring(ProtobufEnum.MSG_SYNC_ADD_DATA), observer)

	observer = CObserver.New("HandleSyncRemoveData", g_NetPlayerDataCtrl)
	g_NetPlayerDataCtrl:RegisterObserver(tostring(ProtobufEnum.MSG_SYNC_REMOVE_DATA), observer)
end


function mainClient.InitPB()

	--local dir = FToLuaPaths.ProjectContentDir()
	--local filePath = dir .. "Lua/LuaClient/logic/proto/FrameClientMessage.proto"
	--local filePath = "FrameClientMessage.proto"
	--protoc:loadfile(filePath)
	--pbc.register_file(filePath)

	pbc.register_file("FrameDefineMessage.pb")
	pbc.register_file("FrameClientMessage.pb")
	pbc.register_file("EnumMessage.pb")
	pbc.register_file("CodeMessage.pb")
	pbc.register_file("DefineMessage.pb")
	pbc.register_file("ClientMessage.pb")
	pbc.register_file("FrameEnumMessage.pb")
	pbc.register_file("FrameCodeMessage.pb")
	pbc.register_file("ServerMessage.pb")
	pbc.register_file("FrameMessage.pb")
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
	g_GameFSM:AddTransition(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.CHECK_VERSION)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.LOGIN, GameFSMStateIdEnum.MAIN_CAMPSITE)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.MAIN_CAMPSITE, GameFSMStateIdEnum.PVP_MATCH)
	g_GameFSM:AddTransition(GameFSMStateIdEnum.PVP_MATCH, GameFSMStateIdEnum.MAIN_CAMPSITE)
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
    --角色列表--
    g_Facade:RegisterProxy(CRoleListProxy.New(ProxyEnum.ROLE_LIST))
    --角色详情界面--
    g_Facade:RegisterProxy(CRoleListProxy.New(ProxyEnum.ROLE_INFORMATION))

    -------------------------------------游戏大厅-------------------------------------------------

	-------------------------------------游戏设置-------------------------------------------------
	g_Facade:RegisterProxy(CGameSettingProxy.New(ProxyEnum.GAME_SETTING))
	-------------------------------------游戏设置-------------------------------------------------

	-------------------------------------通用确认-------------------------------------------------
	g_Facade:RegisterProxy(CCommConfirmProxy.New(ProxyEnum.COMM_CONFIRM))
	-------------------------------------通用确认-------------------------------------------------
end

--注册所有中介
function mainClient.RegisterMediatorAll()
	print("mainClient.RegisterMediatorAll...")
	-------------------------------------通用提示-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CCommonPromptMediator)
	-------------------------------------通用提示-------------------------------------------------

	-------------------------------------檢測版本-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CCheckVersionMediator)
	-------------------------------------檢測版本-------------------------------------------------

	-------------------------------------版本更新-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CBatchUpdateMediator)
	-------------------------------------版本更新-------------------------------------------------

	-------------------------------------服務器驗證-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CServerAuthMediator)
	-------------------------------------服務器驗證-------------------------------------------------

	----------------------------------------登陸--------------------------------------------------
	g_MediatorFactory:RegisterMediator(CLoginMediator)
	----------------------------------------登陸--------------------------------------------------

	-------------------------------------1vs1PVP匹配--------------------------------------------------
	g_MediatorFactory:RegisterMediator(CPVPMatchMediator)
	-------------------------------------1vs1PVP匹配--------------------------------------------------

	-------------------------------------游戏大厅--------------------------------------------------
	g_MediatorFactory:RegisterMediator(CMainCampsiteMediator)
	--背包--
	g_MediatorFactory:RegisterMediator(CPackMediator) 
	--招募所--
	g_MediatorFactory:RegisterMediator(CDeviationMediator) 
	g_MediatorFactory:RegisterMediator(CNewHeroDisplayMediator) 
	g_MediatorFactory:RegisterMediator(CRecruitmentOfficeMediator)
	--角色列表--
    g_MediatorFactory:RegisterMediator(CRoleListMediator)
    --角色详情界面--
    g_MediatorFactory:RegisterMediator(CRoleInformationMediator)
    --队伍管理--
    g_MediatorFactory:RegisterMediator(CTeamManagementMediator)
	-------------------------------------游戏大厅--------------------------------------------------
	
	-------------------------------------游戏设置-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CGameSettingMediator)
	-------------------------------------游戏设置-------------------------------------------------

	-------------------------------------通用确认-------------------------------------------------
	g_MediatorFactory:RegisterMediator(CCommConfirmMediator)
	-------------------------------------通用确认-------------------------------------------------
end


function mainClient.ProcessReceiveMessage(msgId, pbData, pdDataLength)
	do
		print("~~~~~~~~~~~~~~~~mainClient.ProcessReceiveMessage, msgId:" .. msgId)
		g_Facade:SendNotification(tostring(msgId), {MsgId=msgId, Data=pbData, DataLength=pdDataLength})
		return msgId
	end
end

function mainClient.OnDisconnect()
	print("lua mainClient.OnDisconnect...")
	g_Facade:SendNotification(NotifierEnum.SOCKET_DISCONNECT, "网络连接中断！")
end

function mainClient.AdjustFrameRate()
	--UCWFuncLib:CWGConsoleCmd("t.MaxFPS 60.0f")
end

return 1