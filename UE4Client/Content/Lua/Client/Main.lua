require "../Common/common"
_logic = require "Logic/logic"

Main = {}

function Main.Init()
	-- init pb
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
	_message:LoadProtocol( protofiles )

	-- connect
	_net_client:Connect( 1, "139.196.33.35", 12027 )

	_net_client:AddConnect( "Main", Main.OnConnect )

	-- logic module
	_logic:Init()
end

function Main.Tick( deltatime )

end

function Main.OnConnect( id, code )

	local MsgLoginReqData = 
	{
	   token = "xxxxx",
	   accountid = "500001",
	   version = "0.0.0.0"
	}
	
    _net_client:Send( 100, "KFMsg.MsgLoginReq", MsgLoginReqData )
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