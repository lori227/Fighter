local CPlayer = class( "CPlayer" )

function CPlayer:ctor()
    self._id = 0
end

function CPlayer:Init()
    _message:Add( _protobuf:GetMsgId( "MSG_LOGIN_ACK" ), "KFMsg.MsgLoginAck", 
    function( msg )
         self:HandleLoginAck( msg )
    end )

    _message:Add( _protobuf:GetMsgId( "MSG_SYNC_UPDATE_DATA" ), "KFMsg.MsgSyncUpdateData", 
    function( msg )
         self:HandleSyncUpdateData( msg )
    end )

    _message:Add( _protobuf:GetMsgId( "MSG_SYNC_ADD_DATA" ), "KFMsg.MsgSyncAddData", 
    function( msg )
         self:HandleSyncAddData( msg )
    end )

    _message:Add( _protobuf:GetMsgId( "MSG_SYNC_REMOVE_DATA" ), "KFMsg.MsgSyncRemoveData", 
    function( msg )
         self:HandleSyncRemoveData( msg )
    end )
end

function CPlayer:HandleLoginAck( msg )
    self._id = msg.playerid
    _kernel:InitData( msg.playerid, msg.playerdata )

    local data = 
	{
	   matchid = 1,
       serverid = 0,
	   version = "0.0.0.0"
	}
	
    _net_client:Send( _protobuf:GetMsgId( "MSG_START_MATCH_REQ" ), "KFMsg.MsgStartMatchReq", data )
end

function CPlayer:HandleSyncUpdateData( msg )
    _kernel:SyncUpdateData( msg.pbdata )
end

function CPlayer:HandleSyncAddData( msg )
    _kernel:SyncAddData( msg.pbdata )
end

function CPlayer:HandleSyncRemoveData( msg )
    _kernel:SyncRemoveData( msg.pbdata )
    table.print( _kernel._data )
end

return CPlayer