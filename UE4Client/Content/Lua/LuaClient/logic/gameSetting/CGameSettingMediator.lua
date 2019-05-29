
--[[ 
    设置界面
]]--
local CWAudioVideoMgr = import("CWAudioVideoMgr")
local CWLocalDataMgr = import("CWLocalDataMgr")
local CWGameSettingSG = import("CWGameSettingSG")

local CGameSettingMediator = class("CGameSettingMediator", CMediator)

-- name: MediatorEnum.GAME_SETTING
function CGameSettingMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.show_ = false
end

function CGameSettingMediator.Destroy(self)
    CMediator.Destroy(self)
end

function CGameSettingMediator.Open(self, inParams)
    print(">> CGameSettingMediator.Open, enter.")
    --table.print(inParams)

    if nil == self.userWidget_ then
        self:CreateUserWidget()
    end

    if not self.show_ then
        self:Show()
    end
end

function CGameSettingMediator.Close(self, inParams)
    print(">> CGameSettingMediator.Close, enter.")
    --table.print(inParams)

    if self.show_ then
        self:Hide()
    end
end

function CGameSettingMediator.Show(self)
    print(">> CGameSettingMediator.Show, enter.")
    self.show_ = true

    if self.userWidget_ then
        self.userWidget_:AddToViewport(50)
    end
end

function CGameSettingMediator.Hide(self)
    print(">> CGameSettingMediator.Hide, enter.")
    self.show_ = false

    if self.userWidget_ then
        self.userWidget_:RemoveFromViewport()
        --self:OnDestroyed()
    end
end

--[[ 注册监听 ]]--
function CGameSettingMediator.OnRegisterUI(self)
    print(">> CGameSettingMediator.OnRegisterUI, enter.")
    CMediator.OnRegisterUI(self)

    self:RegisterObserver(NotifierEnum.OPEN_GAMESETTING, "Open")
    self:RegisterObserver(NotifierEnum.CLOSE_GAMESETTING, "Close")
end

--[[ 注册指令 ]]--
function CGameSettingMediator.OnRegisterCommand(self)
    print(">> CGameSettingMediator.OnRegisterCommand, enter.")
    CMediator.OnRegisterCommand(self)
end

--[[ 移除 ]]--
function CGameSettingMediator.OnRemove(self)
    print(">> CGameSettingMediator.OnRemove, enter.")
    self:OnDestroyed()

    CMediator.OnRemove(self)
end

function CGameSettingMediator.ListNotificationInterests(self)
    return { }
end

function CGameSettingMediator.HandleNotification(self, notification)
end

--[[ 创建UserWidget ]]--
function CGameSettingMediator.CreateUserWidget(self, inParams)
    print(">> CGameSettingMediator.CreateUserWidget, enter.")
    self.userWidget_ = slua.loadUI(UIUtil.USER_WIDGET_ENUM.UI_SETTING)
    if nil == self.userWidget_ then
        --dump(self)
        error(">> CGameSettingMediator.CreateUserWidget, self.userWidget_ is nil!")
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

    self:OnCreate()
 end

