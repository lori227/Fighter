local CDeviationItem = class("CDeviationItem", CUIItemBase)

function CDeviationItem.ctor(self, id)
	CUIItemBase.ctor(self, id)
	self.configData_ = nil
	self.lock_ = nil	
	self.nilButton_ = nil
	self.buttonList_ = {}
end


function CDeviationItem.OnInit(self, data)
	CUIItemBase.OnInit(self)
	self.configData_ = data
end

function CDeviationItem.OnCreateUI(self)
	CUIItemBase.OnCreateUI(self)

    if table.count(self.configData_.ChildTypes) + 1 <= 4 then
        self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_DeviationItem_1.WB_DeviationItem_1')
    else
        self.userWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_DeviationItem_2.WB_DeviationItem_2')
    end
    if self.userWidget_ ~= nil and self.configData_ ~= nil then

		self.lock_ = self.userWidget_:FindWidget("Lock")
		self.userWidget_:FindWidget("LogoText"):SetText(g_UITextCfg[self.configData_.TypeName].Des)
		self.userWidget_:FindWidget("LockText"):SetText(g_UITextCfg["RECRUITMENT_CHARACTER_TENDENCY_LOCK"].Des)
		self.userWidget_:FindWidget("TipsText"):SetText(g_UITextCfg["RECRUITMENT_CHARACTER_TENDENCY_LOCK_TIPS"].Des)

		self.userWidget_:FindWidget("Text_0"):SetText(g_UITextCfg[self.configData_.TypeName .. "_NONE"].Des)
		self.nilButton_ = self.userWidget_:FindWidget("Button_0")
		self.nilButton_:SetVisibility(0)
		
		self.nilButton_.OnClicked:Add(function ()
			g_Facade:SendNotification(NotifierEnum.DEVIATION_REQUEST_REMOVE_DATA, self.configData_.ChildTypes)
		end)

		for k, v in pairs(self.configData_.ChildTypes) do
			local name = "Button_" .. k
			self.buttonList_[v.Id] = self.userWidget_:FindWidget(name)
			self.buttonList_[v.Id]:SetVisibility(0)
			name = "Text_" .. k
			self.userWidget_:FindWidget(name):SetText(g_UITextCfg[v.Name].Des)

			self.buttonList_[v.Id].OnClicked:Add(function ()
				if g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE):HasDeviationData(v.Id) then
					g_Facade:SendNotification(NotifierEnum.DEVIATION_REQUEST_REMOVE_DATA, v)
				else
					g_Facade:SendNotification(NotifierEnum.DEVIATION_REQUEST_ADD_DATA, v)
				end
			end)		
		end	
	end
	
end

function CDeviationItem.OnRefreshItem(self)
	CUIItemBase.OnRefreshItem(self)

	local recruitmentOfficeProxy = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	local hasData = 0  
	for k, v in pairs(self.configData_.ChildTypes) do
		if recruitmentOfficeProxy:HasDeviationData(v.Id) then
			hasData = hasData + 1
			self.buttonList_[v.Id]:SetBackgroundColor(CDeviationMediator:Get().green_)
		else
			self.buttonList_[v.Id]:SetBackgroundColor(CDeviationMediator:Get().white_)
		end
	end
	if hasData == 0 then
		self.nilButton_:SetBackgroundColor(CDeviationMediator:Get().green_)
	else
		self.nilButton_:SetBackgroundColor(CDeviationMediator:Get().white_)
	end
end

function CDeviationItem.OnDestroyedUI(self)
	CUIItemBase.OnDestroyedUI(self)
end

function CDeviationItem.OnDestroyed(self)
	self.configData_ = nil
	self.lock_ = nil	
	self.nilButton_ = nil
	for k, v in pairs(self.buttonList_) do
		self.buttonList_[k] = nil
	end
	self.buttonList_ = nil
	
    CUIItemBase.OnDestroyed(self)
end

return CDeviationItem
