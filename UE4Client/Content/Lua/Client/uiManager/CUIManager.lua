
local CUIManager = class("CUIManager")

function CUIManager.ctor(self)
	
	self:OnInit()
end

function CUIManager.OnInit(self)

end

function CUIManager.Destroy(self)
	
end

function CUIManager.OnDestroy(self)

end

--[[ 打开UI ]]--
function CUIManager.OpenUI(self, uiKey)
	if uiKey == NotifierEnum.OPEN_GAMESETTING then
		g_Facade:SendNotification(NotifierEnum.OPEN_GAMESETTING)
	elseif uiKey == NotifierEnum.OPEN_COMMCONFIRM then
		g_Facade:SendNotification(NotifierEnum.OPEN_COMMCONFIRM)
	else
		print(">> OpenUI, Fail! uiKey:".. uiKey)
	end
end

--[[ 关闭UI ]]--
function CUIManager.CloseUI(self, uiKey)
	if uiKey == NotifierEnum.CLOSE_GAMESETTING then
		g_Facade:SendNotification(NotifierEnum.CLOSE_GAMESETTING)
	elseif uiKey == NotifierEnum.CLOSE_COMMCONFIRM then
		g_Facade:SendNotification(NotifierEnum.CLOSE_COMMCONFIRM)
	else
		print(">> CloseUI, Fail! uiKey:".. uiKey)
	end
end

--[[ 是否Mediator打开有效UI ]]--
function CUIManager.HasMediatorOpenUI(self, inMediatorName)
	print(inMediatorName)
	if nil == inMediatorName or inMediatorName == CMediator.NAME then
		error(">> CUIManager.HasMediatorOpenUI, inMediatorName is invalid!")
		return
	end

	local mediator = g_View:GetMediator(inMediatorName)
	if nil ~= mediator and nil ~= mediator.IsValidUserWidget then
		return mediator:IsValidUserWidget()
	end
end

return CUIManager