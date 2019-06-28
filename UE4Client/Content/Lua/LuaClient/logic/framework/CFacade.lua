local CFacade = class("CFacade")


function CFacade.ctor(self)

end

function CFacade.RegisterProxy(self, proxy)
    g_Model:RegisterProxy(proxy)
end


function CFacade.RetrieveProxy(self, proxyName)
    return g_Model:RetrieveProxy(proxyName)
end


function CFacade.UnregisterProxy(self, proxyName)
    return g_Model:UnregisterProxy(proxyName)
end


function CFacade.HasProxy(self, proxyName)
    return g_Model:HasProxy(proxyName)
end


function CFacade.RegisterCommand(self, notificationName, commandType)
    g_Controller:RegisterCommand(notificationName, commandType)
end

function CFacade.UnregisterCommand(self, notificationName)
    g_Controller:UnregisterCommand(notificationName)
end


function CFacade.HasCommand(self, notificationName)
    return g_Controller:HasCommand(notificationName)
end


function CFacade.SendNotification(self, notificationName, body, type)
    self:NotifyObservers(CNotification.New(notificationName, body, type))
end

function CFacade.NotifyObservers(self, notification)
    g_NetPlayerDataCtrl:NotifyObservers(notification)
    g_View:NotifyObservers(notification)
end

return CFacade