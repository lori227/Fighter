
--[[ 
    通用确认
]]--

local CCommConfirmMediator = class("CCommConfirmMediator", CMediator)

-- name: MediatorEnum.COMM_CONFIRM
function CCommConfirmMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.show_ = false
end

function CCommConfirmMediator.Destroy(self)
    CMediator.Destroy(self)
end

function CCommConfirmMediator.Open(self, inParams)
    print(">> CCommConfirmMediator.Open, enter.")
    --table.print(inParams)

    if nil == self.userWidget_ then
        self:CreateUserWidget(inParams)
    end

    if not self.show_ then
        self:Show()
    end
end

function CCommConfirmMediator.Close(self, inParams)
    print(">> CCommConfirmMediator.Close, enter.")
    --table.print(inParams)

    if self.show_ then
        self:Hide()
    end
end

function CCommConfirmMediator.Show(self)
    print(">> CCommConfirmMediator.Show, enter.")
    self.show_ = true

    if self.userWidget_ then
        self.userWidget_:AddToViewport(150)
    end
end

function CCommConfirmMediator.Hide(self)
    print(">> CCommConfirmMediator.Hide, enter.")
    self.show_ = false

    if self.userWidget_ then
        self.userWidget_:RemoveFromViewport()
        self:OnDestroyed()
    end
end

--[[ 注册监听 ]]--
function CCommConfirmMediator.OnRegisterUI(self)
    print(">> CCommConfirmMediator.OnRegisterUI, enter.")
    CMediator.OnRegisterUI(self)

    self:RegisterObserver(NotifierEnum.OPEN_COMMCONFIRM, "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_COMMCONFIRM, "Close")
end

--[[ 注册指令 ]]--
function CCommConfirmMediator.OnRegisterCommand(self)
    print(">> CCommConfirmMediator.OnRegisterCommand, enter.")
    CMediator.OnRegisterCommand(self)
end

--[[ 移除 ]]--
function CCommConfirmMediator.OnRemove(self)
    print(">> CCommConfirmMediator.OnRemove, enter.")
    self:OnDestroyed()

    CMediator.OnRemove(self)
end

function CCommConfirmMediator.ListNotificationInterests(self)
    return { }
end

function CCommConfirmMediator.HandleNotification(self, notification)
end

--[[ 创建UserWidget ]]--
function CCommConfirmMediator.CreateUserWidget(self, inParams)
    print(">> CCommConfirmMediator.CreateUserWidget, enter.")
    self.userWidget_ = slua.loadUI(UIUtil.USER_WIDGET_ENUM.UI_COMMCONFIRM)
    if nil == self.userWidget_ then
        error(">> CCommConfirmMediator.CreateUserWidget, self.userWidget_ is nil!")
        return
    end
    
    -- Init Main Userwidget Delegete
    if nil ~= self.userWidget_.OnConstruct then
        self.userWidget_.OnConstruct:Add(function()     self:OnConstruct() end)
    end
    if nil ~= self.userWidget_.OnDestruct then
        self.userWidget_.OnDestruct:Add(function()      self:OnDestruct() end)
    end
    if nil ~= self.userWidget_.OnBeginDestroy then
        self.userWidget_.OnBeginDestroy:Add(function()  self:OnDestroyed() end)
    end

    -- Comm Setting
    local paramBody = inParams and inParams:GetBody() or nil
    if nil ~= paramBody then
        if nil ~= paramBody.contentKey and "" ~= paramBody.contentKey then
            self.userWidget_:SetTxtContentByKey(paramBody.contentKey)
        end
        if nil ~= self.userWidget_.OnOkClick and nil ~= paramBody.onOkClick then
            self.userWidget_.OnOkClick:Add(paramBody.onOkClick)
        end
        if nil ~= self.userWidget_.OnCancelClick and nil ~= paramBody.onCancelClick then
            self.userWidget_.OnCancelClick:Add(paramBody.onCancelClick)
        end
    end

    self:OnCreate()
 end

--[[ 初始化回调 ]]--
function CCommConfirmMediator.OnCreate(self)
    -- Init Reference
    -- Init Listener
    -- Init List
    -- InitializeImpl
end

--[[ 构造回调(CWUserWidget) ]]--
function CCommConfirmMediator.OnConstruct(self)
    print(">> CCommConfirmMediator.OnConstruct, enter.")
end

--[[ 销毁回调(CWUserWidget) ]]--
function CCommConfirmMediator.OnDestruct(self)
    print(">> CCommConfirmMediator.OnDestruct, enter.")
    self:OnDestroyed()
end

--[[ 销毁回调 ]]--
function CCommConfirmMediator.OnDestroyed(self)
    print(">> CCommConfirmMediator.OnDestroyed, enter.")
    if nil == self.userWidget_ then
        print(">> CCommConfirmMediator.OnDestroyed, already destroy!")
        return
    end

    -- Destroy Listener
    if nil ~= self.userWidget_.OnConstruct then
        self.userWidget_.OnConstruct:Clear()
    end
    if nil ~= self.userWidget_.OnDestruct then
        self.userWidget_.OnDestruct:Clear()
    end
    if nil ~= self.userWidget_.OnBeginDestroy then
        self.userWidget_.OnBeginDestroy:Clear()
    end

    if nil ~= self.userWidget_.OnOkClick then
        self.userWidget_.OnOkClick:Clear()
    end
    if nil ~= self.userWidget_.OnCancelClick then
        self.userWidget_.OnCancelClick:Clear()
    end

    -- Destroy Reference
    -- Destroy List
    self.userWidget_ = nil
    self.show_ = false
end

-------------------------------------------- Get/Set ------------------------------------
function CCommConfirmMediator.GetUserWidget(self)
    return self.userWidget_
end

function CCommConfirmMediator.IsValidUserWidget(self)
    return self.userWidget_ ~= nil
end

return CCommConfirmMediator