
--[[ 
    通用确认
]]--
local KismetInputLibrary = import("KismetInputLibrary")

local CCommConfirmMediator = class("CCommConfirmMediator", CMediator)

-- name: MediatorEnum.COMM_CONFIRM
function CCommConfirmMediator.ctor(self, name)
    CMediator.ctor(self, name)
end

--[[ 注册指令 ]]--
function CCommConfirmMediator.OnRegisterCommand(self)
    print(">> CCommConfirmMediator.OnRegisterCommand, enter.")
    CMediator.OnRegisterCommand(self)
end

--[[ 移除指令 ]]--
function CCommConfirmMediator.OnUnregisterCommand(self)
    print(">> CCommConfirmMediator.OnUnregisterCommand, enter.")
    CMediator.OnUnregisterCommand(self)
end

function CCommConfirmMediator.ListNotificationInterests(self)
    return { }
end

function CCommConfirmMediator.HandleNotification(self, notification)
end

--[[ Callable(Super) ]]--
function CCommConfirmMediator.OnCreateUI(self)
    print(">> CCommConfirmMediator.OnCreateUI, enter.")
    CMediator.OnCreateUI(self)

    self:CreateUserWidget()
end

--[[ Callable(Super) ]]--
function CCommConfirmMediator.OnDestroyedUI(self)
    print(">> CCommConfirmMediator.OnDestroyedUI, enter.")
    CMediator.OnDestroyedUI(self)
end

--[[ Callable(Super) ]]--
function CCommConfirmMediator.OnShow(self)
    print(">> CCommConfirmMediator.OnShow, enter.")
    CMediator.OnShow(self)

    if self.userWidget_ then
        self.userWidget_:AddToViewport(150)
    end
end

--[[ Callable(Super) ]]--
function CCommConfirmMediator.OnClose(self)
    print(">> CCommConfirmMediator.OnClose, enter.")
    CMediator.OnClose(self)

    if self.userWidget_ then
        self.userWidget_:RemoveFromViewport()
    end
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

    self:OnCreate()
 end

--[[ 初始化 ]]--
 function CCommConfirmMediator.Init(self, inParams)
    -- Comm Setting
    if nil ~= inParams then
        if nil ~= inParams.contentKey and "" ~= inParams.contentKey then
            self.userWidget_:SetTxtContentByKey(inParams.contentKey)
        end
        if nil ~= self.userWidget_.OnOkClick and nil ~= inParams.onOkClick then
            self.userWidget_.OnOkClick:Add(inParams.onOkClick)
        end
        if nil ~= self.userWidget_.OnCancelClick and nil ~= inParams.onCancelClick then
            self.userWidget_.OnCancelClick:Add(inParams.onCancelClick)
        end
    end

    self.initParams = inParams
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
    -- Key Event
    self.userWidget_.OnKeyPressed:Add(function(inKey)     self:OnKeyPressed(inKey) end)

    --self.userWidget_:SetIsEnabled(true)
    self.userWidget_:SetKeyboardFocus()
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

    -- Key Event
    self.userWidget_.OnKeyPressed:Clear()
    -- Destroy Listener
    if nil ~= self.userWidget_.OnConstruct then
        self.userWidget_.OnConstruct:Clear()
    end
    if nil ~= self.userWidget_.OnDestruct then
        self.userWidget_.OnDestruct:Clear()
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

-------------------------------------------- Callable ------------------------------------
function CCommConfirmMediator.OnKeyPressed(self, inKey)
    local keyName = KismetInputLibrary.Key_GetDisplayName(inKey)
    print(">> CCommConfirmMediator, ".. keyName)
    if keyName == "Escape" then
        if self.initParams then
            self.initParams.onCancelClick()
        end
    end
end

return CCommConfirmMediator