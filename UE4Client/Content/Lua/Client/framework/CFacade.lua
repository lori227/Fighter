local CFacade = class("CFacade")

function CFacade.ctor(self)
end

function CFacade.RegisterProxy(self, proxy)
    g_Model:RegisterProxy(proxy)
end

function CFacade.RetrieveProxy(self, proxyName)
    return g_Model:RetrieveProxy(proxyName)
end

function CFacade.RemoveProxy(self, proxyName)
    return g_Model:RemoveProxy(proxyName)
end

function CFacade.HasProxy(self, proxyName)
    return g_Model:HasProxy(proxyName)
end

function CFacade.RegisterCommand(self, notificationName, commandType)
    g_Controller:RegisterCommand(notificationName, commandType)
end

function CFacade.RemoveCommand(self, notificationName)
    g_Controller:RemoveCommand(notificationName)
end

function CFacade.HasCommand(self, notificationName)
    return g_Controller:HasCommand(notificationName)
end

function CFacade.RegisterMediator(self, mediator)
    g_View:RegisterMediator(mediator)
end

function CFacade.RetrieveMediator(self, mediatorName)
    return g_View:RetrieveMediator(mediatorName)
end

function CFacade.RemoveMediator(self, mediatorName)
    return g_View:RemoveMediator(mediatorName)
end

function CFacade.HasMediator(self, mediatorName)
    return g_View:HasMediator(mediatorName)
end

function CFacade.SendNotification(self, notificationName, body, type)
    self:NotifyObservers(CNotification.New(notificationName, body, type))
end

function CFacade.NotifyObservers(self, notification)
    g_View:NotifyObservers(notification)
end

return CFacade