require "../Common/common"
_logic = require "Logic/logic"

Main = {}

function Main.Init()
	-- init protobuf
	local protofiles = 
	{
		"FrameDefineMessage.pb",
		"FrameEnumMessage.pb",
		"FrameCodeMessage.pb",
		"FrameClientMessage.pb",
		"EnumMessage.pb",
		"CodeMessage.pb",
		"DefineMessage.pb",
		"ClientMessage.pb",
	}
	_protobuf:LoadProtocol( "Lua/Protocol", protofiles )

	-- logic module
	_logic:Init()

	_net_client:AddConnect( "Main", Main.OnConnect )

	-- 认证
	_timer:AddDelayTimer( "main", 2, Main.Auth )
end

function Main.Auth()
	local channel = _protobuf:GetEnumId("KFMsg.ChannelEnum", "Internal" )
	local request = { ["channel"] = channel, ["account"] = "lori227" }
	local response = _http_client:PostJson( _define._auth_url, request )
	if response == nil then
		print( "http failed" )
		return
	end

	if response.retcode ~= 1 then
		_display:ShowResult( response.retcode )
		return
	end

	Main._token = response.token
	Main._account_id = response.accountid

	-- connect
	local zone = response["zone"]
	_net_client:Connect( zone.zoneid, zone.ip, zone.port )
end

function Main.Tick( deltatime )
	-- 定时器逻辑
	_timer:Tick( deltatime )

end

function Main.OnConnect( id, code )

	local data = 
	{
	   token = Main._token,
	   accountid = Main._account_id,
	   version = "0.0.0.0"
	}
	
    _net_client:Send( 100, "KFMsg.MsgLoginReq", data )
end
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
function Main.NetConnect( id, code )
	_net_client:OnConnect( id, code )
end

function Main.NetFailed( id, code )
	_net_client:OnFailed( id, code )
end

function Main.NetDisconnect( id, code )
	_net_client:OnDisconnect( id, code )
end

function Main.HandleMessage( msgid, data, length )
	_message:Call( msgid, data, length )
end

return 0