--[[ 初始化回调 ]]--
function CGameSettingMediator.OnCreate(self)
    -- Init Base Data
    local LocalDataMgr = CWLocalDataMgr.GetLocalDataMgr(self.userWidget_)
    if nil ~= LocalDataMgr then
        self.userWidget_.GameSettingSaveData = CWLocalDataMgr:GetGameSettingData()
        self.userWidget_.GameSettingData = CWGameSettingSG.NewGameSettingSG(self.userWidget_)
        CWGameSettingSG.CopyProperty(self.userWidget_.GameSettingData, self.userWidget_.GameSettingSaveData)
    else
        error(">> CGameSettingMediator.OnCreate, LocalDataMgr is nil!")
    end

    -- Init Reference
    self.trsSwitcher_ = self.userWidget_:FindWidget("TrsSwitcher")
    self.btnClose_ = self.userWidget_:FindWidget("BtnClose")
    self.btnReset_ = self.userWidget_:FindWidget("BtnReset")
    self.btnApply_ = self.userWidget_:FindWidget("BtnApply")
    self.btnRefresh_ = self.userWidget_:FindWidget("BtnRefresh")
    self.btnVolume_ = self.userWidget_:FindWidget("BtnVolume")
    self.txtWinMode_ = self.userWidget_:FindWidget("TxtWinMode")
    self.cBWinMode_ = self.userWidget_:FindWidget("CBWinMode")
    self.trsCheckBoxGroup_ = self.userWidget_:FindWidget("TrsCheckBoxGroup")

    -- Init Listener
    self.btnClose_.OnClicked:Add(function()    self:OnClickedBtnClose()  end)
    self.btnReset_.OnClicked:Add(function()    self:OnClickedBtnReset()  end)
    self.btnApply_.OnClicked:Add(function()    self:OnClickedBtnApply()  end)
    --self.btnRefresh_.OnClicked:Add(function()  self:OnClickedBtnRefresh()  end)
    self.btnVolume_.OnClicked:Add(function()   self:OnClickedBtnVolume()  end)
    self.trsCheckBoxGroup_.OnStateChanged:Add( function(inCheckBox, inChangeArray)  self:OnStateChangedCheckBoxGroup(inCheckBox, inChangeArray)  end)
    self.cBWinMode_.OnCheckStateChanged:Add(   function(bIsChecked)   self:OnCheckStateChangedWinMode(bIsChecked)  end)

    -- Init List
    local imgSelectedName, btnSelectedName = "ImgSelected", "BtnSelected"
    self.selectedList_ = {}
    for i = 1, 3 do
        local newIdx = i - 1
        local imgSelected = self.userWidget_:FindWidget(imgSelectedName .. newIdx)
        local btnSelected = self.userWidget_:FindWidget(btnSelectedName .. newIdx)

        btnSelected.OnClicked:Add(function()    self:SwitchPage(newIdx)  end)
        btnSelected.OnHovered:Add(function()    self:OnHoveredBtnSwitch(newIdx) end)
        --btnSelected.OnUnhovered:Add(function()  self:OnUnhoveredBtnSwitch(newIdx) end)

        self.selectedList_[i] = { idx = newIdx, img = imgSelected, btn = btnSelected, ["Test"] = 110 }
    end
    --table.print(self.selectedList_)

    local itemGamePlayName, cBExpName, txtTipsName = "ItemGamePlay", "CBExp", "TxtTips"
    self.itemGamePlayList_ = {}
    for i = 1, 3 do
        local newIdx = i - 1
        local itemGamePlay = self.userWidget_:FindWidget(itemGamePlayName .. newIdx)
        local cBExp = itemGamePlay:FindWidget(cBExpName)
        local txtTips = itemGamePlay:FindWidget(txtTipsName)
        --cBExp.OnCheckStateChanged:Add(function(bIsChecked)   self:OnCheckStateChangedGamePlay(bIsChecked, i)  end)

        self.itemGamePlayList_[i] = { item = itemGamePlay, checkBox = cBExp, txtTips = txtTips }
    end
    --table.print(self.itemGamePlayList_)

    -- InitializeImpl
    --[[self.settingData_ = {
        pawnUIMode = false,
        bWindowMode = true,
        resolution = { x = 1280, y = 720 },--FIntPoint.New(1280, 720),
        audioSettings = {
            { AudioSetType = 0, bEnableAudio = true, AudioTypeVolume = 100 },
            { AudioSetType = 1, bEnableAudio = true, AudioTypeVolume = 100 },
            { AudioSetType = 2, bEnableAudio = true, AudioTypeVolume = 100 },
            { AudioSetType = 3, bEnableAudio = true, AudioTypeVolume = 100 },
            { AudioSetType = 4, bEnableAudio = true, AudioTypeVolume = 100 }
        }
    }
    table.print(self.settingData_)]]--
    self.trsCheckBoxGroup_:InitCheckBoxGroup()
    self.userWidget_:UpdateSettingWidget()
    for i, elem in ipairs(self.itemGamePlayList_) do
        if nil ~= elem.checkBox and nil ~= elem.txtTips then
            local newTxt = elem.checkBox:IsChecked() and "ON" or "OFF"
            elem.txtTips:SetText(newTxt)
        end
    end

    local bIsWindowsMode = self.userWidget_.GameSettingData.bWindowMode
    print(bIsWindowsMode)
    self.cBWinMode_:SetIsChecked(bIsWindowsMode)
    self:OnCheckStateChangedWinMode(bIsWindowsMode)

    self.audioSettings_ = {}
    self.audioSettNodes_ = {}
    for i = 1, 5 do
        local newIdx = i - 1
        local itemSoundNode = self.userWidget_:FindWidget("ItemSoundNode" .. newIdx)
        if nil ~= itemSoundNode then
            local barVolume = itemSoundNode:FindWidget("BarVolume")
            local sliderVolume = itemSoundNode:FindWidget("SliderVolume")
            itemSoundNode.OnAudioVolumeChange:Add(function(inAudioType, inVolume)
                self:OnAudioVolumeChange(inAudioType, inVolume)
            end)
            self.audioSettNodes_[itemSoundNode.InAudioType] = 
            {
                idx = newIdx, audioType = itemSoundNode.InAudioType, 
                soundNode = itemSoundNode, barVolume = barVolume, sliderVolume = sliderVolume
            }
        end

        local audioSetting = self.userWidget_.GameSettingData.AudioSettings:Get(newIdx)
        if nil ~= audioSetting then
            self.audioSettings_[audioSetting.AudioSetType] =
            {
                idx = newIdx, audioType = audioSetting.AudioSetType, 
                audioSetting = audioSetting
            }
        end
    end
    for i = 1, 5 do
        local newIdx = i - 1
        if nil ~= self.audioSettNodes_[newIdx] then
            if nil ~= self.audioSettings_[newIdx] then
                local percent = self.audioSettings_[newIdx].audioSetting.AudioTypeVolume / 100
                self.audioSettNodes_[newIdx].barVolume:SetPercent(percent)
                self.audioSettNodes_[newIdx].sliderVolume:SetValue(percent)
            end
        end
    end
    table.print(self.userWidget_.GameSettingData)
