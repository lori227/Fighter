local CPlayer = class( "CPlayer" )

function CPlayer:ctor()
    self._id = 0
end

function CPlayer:Init()
    _message:Add( _protobuf:GetMsgId( "MSG_LOGIN_ACK" ), "KFMsg.MsgLoginAck", function( msg ) self:HandleLoginAck( msg ) end )
end

function CPlayer:HandleLoginAck( msg )
    self._id = msg.playerid
    print( msg.playerid )
    print( msg.servertime )

    -- local playerdata = msg.playerdata
    -- for k, v in pairs( playerdata ) do
    --     print( k )
    -- end
    -- table.dump( msg.playerdata, "playerdata -->" )
end


return CPlayer