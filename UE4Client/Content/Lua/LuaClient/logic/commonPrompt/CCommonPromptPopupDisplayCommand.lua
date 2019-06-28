local CCommonPromptPopupDisplayCommand = class("CCommonPromptPopupDisplayCommand", CCommand)
      
function CCommonPromptPopupDisplayCommand.ctor(self)
	CCommand.ctor(self)
end

function CCommonPromptPopupDisplayCommand.Execute(self, notification)
	print("CCommonPromptPopupDisplayCommand.Execute...")
 	self:PopupDisplay(notification)
end

function CCommonPromptPopupDisplayCommand.PopupDisplay(self, notification)
	local body = notification:GetBody()
	g_Facade:RetrieveProxy(ProxyEnum.COMMON_PROMPT):SetPrompt(body)
	CCommonPromptMediator:Show()
end

return CCommonPromptPopupDisplayCommand