local CBatchUpdateMediator = class("CBatchUpdateMediator", CMediator)

function CBatchUpdateMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
end

function CBatchUpdateMediator.Destroy(self)
    print("CBatchUpdateMediator -->Destroy")

    self.uiPanel_ = nil

    CMediator.Destroy(self)
end

function CBatchUpdateMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CBatchUpdateMediator -->OnRegisterUI")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_BATCH_UPDATE,  "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_BATCH_UPDATE,  "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CBatchUpdateMediator.OnRegisterCommond(self)
    CMediator.OnRegisterCommond(self)
    print("CBatchUpdateMediator -->OnRegisterCommond")
    -------------------------------------注册Commond命令------------------------------------------------

    -------------------------------------注册Commond命令------------------------------------------------
end


function CBatchUpdateMediator.OnRemove(self)
    print("CBatchUpdateMediator -->OnRemove")

    self.uiPanel_ = nil

    self:RemoveObserver(NotifierEnum.OPEN_BATCH_UPDATE)
    self:RemoveObserver(NotifierEnum.CLOSE_BATCH_UPDATE)

    CMediator.OnRemove(self)
end


function CBatchUpdateMediator.Open(self)
    if self.uiPanel_ == nil then
        self:OnCreatePanel()
    end

    if self.show_ ~= true then
        self:Show()
    end
end

function CBatchUpdateMediator.Close(self)
    if self.show_ == true then
        self:Hide()
    end
end


function CBatchUpdateMediator.OnCreatePanel(self)
   
end


function CBatchUpdateMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then
        self.uiPanel_:AddToViewport(0)
    end
end


function CBatchUpdateMediator.Hide(self)
    self.show_ = false

    if self.show_ then
        self.uiPanel_:RemoveFromViewport()
    end
end

function CBatchUpdateMediator.ListNotificationInterests(self)
    return {}
end

function CBatchUpdateMediator.HandleNotification(self, notification)
    print("CBatchUpdateMediator.HandleNotification...")
end

return CBatchUpdateMediator