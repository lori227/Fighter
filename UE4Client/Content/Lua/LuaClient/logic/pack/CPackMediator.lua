local CPackMediator = class("CPackMediator", CMediator)

function CPackMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
end

function CPackMediator.OnInit(self)
    print("CPackMediator -->OnInit")
    CMediator.OnInit(self)
end

function CPackMediator.OnDestroyed(self)
    print("CPackMediator -->OnDestroyed")
   
    self.uiPanel_ = nil
    self.show_ = false

    CMediator.Destroy(self)
end


function CPackMediator.OnRegisterCommand(self)
    print("CPackMediator -->OnRegisterCommand")
    CMediator.OnRegisterCommand(self)

    -------------------------------------注册Commond命令------------------------------------------------
    g_Facade:RegisterCommand(NotifierEnum.REQUEST_REFRESH_PACK, CPackRefreshPackCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CPackMediator.OnRemoveCommand(self)
    print("CPackMediator -->OnRemoveCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    g_Facade:RemoveCommand(NotifierEnum.REQUEST_REFRESH_PACK)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnRemoveCommand(self)
end

function CPackMediator.OnShow(self)

    self:AddToViewport(0)
end

function CPackMediator.OnClose(self)

    self:RemoveFromViewport()
end


function CPackMediator.OnCreateUI(self)
    print("CPackMediator -->OnCreateUI")
    CMediator.OnCreateUI(self)

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/Pack/WB_PackUI.WB_PackUI')
    local packProxy = g_Facade:RetrieveProxy(ProxyEnum.PACK)
    local packBox = self.userWidget_:FindWidget('PackBox')
    local row_ = 0
    local column_ = -1

    print(packProxy.gridsNum_)

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
    self.anim_ = self.userWidget_.OpenPack
    self.userWidget_.OpenPack.OnAnimationStarted:Add(function ()
        self.canClick_ = false
        self:SetTargetVisibility(self.userWidget_, 4)  
    end)
    self.userWidget_.OpenPack.OnAnimationFinished:Add(function ()
        --反放结束为False
        if self.userWidget_:IsAnimationPlayingForward(self.userWidget_.OpenPack) == false then
            self:SetTargetVisibility(self.userWidget_, 1)  
        end
        self.canClick_ = true
    end)

    --self.userWidget_:AddToViewport(1) 
    self.show_ = true 
    self.userWidget_:PlayAnimation(self.userWidget_.OpenPack, 0, 1, 3, 1)
        
    g_Facade:SendNotification(NotifierEnum.REQUEST_REFRESH_PACK) 
 end

 function CPackMediator.OnDestroyedUI(self)
    print("CPackMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
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