end

--[[ 构造回调(CWUserWidget) ]]--
function CGameSettingMediator.OnConstruct(self)
    print(">> CGameSettingMediator.OnConstruct, enter.")
end

--[[ 销毁回调(CWUserWidget) ]]--
function CGameSettingMediator.OnDestruct(self)
    print(">> CGameSettingMediator.OnDestruct, enter.")
    self:OnDestroyed()
end

--[[ 销毁回调 ]]--
function CGameSettingMediator.OnDestroyed(self)
    print(">> CGameSettingMediator.OnDestroyed, enter.")
    if nil == self.userWidget_ then
        print(">> CGameSettingMediator.OnDestroyed, already destroy!")
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
    self.btnClose_.OnClicked:Clear()
    self.btnReset_.OnClicked:Clear()
    self.btnApply_.OnClicked:Clear()
    self.btnRefresh_.OnClicked:Clear()
    self.btnVolume_.OnClicked:Clear()
    self.cBWinMode_.OnCheckStateChanged:Clear()
    for i, elem in ipairs(self.selectedList_) do
        if nil ~= elem.btn then
            elem.btn.OnClicked:Clear()
            elem.btn.OnHovered:Clear()
        end
    end
    for i, elem in ipairs(self.itemGamePlayList_) do
        if nil ~= elem.checkBox then
            elem.checkBox.OnCheckStateChanged:Clear()
        end
    end

    -- Destroy Reference
    self.userWidget_.GameSettingSaveData = nil
    self.userWidget_.GameSettingData = nil
    self.btnClose_ = nil
    self.btnReset_ = nil
    self.btnApply_ = nil
    self.btnRefresh_ = nil
    self.trsSwitcher_ = nil
    self.trsCheckBoxGroup_ = nil
    self.txtWinMode_ = nil
    self.cBWinMode_ = nil

    -- Destroy List
    self.selectedList_ = nil
    self.userWidget_ = nil
    self.show_ = false
end

-------------------------------------------- Get/Set ------------------------------------
function CGameSettingMediator.GetUserWidget(self)
    return self.userWidget_
end

function CGameSettingMediator.IsValidUserWidget(self)
    return self.userWidget_ ~= nil
end

-------------------------------------------- Function ------------------------------------
function CGameSettingMediator.SwitchPage(self, pageIdx)
    --print(">> CGameSettingMediator.SwitchPage:" .. pageIdx)
    self.trsSwitcher_:SetActiveWidgetIndex(pageIdx)
end

function CGameSettingMediator.ResetDefaultSetting(self, pageIdx)
    local gameSettingCDO = CWGameSettingSG.GetClassDefaultObj()
    if nil == self.userWidget_.GameSettingData or nil == gameSettingCDO then
        error(">> CGameSettingMediator.ResetDefaultSetting, gameSettingData_/gameSettingCDO is nil!")
        return
    end

    -- Reset Idx Page
    if 0 == pageIdx then
        self.userWidget_.GameSettingData.Resolution = gameSettingCDO.Resolution
        self.userWidget_.GameSettingData.bWindowMode = gameSettingCDO.bWindowMode
    elseif 1 == pageIdx then
        self.userWidget_.GameSettingData.AudioSettings = gameSettingCDO.AudioSettings
    elseif 2 == pageIdx then
        self.userWidget_.GameSettingData.EnablePawnUIMode = gameSettingCDO.EnablePawnUIMode
    else
        error(">> CGameSettingMediator.ResetDefaultSetting, error pageIdx:".. pageIdx)
    end
end

function CGameSettingMediator.ApplyGameSetting(self)
    -- setting sound audio
    for i = 1, 5 do
        local newIdx = i - 1
        local audioSettingData = self.audioSettings_[newIdx]
        if nil ~= audioSettingData then
            local audioType = audioSettingData.audioSetting.AudioSetType
            local audioVolume = audioSettingData.audioSetting.AudioTypeVolume
            CWGameSettingSG.SetAudioVolume(self.userWidget_.GameSettingData, audioType, audioVolume)
        end
    end

    if nil ~= self.userWidget_.GameSettingData then
        CWGameSettingSG.CopyProperty(self.userWidget_.GameSettingSaveData, self.userWidget_.GameSettingData)
    end
    CWGameSettingSG.SaveGameSetData(self.userWidget_.GameSettingSaveData, "SG_GameSetting", 0)
