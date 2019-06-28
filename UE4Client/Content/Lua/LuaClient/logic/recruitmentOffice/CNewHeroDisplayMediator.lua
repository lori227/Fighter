local CNewHeroDisplayMediator = class("CNewHeroDisplayMediator", CMediator)

function CNewHeroDisplayMediator.ctor(self, name)
    CMediator.ctor(self, name)

end

function CNewHeroDisplayMediator.OnInit(self, ...)
    print("CNewHeroDisplayMediator -->OnInit")
    CMediator.OnInit(self, ...)

end

function CNewHeroDisplayMediator.OnDestroyed(self)
    print("CNewHeroDisplayMediator -->OnDestroyed")
 
    CMediator.OnDestroyed(self)
end


function CNewHeroDisplayMediator.OnRegisterCommand(self)
    CMediator.OnRegisterCommand(self)
    print("CNewHeroDisplayMediator -->OnRegisterCommand")
    -------------------------------------注册Commond命令------------------------------------------------
    -------------------------------------注册Commond命令------------------------------------------------  
end


function CNewHeroDisplayMediator.OnUnregisterCommand(self)
    print("CNewHeroDisplayMediator -->OnUnregisterCommand")
    -------------------------------------移除注册Command命令-------------------------------------------------
    -------------------------------------移除注册Command命令-------------------------------------------------
    CMediator.OnUnregisterCommand(self)
end

function CNewHeroDisplayMediator.OnCreateUI(self)
    CMediator.OnCreateUI(self)
    print("CNewHeroDisplayMediator -->OnCreateUI")

    self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_NewHero.WB_NewHero')

    self.userWidget_:FindWidget('PassBtn').OnClicked:Add(function ()
        CNewHeroDisplayMediator:Close()
    end)
end

function CNewHeroDisplayMediator.OnRefreshUI(self)
    local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
    local newHeroShowData = recruitmentOfficeProxy:GetNewHeroShowData()
    if newHeroShowData then
        self.userWidget_:FindWidget('RaceCareerText'):SetText(g_UITextCfg[g_RecruitmentOfficeConfig:GetRaceNameById(newHeroShowData.race)].Des
                                                        .. " + " .. g_UITextCfg[g_RecruitmentOfficeConfig:GetProfessionNameById(newHeroShowData.profession)].Des)
        self.userWidget_:FindWidget('NameText'):SetText(newHeroShowData.name)
        recruitmentOfficeProxy:RemoveNewHeroShowData()
    end
end

function CNewHeroDisplayMediator.OnDestroyedUI(self)
    print("CNewHeroDisplayMediator -->OnDestroyedUI")

    CMediator.OnDestroyedUI(self)
end

function CNewHeroDisplayMediator.OnShow(self)     

    self:OnRefreshUI()

    self:AddToViewport(UIViewZOrderEnum.HIGH)
end

function CNewHeroDisplayMediator.OnClose(self)

    self:RemoveFromViewport()
end

function CNewHeroDisplayMediator.ListNotificationInterests(self)
    return {}
end

function CNewHeroDisplayMediator.HandleNotification(self, notification)
    print("CNewHeroDisplayMediator.HandleNotification...")
end

return CNewHeroDisplayMediator 