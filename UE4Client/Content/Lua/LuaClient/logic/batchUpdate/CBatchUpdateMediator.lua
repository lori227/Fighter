local CBatchUpdateMediator = class("CBatchUpdateMediator", CMediator)

function CBatchUpdateMediator.ctor(self, name)
    CMediator.ctor(self, name)
end

function CBatchUpdateMediator.OnInit(self)
    print("CBatchUpdateMediator -->OnInit")
    CMediator.OnInit(self)
end

function CBatchUpdateMediator.OnDestroyed(self)
    print("CBatchUpdateMediator -->OnDestroyed")

    self:OnDestroyedUI()

    CMediator.OnRemove(self)
end


function CBatchUpdateMediator.OnRegisterCommand(self)
    print("CBatchUpdateMediator -->OnRegisterCommond")
    CMediator.OnRegisterCommand(self)
    -------------------------------------注册Commond命令------------------------------------------------

    -------------------------------------注册Commond命令------------------------------------------------
end


function CBatchUpdateMediator.OnUnregisterCommand(self)
    print("CBatchUpdateMediator -->OnRemoveCommand")
    -------------------------------------移除注册Commond命令------------------------------------------------

    -------------------------------------移除注册Commond命令------------------------------------------------
    CMediator.OnRemoveCommand(self)
end


function CBatchUpdateMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CBatchUpdateMediator -->OnCreateUI")

end

function CBatchUpdateMediator.OnDestroyedUI(self)
    print("CBatchUpdateMediator -->OnDestroyedUI")
    
    CMediator.OnDestroyUI(self)
end



function CBatchUpdateMediator.OnShow(self)
    self.show_ = true

    self:AddToViewport()
end


function CBatchUpdateMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
end

function CBatchUpdateMediator.ListNotificationInterests(self)
    return {}
end

function CBatchUpdateMediator.HandleNotification(self, notification)
    print("CBatchUpdateMediator.HandleNotification...")
end

return CBatchUpdateMediator