local CCommand = class("CCommand", CNotifier)

function CCommand.ctor(self)
	CNotifier.ctor(self)
end

function CCommand.Execute(self, notification)

end

return CCommand