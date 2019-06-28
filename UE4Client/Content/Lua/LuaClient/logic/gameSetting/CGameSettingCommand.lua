
local CGameSettingCommand = class("CGameSettingCommand", CCommand)

function CGameSettingCommand.ctor(self)
	CCommand.ctor(self)
end

function CGameSettingCommand.Execute(self, notification)
	print("CGameSettingCommand.Execute...")
end

return CGameSettingCommand