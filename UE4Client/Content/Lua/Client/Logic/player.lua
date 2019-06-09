local CPlayer = class( "CPlayer" )

function CPlayer:ctor()
    self._id = 0
end

function CPlayer:Init()
    _message:Add( _protobuf:GetMsgId( "MSG_LOGIN_ACK" ), "KFMsg.MsgLoginAck", 
    function( msg )
         self:HandleLoginAck( msg )
    end )

    _kernel:RegisterUpdateDataFunction( "id", 
    function( key, oldvalue, newvalue )
        self:OnServerIdUpdate( key, oldvalue, newvalue )
    end )
end

function CPlayer:HandleLoginAck( msg )
    self._id = msg.playerid
    _kernel:InitData( msg.playerid, msg.playerdata )
end

function CPlayer:OnServerIdUpdate( key, oldvalue, newvalue )
    print( "key.."..key )
    print( "oldvalue.."..oldvalue )
    print( "newvalue.."..newvalue )
end

return CPlayer