end

function CGameSettingMediator.ResetOriginalSetting(self, bNotifyBlueprint)
    CWGameSettingSG.CopyProperty(self.userWidget_.GameSettingData, self.userWidget_.GameSettingSaveData)
    if bNotifyBlueprint then
        self.userWidget_:OnCommUpdateSetting(false)
    end
end

-------------------------------------------- Callable ------------------------------------
function CGameSettingMediator.OnClickedBtnClose(self)
    --self.userWidget_:DestroyWidget()
    if not CWGameSettingSG.CompareProperty(self.userWidget_.GameSettingData, self.userWidget_.GameSettingSaveData) then
        g_Facade:SendNotification(NotifierEnum.CLOSE_GAMESETTING)
        return
    end

    -- 打开确认界面
    if not g_UIManager:HasMediatorOpenUI(MediatorEnum.COMM_CONFIRM) then
        g_Facade:SendNotification(NotifierEnum.OPEN_COMMCONFIRM, 
        {
            contentKey = "UI_GameSetting",
            onOkClick = function()
                self:ApplyGameSetting()
                g_Facade:SendNotification(NotifierEnum.CLOSE_GAMESETTING)
            end,
            onCancelClick = function()
                self:ResetOriginalSetting(true)
                g_Facade:SendNotification(NotifierEnum.CLOSE_GAMESETTING)
            end
        })
    end
end

function CGameSettingMediator.OnClickedBtnReset(self)
    self.userWidget_:OnCommUpdateSetting(true)
end

function CGameSettingMediator.OnClickedBtnApply(self)
    self:ApplyGameSetting()
end

function CGameSettingMediator.OnClickedBtnRefresh(self)
    --[[local localPC = self.userWidget_:GetLocalPC()
    if nil ~= localPC then
        localPC:RefreshLevelInClient()
    end
    self.userWidget_:RefreshLevel()]]--
    -- PS: 脑壳晕-Lua调用C++中ServerFunc,执行在Client!!!
end

function CGameSettingMediator.OnClickedBtnVolume(self)
    self.userWidget_:OnCheckAudioTest()
end

function CGameSettingMediator.OnCheckStateChangedWinMode(self, bIsChecked)
    local newTxt = bIsChecked and "WINDOWS" or "FULL SCREEN"
    self.txtWinMode_:SetText(newTxt)
end

function CGameSettingMediator.OnStateChangedCheckBoxGroup(self, inCheckBox, inChangeArray)
    for i, elem in ipairs(self.itemGamePlayList_) do
        if nil ~= elem.checkBox and nil ~= elem.txtTips then
            local newTxt = (inCheckBox == elem.checkBox) and "ON" or "OFF"
            --local newTxt = inCheckBox:IsChecked() and "ON" or "OFF"
            elem.txtTips:SetText(newTxt)
        end
    end
end

function CGameSettingMediator.OnCheckStateChangedGamePlay(self, bIsChecked, idx)
    local checkItem = self.itemGamePlayList_[idx]
    if nil ~= checkItem and nil ~= checkItem.txtTips then
        local newTxt = bIsChecked and "ON" or "OFF"
        checkItem.txtTips:SetText(newTxt)
    else
        error(">> CGameSettingMediator.OnCheckStateChangedGamePlay, checkItem is nil! bIsChecked/idx:".. bIsChecked.. idx)
    end
end

function CGameSettingMediator.OnHoveredBtnSwitch(self, pageIdx)
    --print(">> CGameSettingMediator.OnHoveredBtnSwitch:" .. pageIdx)
    for i, elem in ipairs(self.selectedList_) do
        if nil ~= elem.img then
            if pageIdx == elem.idx then
                elem.img:SetColorAndOpacity(FLinearColor.Red)
            else
                elem.img:SetColorAndOpacity(FLinearColor.White)
            end
        end
    end
end

function CGameSettingMediator.OnAudioVolumeChange(self, inAudioType, inVolume)
    if nil ~= self.audioSettings_[inAudioType] then
        self.audioSettings_[inAudioType].audioSetting.AudioTypeVolume = inVolume

        local AudioVideoMgr = CWAudioVideoMgr.GetAVMgr(self.userWidget_)
        if nil ~= AudioVideoMgr then
            AudioVideoMgr:SetAkAudioVolume(inAudioType, inVolume, 0)
        else
            error(">> CGameSettingMediator.OnAudioVolumeChange, AudioVideoMgr is nil!")
        end
    end
end

return CGameSettingMediator