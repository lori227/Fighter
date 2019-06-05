
--[[
	UI Util
]]--

UIUtil = {}

UIUtil.UI_BASE_PATH = "/Game/Blueprints/UI/Widget/"

UIUtil.USER_WIDGET_ENUM =
{
	UI_SETTING = UIUtil.UI_BASE_PATH .. "Fight/WB_WinSetting.WB_WinSetting",
	UI_COMMCONFIRM = UIUtil.UI_BASE_PATH .. "Comm/WB_ComConfirm.WB_ComConfirm"
}
--SetErrorIndex(UIUtil.USER_WIDGET_ENUM)

function UIUtil.Init()

end

function UIUtil.SetWidgetVisibility(inWidget, inVisibility)
	if nil ~= inWidget then
		inWidget:SetVisibility(inVisibility)
	else
		--dump(inWidget)
		print(">> SetWidgetVisibility, inWidget is nil!!!")
	end
end

function UIUtil.SetWidgetPosition(inWidget, inPosition)
	if nil ~= inWidget then
		-- TODO:
	end
end

return UIUtil