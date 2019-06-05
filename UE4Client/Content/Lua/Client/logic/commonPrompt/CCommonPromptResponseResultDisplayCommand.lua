local CCommonPromptResponseResultDisplayCommand = class("CCommonPromptResponseResultDisplayCommand", CCommand)
      
function CCommonPromptResponseResultDisplayCommand.ctor(self)
	CCommand.ctor(self)
end

function CCommonPromptResponseResultDisplayCommand.Execute(self, notification)
	print("CCommonPromptResponseResultDisplayCommand.Execute...")

    local body = notification:GetBody()
	local t = pb.decode("KFMsg.MsgResultDisplay", body["Data"])
	local result = t["result"]
  	local str = t["param"]
   	print("~~~~~~~result:" .. tostring(result))
	local p = "服务器提示Id:"..result
	local commonPromptProxy = g_Facade:RetrieveProxy(ProxyEnum.COMMON_PROMPT)
	commonPromptProxy:SetPrompt(p)

	self.uiPromptText_ = p

	g_Facade:SendNotification(NotifierEnum.OPEN_COMMON_PROMPT)
end

return CCommonPromptResponseResultDisplayCommand