local CMainCampsiteRequestAddDataCommand = class("CMainCampsiteRequestAddDataCommand", CCommand)

function CMainCampsiteRequestAddDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CMainCampsiteRequestAddDataCommand.Execute(self, notification)
	print("CMainCampsiteRequestAddDataCommand.Execute...")

	self:AddData()
end

function CMainCampsiteRequestAddDataCommand.AddData(self, notification)
	local params = {}	
	local cost = "[{\"money\":\"10000\"}]"
	table.insert(params, cost)
	local MsgCommonReqData = 
	{	
		command = "adddata",
		params  = params,
	}
	--table.print(MsgCommonReqData)
	local str = pbc.encode("KFMsg.MsgCommandReq", MsgCommonReqData)
	g_Network:Send(ProtobufEnum.MSG_COMMAND_REQ, str, #str)

end

return CMainCampsiteRequestAddDataCommand