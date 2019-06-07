local M = {}

function M.Init()
    local msgid = _message.GetFrameClientMsgId( "MSG_RESULT_DISPLAY" )
    _message.Add( msgid, "KFMsg.MsgResultDisplay", ShowDisplay )
end

local function ShowDisplay( data )
    table.print( data )

    _log.LogInfo( "display result=["..data.result.."]" )
end


return M