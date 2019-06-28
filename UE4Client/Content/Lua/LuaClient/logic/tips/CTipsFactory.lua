local CTipsFactory = class("CTipsFactory")

function CTipsFactory.ctor(self)
    self.tipsModel_ = {}
    self.isEnter_ = false 
end

function CTipsFactory.ShowOrHideTips(self, tipsEnum, data)
    local tipsWidget = self:CreateTips(tipsEnum, data)
    if not self.isEnter_ then
        self.isEnter_ = true
        g_TimeCtrl:AddTimer(self.FollowMouseDisplay, 0.01, 0, tipsWidget)
        tipsWidget.Tips:SetVisibility(4)
    else
        self.isEnter_ = false
        tipsWidget.Tips:SetVisibility(1)
    end
end

function CTipsFactory.CreateTips(self, tipsEnum, data)
    local tipsModel = self:GetTipsModel(tipsEnum)
    local tipsWidget = tipsModel:CreateTips(data)
    return tipsWidget
end

--获取Tips模板
function CTipsFactory.GetTipsModel(self, tipsEnum)
    if self.tipsModel_[tipsEnum] == nil then
        self:AddTipsModel(tipsEnum)
    end    
    return self.tipsModel_[tipsEnum]
end

--加载Tips模板
function CTipsFactory.AddTipsModel(self, tipsEnum)
    if tipsEnum == TipsEnum.EQUIPMENT then
        self.tipsModel_[tipsEnum] = CEquipmentTips.New()
    elseif tipsEnum == TipsEnum.SKILL then
        self.tipsModel_[tipsEnum] = CSkillTips.New()
    elseif tipsEnum == TipsEnum.BUFF then
        self.tipsModel_[tipsEnum] = CBuffTips.New()
    elseif tipsEnum == TipsEnum.EXPLAIN then
        self.tipsModel_[tipsEnum] = CExplainTips.New()
    end
end

--跟随鼠标显示
function CTipsFactory.FollowMouseDisplay(deltatime, timeId, tipsWidget)
    if g_TipsFactory.isEnter_ then
        local v2 = WidgetLayoutLibrary.GetMousePositionOnViewport(tipsWidget)
        v2.X = v2.X + 16 
        v2.Y = v2.Y + 32 
        tipsWidget.Tips.Slot:SetPosition(v2)
        --g_TipsFactory:SelfAdaption(tipsWidget)
    else
        g_TimeCtrl:DelTimer(timeId)
    end
end

--自适应
function CTipsFactory.SelfAdaption(self, tipsWidget)
    local v2 = WidgetLayoutLibrary.GetViewportSize(tipsWidget)
    --print(v2.X)
    print(v2.Y)
    local x = v2.X/1920
    local y = v2.Y/1080

    local v2_ = tipsWidget.Background.Slot:GetSize()
    v2_.X = v2_.X * x
    v2_.Y = v2_.Y * y
    -- print(v2_.X)
    -- print(v2_.Y)

    local tipsv2 = tipsWidget.Tips.Slot:GetPosition()
    --print(tipsv2.X)
    --print(tipsv2.Y)
    --tipsv2 = tipsv2 + v2_
    tipsv2.X =  tipsv2.X * x 
    tipsv2.Y =  (tipsv2.Y - 12.5) * y
    --print(tipsv2.X + v2_.X)
    print(tipsv2.Y + v2_.Y)
    v2 = WidgetLayoutLibrary.GetMousePositionOnViewport(tipsWidget)
    --print(v2.X + 16 + 12.5)
    --print((v2.Y + 32 + 12.5)*y)
end

function CTipsFactory.RemoveAllTips(self)
    for k, v in pairs(self.tipsModel_ ) do 
        v:RemoveTips()
        self.tipsModel_[k] = nil
    end
end
    
return CTipsFactory