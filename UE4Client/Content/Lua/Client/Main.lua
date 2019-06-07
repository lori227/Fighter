--pbc = require "protobuf"
require "../Common/common"

Main = {}

function Main.Init()

	-- init pb
	Main.LoadProtocol()

	-- connect
	_net_client.Connect( "139.196.33.35", 12027 )

end

function Main.Tick( deltatime )

end

------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
function Main.LoadProtocol()
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

	local protodir = string.format( "%sLua/Protocol", FLuaBind.ContentDir() )
	for _, v in ipairs( protofiles ) do
		local protofile = string.format( "%s/%s", protodir, v )
		_pbc.register_file(protofile)
	end
end


function Main.NetConnect( code )
	local MsgLoginReqData = 
	{
	   token = "xxxxx",
	   accountid = "500001",
	   version = "0.0.0.0"
	}
	
	_net_client.Send( 100, "KFMsg.MsgLoginReq", MsgLoginReqData )
end

function Main.NetFailed( code )
	print( "net failed code = " .. code )
end

function Main.NetDisconnect( code )

end

function Main.HandleMessage( msgid, data, length )
	_message.Call( msgid, data, length )
end

return 0