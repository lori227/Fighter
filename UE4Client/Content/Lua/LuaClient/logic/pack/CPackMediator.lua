local CPackMediator = class("CPackMediator", CMediator)

function CPackMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.show_ = false
end

function CPackMediator.Destroy(self)
    print("CPackMediator -->Destroy")
   
    self.uiPanel_ = nil
    self.show_ = false

    CMediator.Destroy(self)
end

function CPackMediator.OnRegisterUI(self)
    CMediator.OnRegisterUI(self)
    print("CPackMediator -->OnRegisterUI")

    -------------------------------------注册UI逻辑相关-------------------------------------------------
    self:RegisterObserver(NotifierEnum.OPEN_PACK, "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_PACK, "Close")
    -------------------------------------注册UI逻辑相关-------------------------------------------------
end

function CPackMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CPackMediator -->OnRegisterCommand")

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_REFRESH_PACK, CPackRefreshPackCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CPackMediator.OnRemove(self)
    print("CPackMediator -->OnRemove")

    self.uiPanel_ = nil
    self.show_ = false

    self:RemoveObserver(NotifierEnum.OPEN_PACK)
    self:RemoveObserver(NotifierEnum.CLOSE_PACK)

    g_Facade:RemoveCommand(NotifierEnum.REQUEST_REFRESH_PACK)

    CMediator.OnRemove(self)
end

function CPackMediator.Open(self)
    if self.show_ == false then
        if self.uiPanel_ == nil then
            self:OnCreatePanel()
        else
            if self.canClick_ then
                self:Show()
            end
        end
    else
        if self.canClick_ then
            self:Hide()
        end
    end
end

function CPackMediator.Close(self)
    if self.uiPanel_ then
       self.uiPanel_:RemoveFromViewport()   
    end
end

function CPackMediator.OnCreatePanel(self)
    self.uiPanel_ = slua.loadUI('/Game/Blueprints/UI/Widget/Pack/WB_PackUI.WB_PackUI')
    local packProxy = g_Facade:RetrieveProxy(ProxyEnum.PACK)
    local packBox = self.uiPanel_:FindWidget('PackBox')
    local row_ = 0
    local column_ = -1

    for  i = 1, packProxy:GetGridsNum() do
        local packItem = slua.loadUI('/Game/Blueprints/UI/Widget/Pack/WB_PackItem.WB_PackItem')
        local packBox_object =  packBox:AddChildtoUniformGrid(packItem)
        if column_ < 5 then
           column_ = column_ + 1
           else
            row_ = row_ + 1
               column_ = 0 
           end 
        packBox_object:SetRow(row_)
        packBox_object:SetColumn(column_)
        --创建格子对象
        packProxy:AddGrid(i, CPackGridItem.New(packItem))
        local btn = packItem:FindWidget("Button_0")
        btn.OnClicked:Add(function()
           print(">>>>>>>" .. i)
        end)
    end

    --播放绑定回调
    self.uiPanel_.OpenPack.OnAnimationStarted:Add(function ()
        self.canClick_ = false
        self:SetTargetVisibility(self.uiPanel_, 4)  
    end)
    self.uiPanel_.OpenPack.OnAnimationFinished:Add(function ()
        --反放结束为False
        if self.uiPanel_:IsAnimationPlayingForward(self.uiPanel_.OpenPack) == false then
            self:SetTargetVisibility(self.uiPanel_, 1)  
        end
        self.canClick_ = true
    end)

    self.uiPanel_:AddToViewport(1) 
    self.show_ = true 
    self.uiPanel_:PlayAnimation(self.uiPanel_.OpenPack, 0, 1, 3, 1)
        
    g_Facade:SendNotification(NotifierEnum.REQUEST_REFRESH_PACK) 
 end

function CPackMediator.Show(self)
    self.show_ = true

    if self.uiPanel_ then 
        self.uiPanel_:PlayAnimation(self.uiPanel_.OpenPack, 0, 1, 3, 1)
    end
end

function CPackMediator.Hide(self)
    self.show_ = false

    if self.uiPanel_ then
        self.uiPanel_:PlayAnimation(self.uiPanel_.OpenPack, 0, 1, 1, 1)
    end
end

function CPackMediator.ListNotificationInterests(self)
    return {}
end

function CPackMediator.HandleNotification(self, notification)
    print("CPackMediator.HandleNotification...")
end

function CPackMediator.SetTargetVisibility(self, target, visibility)
    if target then
        target:SetVisibility(visibility)
    end
end

return CPackMediator