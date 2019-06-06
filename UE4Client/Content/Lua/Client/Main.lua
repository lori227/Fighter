--pbc = require "protobuf"
require "../Common/common"

Main = {}

function Main.Init()

	-- connect
	--FLuaBind.Connect( "139.196.33.35", 12027 )

	_kernel.SetObjectValue( "signin", "day", 2 )
	local day = _kernel.GetObjectValue( "signin", "day" )
	print( day )
end

function Main.Tick( deltatime )

end

function Main.Money( data )
	print( "money") 
end

function Main.Level( data )
	print( "level" )
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
	_message.Call( msgid, data, length )
end

return 0