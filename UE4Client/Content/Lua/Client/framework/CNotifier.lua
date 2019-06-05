local CNotifier = class("CNotifier")

function CNotifier:ctor(self)

end

function CNotifier.SendNotification(self, notificationName, body, type)
	print("CNotifier.SendNotification... notificationName:"..notificationName)
	g_Facade:SendNotification(notificationName, body, type)
end


return CNotifier