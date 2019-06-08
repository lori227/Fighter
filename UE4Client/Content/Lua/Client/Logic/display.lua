local CDisplay = class( "CDisplay" )

function CDisplay:ctor()

end

function CDisplay:Init()
    local msgid = _protobuf:GetMsgId( "MSG_RESULT_DISPLAY" )
    _message:Add( msgid, "KFMsg.MsgResultDisplay", function( msg )
        self:ShowDisplay( msg )
    end )
end

function CDisplay:ShowDisplay( msg )
    _log:LogInfo( "display result=["..msg.result.."]" )
end


return CDisplay