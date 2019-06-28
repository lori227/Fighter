local CController = class("CController")


function CController.ctor(self)
	self.commandMap_ = {}
end	


function CController.ExecuteCommand(self, note)
	if note == nil then
		error("CController.ExecuteCommand, note:", note)
		return 
	end

	local commandType = nil
	if not self.commandMap_[note:GetName()]  then 
		return 
	end

	commandType = self.commandMap_[note:GetName()]

	local commandInstance = commandType.New()
	commandInstance:Execute(note)
end


function CController.RegisterCommand(self, notificationName, commandType)
	if notificationName == nil or notificationName == "" then
		error("CController.RegisterCommand, notificationName:", notificationName)
		return
	end

	if commandType == nil then
		error("CController.RegisterCommand, commandType:", commandType)
		return
	end

	if not self.commandMap_[notificationName] then
		g_View:RegisterObserver(notificationName, CObserver.New("ExecuteCommand", self))
	end
	self.commandMap_[notificationName] = commandType
end


function CController.UnregisterCommand(self, notificationName)
	if notificationName == nil or notificationName == "" then
		error("CController.UnregisterCommand, notificationName:", notificationName)
		return
	end

	if self.commandMap_[notificationName] then
		g_View:UnregisterObserver(notificationName, self)
		self.commandMap_[notificationName] = nil
		--table.remove(self.commandMap_, notificationName)
	end
end


function CController.HasCommand(self, notificationName)
	return self.commandMap_[notificationName] ~= nil
end


return CController
