local CTeamManagementMediator = class("CTeamManagementMediator", CMediator)

function CTeamManagementMediator.ctor(self, name)
    CMediator.ctor(self, name)

    self.uiPanel_ = nil
    self.show_ = false
end

function CTeamManagementMediator.OnInit(self)
    print("CTeamManagementMediator -->OnInit")
    CMediator.OnInit(self)
end

function CTeamManagementMediator.OnDestroyed(self)
    print("CTeamManagementMediator -->OnDestroyed")
    
    self.uiPanel_ = nil
    self.show_ = false

    CMediator.Destroy(self)
end



function CTeamManagementMediator.OnRegisterCommand(self)
    print("CTeamManagementMediator -->OnRegisterCommand")
    CMediator.OnRegisterCommand(self)

    -------------------------------------注册Commond命令------------------------------------------------
    --g_Facade:RegisterCommand(NotifierEnum.REQUEST_AUTH_INFO, CServerAuthRequestAuthInfoCommand)
    -------------------------------------注册Commond命令------------------------------------------------
end

function CTeamManagementMediator.OnUnregisterCommand(self)
    print("CTeamManagementMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    --g_Facade:UnregisterCommand(NotifierEnum.REQUEST_AUTH_INFO)
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end


function CTeamManagementMediator.OnCreateUI(self)
    print("CTeamManagementMediator -->OnCreateUI")
    CMediator.OnCreateUI(self)

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/TeamManagement/WB_TeamManagement.WB_TeamManagement')
    self.uiReturnBtn_ = self.userWidget_:FindWidget('ReturnBtn')
    
    self.userWidget_:CreateModel()
   
    local model = self.userWidget_.Model
    local modelSkeletalMesh = model.SkeletalMesh

    local kismetMathLibrary = import("KismetMathLibrary")
    local widgetLayoutLibrary = import("WidgetLayoutLibrary")
    local v2_Start = nil
    local v2_Move = nil
    local v2_Difference = nil
    self.isRotate = false

    local wb_TeamHeroItem = self.userWidget_.WB_TeamHeroItem
    
    wb_TeamHeroItem.TeamHeroItemOnMouseButtonDown:Add(function (geometry, mouseEvent) 
        self.isRotate = true
        v2_Start = widgetLayoutLibrary.GetMousePositionOnViewport(wb_TeamHeroItem)
    end)
    wb_TeamHeroItem.TeamHeroItemOnMouseButtonMove:Add(function (geometry, mouseEvent)
        if self.isRotate == true then
            v2_Move = widgetLayoutLibrary.GetMousePositionOnViewport(wb_TeamHeroItem)
            v2_Difference = v2_Move - v2_Start
            local rotator = kismetMathLibrary.MakeRotator(0, 0, v2_Difference.X)          
            modelSkeletalMesh:K2_AddWorldRotation(rotator * -1 * 0.5, false, nil, false)
            v2_Start = v2_Move    
        end
    end)
    wb_TeamHeroItem.TeamHeroItemOnMouseButtonUp:Add(function (geometry, mouseEvent) 
        self.isRotate = false
    end)
    wb_TeamHeroItem.TeamHeroItemOnMouseButtonLeave:Add(function (mouseEvent) 
        self.isRotate = false
    end)

    -- self.tips = slua.loadUI('/Game/Blueprints/UI/Widget/Comm/WB_ExplainTips.WB_ExplainTips')
    -- self.tips:AddToViewport(5)
    -- self.tips:SetVisibility(1)
    local teamHeroItem = self.userWidget_:FindWidget('WB_TeamHeroItem_6')
    local teamHeroBuffBox = teamHeroItem:FindWidget('HeroBuffBox')
    local headImage = teamHeroItem:FindWidget('HeadImage')
    local weaponTypesImage = teamHeroItem:FindWidget('ArmsTypesImage')
    local armsImage = teamHeroItem:FindWidget('ArmsImage')
    local activeSkillsImage = teamHeroItem:FindWidget('ActiveSkillsImage')
    local exploringSkillsImage = teamHeroItem:FindWidget('ExploringSkillsImage')
    local changeArms = teamHeroItem:FindWidget('ChangeArms')


    weaponTypesImage.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器类型")
    end)

    weaponTypesImage.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器类型")
    end)

    headImage.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "头像内容")
    end)

    headImage.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "头像内容")
    end)


    armsImage.OnHovered:Add(function ()
        --self.isEnter = true
        local data = {}
        data["EquipmentIcon"] = "ArmsLogo"
        data["EquipmentName"] = "风暴巨锤"
        data["EquipmentDescription"] = "        主要目的是增加物理吸血，吸取敌方的生命值或者增加自身血量。当英雄的伤害提高到一定程度上，就要购买吸血刀，做到能抗能打。"
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
        --g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        --self.tips:SetVisibility(4)
        --print("BBBBBBBBBBBBBBBBB")
    end)

    armsImage.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        local data = {}
        data["EquipmentIcon"] = "ArmsLogo"
        data["EquipmentName"] = "风暴巨锤"
        data["EquipmentDescription"] = "        主要目的是增加物理吸血，吸取敌方的生命值或者增加自身血量。当英雄的伤害提高到一定程度上，就要购买吸血刀，做到能抗能打。"
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "武器说明")
    end)

    activeSkillsImage.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.SKILL, "主动技能内容")
    end)

    activeSkillsImage.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.SKILL, "主动技能内容")
    end)

    exploringSkillsImage.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.SKILL, "探索技能内容")
    end)

    exploringSkillsImage.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.SKILL, "探索技能内容")
    end)

    changeArms.OnHovered:Add(function ()
        -- self.isEnter = true
        -- g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
        -- print("AAAAAAAAAAAAAAAAAAAA")
        -- self.tips:SetVisibility(4)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "更换")
    end)

    changeArms.OnUnhovered:Add(function ()
        -- self.isEnter = false
        -- self.tips:SetVisibility(1)
        g_TipsFactory:ShowOrHideTips(TipsEnum.EXPLAIN, "更换")
    end)

    for i=1,5 do
        self.teamHeroBuff = slua.loadUI('/Game/Blueprints/UI/Widget/TeamManagement/WB_TeamHeroBuffItem.WB_TeamHeroBuffItem')
        teamHeroBuffBox:AddChild(self.teamHeroBuff)
        self.teamHeroBuff.TeamHeroBuffOnMouseButtonEnter:Add(function (geometry, mouseEvent)
            --print(teamHeroBuff.Slot:GetPosition())
            --self.isEnter = true
            --v2 = widgetLayoutLibrary.GetMousePositionOnViewport(self.teamHeroBuff)
            -- print(v2.X)
            -- print(v2.Y)
            --tips:FindWidget('Tips'):SetRenderTranslation(v2)
            --self.tips:FindWidget('Tips').Slot:SetPosition(v2)
            --g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
            --self.tips:SetVisibility(4)
            g_TipsFactory:ShowOrHideTips(TipsEnum.BUFF, "Buff内容")

        end)

        self.teamHeroBuff.TeamHeroBuffOnMouseButtonLeave:Add(function (mouseEvent)
            -- self.isEnter = false
            -- self.tips:SetVisibility(1)
            g_TipsFactory:ShowOrHideTips(TipsEnum.BUFF, "Buff内容")
        end)

    end

    local teamHeroItem1 = self.userWidget_:FindWidget('WB_TeamHeroItem')
    local teamHeroBuffBox1 = teamHeroItem1:FindWidget('HeroBuffBox')

    for i=1,5 do
        local teamHeroBuff = slua.loadUI('/Game/Blueprints/UI/Widget/TeamManagement/WB_TeamHeroBuffItem.WB_TeamHeroBuffItem')
        teamHeroBuffBox1:AddChild(teamHeroBuff)
        teamHeroBuff.TeamHeroBuffOnMouseButtonEnter:Add(function (geometry, mouseEvent)
            --print(teamHeroBuff.Slot:GetPosition())
            --self.isEnter = true
            --v2 = widgetLayoutLibrary.GetMousePositionOnViewport(self.teamHeroBuff)
            -- print(v2.X)
            -- print(v2.Y)
            --tips:FindWidget('Tips'):SetRenderTranslation(v2)
            --self.tips:FindWidget('Tips').Slot:SetPosition(v2)
            --g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0)
            -- self.tips:SetVisibility(4)
            g_TipsFactory:ShowOrHideTips(TipsEnum.BUFF, "Buff内容")
        end)

        teamHeroBuff.TeamHeroBuffOnMouseButtonLeave:Add(function (mouseEvent)
            --self.isEnter = false
            -- self.tips:SetVisibility(1)
            g_TipsFactory:ShowOrHideTips(TipsEnum.BUFF, "Buff内容")
        end)

    end
    


    self.uiReturnBtn_.OnClicked:Add(function ()
        self:Hide()
    end)
 end

 function CTeamManagementMediator.OnDestroyedUI(self)
    print("CTeamManagementMediator -->OnDestroyedUI")
    self.userWidget_ = nil

    CMediator.OnDestroyedUI(self)
end

function CTeamManagementMediator.OnShow(self)
    self.show_ = true

    self.userWidget_:PlayAnimation(self.userWidget_.OpenRoleList, 0, 1, 3, 1)

    self:AddToViewport(0)
end

function CTeamManagementMediator.OnClose(self)
    self.show_ = false

    self:RemoveFromViewport()
end

function CTeamManagementMediator.ListNotificationInterests(self)
    return {}
end

function CTeamManagementMediator.HandleNotification(self, notification)
    print("CTeamManagementMediator.HandleNotification...")
end


function CTeamManagementMediator.TimeFunction(deltatime, timeId)
    local teamManagementMediator = g_Facade:RetrieveMediator(MediatorEnum.TEAM_MANAGEMENT)
    if teamManagementMediator.isEnter then
        local widgetLayoutLibrary = import("WidgetLayoutLibrary")
        local v2 = widgetLayoutLibrary.GetMousePositionOnViewport(teamManagementMediator.teamHeroBuff)
        v2.X = v2.X + 16
        v2.Y = v2.Y + 32
        teamManagementMediator.tips:FindWidget('Tips').Slot:SetPosition(v2)
    else
        g_TimeCtrl:DelTimer(timeId)
    end
end

return CTeamManagementMediator