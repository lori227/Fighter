local CRecruitmentDeviationRefreshUICommand = class("CRecruitmentDeviationRefreshUICommand", CCommand)

function CRecruitmentDeviationRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentDeviationRefreshUICommand.Execute(self, notification)
	print("CRecruitmentDeviationRefreshUICommand.Execute...")

	self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
	self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

	self.uiPanel_ = self.recruitmentOfficeMediator_.uiPanel_
	if self.uiPanel_ == nil then
		return
	end

	if self.recruitmentOfficeMediator_.hasNewDeviationData_ == true then
		self:RefreshUI()
		self.recruitmentOfficeMediator_.hasNewDeviationData_ = false
	else
		self:OpenUI()
	end
end

function CRecruitmentDeviationRefreshUICommand.RefreshUI(self)
	--获取右侧需隐藏面板
	local rightPanel = self.uiPanel_:FindWidget('RightPanel')
	--获取显示面板
	local deviationPanel = self.uiPanel_:FindWidget('DeviationPanel')
	--获取容器
	local devList = self.uiPanel_:FindWidget('DevList')
	--获取返回按钮
	local devReturnBtn = self.uiPanel_:FindWidget('DevReturnBtn')
	--绑定容器动画
    self.uiPanel_.DeviationAnimation.OnAnimationStarted:Add(function ()
        self.recruitmentOfficeMediator_:SetTargetVisibility(rightPanel, 1)
        self.recruitmentOfficeMediator_:SetTargetVisibility(deviationPanel, 4)
    end)
    self.uiPanel_.DeviationAnimation.OnAnimationFinished:Add(function ()
    	--反放结束为False
	    if self.uiPanel_:IsAnimationPlayingForward(self.uiPanel_.DeviationAnimation) == false then
	        self.recruitmentOfficeMediator_:SetTargetVisibility(deviationPanel, 1)
        	self.recruitmentOfficeMediator_:SetTargetVisibility(rightPanel, 4)
	    end
    end)
    --绑定按钮事件
    devReturnBtn.OnClicked:Add(function ()
    	self.uiPanel_:PlayAnimation(self.uiPanel_.DeviationAnimation, 0, 1, 1, 1)
    end)
    --加载子项
	for k, v in pairs(self.recruitmentOfficeProxy_.deviationList_) do
		--加载职业偏向子项
		local deviationItemUI = nil
		if #DeviationTextEnum[k] <= 4 then
			deviationItemUI = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_DeviationItem_1.WB_DeviationItem_1')
		else
			deviationItemUI = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_DeviationItem_1.WB_DeviationItem_2')
		end
		--已经解锁
		if v:GetLock() == 1 then
			--设置默认Text
			local logoText = deviationItemUI:FindWidget('LogoText')	
			logoText:SetText(DeviationEnum[v:GetId()])
			-- --设置默认按钮选中模式
			local switch = {
				 [1] = function()
			         deviationItemUI:SetBtnColor_0()
			     end,
			     [2] = function()
			         deviationItemUI:SetBtnColor_1()
			     end,
			     [3] = function()
			         deviationItemUI:SetBtnColor_2()
			     end,
			     [4] = function()
			         deviationItemUI:SetBtnColor_3()
			     end
			 }
			switch[v:GetDeviation()]()
			--绑定按钮事件
			local buttonlist = {}
			-- table.insert(buttonlist, deviationItemUI:FindWidget('Button_0'))			
			-- table.insert(buttonlist, deviationItemUI:FindWidget('Button_1'))
			-- table.insert(buttonlist, deviationItemUI:FindWidget('Button_2'))
			-- table.insert(buttonlist, deviationItemUI:FindWidget('Button_3'))
			table.insert(buttonlist, deviationItemUI.Button_1)			
			table.insert(buttonlist, deviationItemUI.Button_2)
			table.insert(buttonlist, deviationItemUI.Button_3)
			table.insert(buttonlist, deviationItemUI.Button_4)
			--设置初始选中状态和绑定Event
			--self:AddEventToButton(v, buttonlist)

			--绑定按钮事件
			local btn_0 = deviationItemUI:FindWidget('Button_1')
			local btn_1 = deviationItemUI:FindWidget('Button_2')
			local btn_2 = deviationItemUI:FindWidget('Button_3')
			local btn_3 = deviationItemUI:FindWidget('Button_4')
			btn_0.OnClicked:Add(function ()
				deviationItemUI:SetBtnColor_0()
			end)
			btn_1.OnClicked:Add(function ()
				deviationItemUI:SetBtnColor_1()
			end)
			btn_2.OnClicked:Add(function ()
				deviationItemUI:SetBtnColor_2()
			end)
			btn_3.OnClicked:Add(function ()
				deviationItemUI:SetBtnColor_3()
			end)
		--未解锁
		else
			local lock = deviationItemUI:FindWidget('Lock')		
			local lockText = deviationItemUI:FindWidget('LockText')
			self.recruitmentOfficeMediator_:SetTargetVisibility(lock, 4)
			lockText:SetText(DeviationLockTextEnum[v:GetId()])
		end
		--添加缓存
		table.insert(self.recruitmentOfficeMediator_.deviationItemUIList_, deviationItemUI)
		--加入容器
		devList:AddChild(deviationItemUI)
	end
    --播放
    self.uiPanel_:PlayAnimation(self.uiPanel_.DeviationAnimation, 0, 1, 3, 1)  
end

function CRecruitmentDeviationRefreshUICommand.OpenUI(self)
	--播放
	self.uiPanel_:PlayAnimation(self.uiPanel_.DeviationAnimation, 0, 1, 3, 1)
end

function CRecruitmentDeviationRefreshUICommand.AddEventToButton(self, item, buttonlist)
	if buttonlist == nil or item == nil then
		return
	end																
	for k, v in pairs(buttonlist) do
		if k <= #DeviationTextEnum[item:GetId()] then
		 	if k == item:GetDeviation() then
		 		v:SetBackgroundColor(self.uiPanel_.Green)
		 	else
		 		v:SetBackgroundColor(self.uiPanel_.White)
		 	end	
		-- 	v.OnClicked.Add(function ()
		-- 		for k1, v1 in pairs(buttonlist) do
		-- 			if v1 == v then
		-- 				v1:SetBackgroundColor(self.uiPanel_.Green)
		-- 			else
		-- 				v1:SetBackgroundColor(self.uiPanel_.White)
		-- 			end
		-- 		end
		-- 	end)
		 	self.recruitmentOfficeMediator_:SetTargetVisibility(v, 4)
		else
			self.recruitmentOfficeMediator_:SetTargetVisibility(v, 2)			
		end	
	end
end

return CRecruitmentDeviationRefreshUICommand
