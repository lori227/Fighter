--pbc = require "protobuf"
require "../Common/Common"

Main = {}

function Main.Init()

	-- connect
	FLuaBind.Connect( "139.196.33.35", 12027 )
end

function Main.Tick( deltatime )

end

------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
function Main.NetConnect( code )
end

function Main.NetFailed( code )
	print( "net failed code = " .. code )
end

function Main.NetDisconnect( code )
end

function Main.HandleMessage( msgid, data, length )
	
end

return 0