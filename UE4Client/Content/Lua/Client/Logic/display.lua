local CDisplay = class( "CDisplay" )
local unpack = unpack or table.unpack

function CDisplay:ctor()

end

function CDisplay:Init()
    _message:Add( _protobuf:GetMsgId( "MSG_RESULT_DISPLAY" ), "KFMsg.MsgResultDisplay", function( msg ) self:HandleShowDisplay( msg ) end )
end

function CDisplay:HandleShowDisplay( msg )
    self:ShowResult( msg.result, msg.param )
end

function CDisplay:ShowResult( result, param )
    _log:LogInfo( "display result=["..result.."]" )
end


return CDisplay