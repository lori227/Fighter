Main = {}

function Main.Init()

	print( _VERSION )

	-- connect
	FLuaBind.Connect( "192.168.1.155", 12005 )
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