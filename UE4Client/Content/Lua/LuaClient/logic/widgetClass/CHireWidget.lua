
	-- local hireWidget = CHireWidget.New()
	-- 设置时间和成功回调函数
	-- hireWidget:SetTimeFunction(2.5, function() print("success") end)
	-- 设置鼠标按下
	-- hireWidget:OnMouseButtonDown(uiwidget, function() print("down") end)
	-- 设置鼠标抬起
	-- hireWidget:OnMouseButtonUp(uiwidget, function() print("up") end)
	-- 加到父节点
	-- hireWidget:AddToParent(parentwidget)
	-- 从父节点移走
	-- hireWidget:RemoveFromParent()
	-- 显示
	-- hireWidget:Show()
	-- 隐藏
	-- hireWidget:Hide()


local CHireWidget = class('CHireWidget')

function CHireWidget.ctor(self)
	self.hireWidget_ = slua.loadUI('/Game/Blueprints/UI/Widget/RecruitmentOffice/WB_HireWidget.WB_HireWidget')
	self.downTime_ = 0
	self.leftMouseButtonDown_ = false
	self.time_ = 0
	self.successFunc_ = nil

	self:Init()
end

function CHireWidget.Init(self)
	if self.hireWidget_ ~= nil then
		self.hireText_ =  self.hireWidget_:FindWidget('HireText')
		self.hireImage_ =  self.hireWidget_:FindWidget('HireImage')
		self.hireWidget_:SetVisibility(4)
	else
		error("WB_HireWidget is empty")
	end
end

function CHireWidget.OnMouseButtonDown(self, widget, downFunc)
	if widget ~= nil then
		widget.ShopItemOnMouseButtonDown:Add(function (geometry, mouseEvent)
		    self.leftMouseButtonDown_ = true
		    self.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0)
		    if downFunc ~= nil then
				downFunc() 
			end	
	    	g_TimeCtrl:AddTimer(self.TimeFunction, 0.01, 0, self)
		end)
	else
		error("Widget is not allowed to be empty")
	end
end

function CHireWidget.OnMouseButtonUp(self, widget, upFunc)
	if Widget ~= nil then
		widget.ShopItemOnMouseButtonUp:Add(function (geometry, mouseEvent)
			self.leftMouseButtonDown_ = false
			self.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0) 
			if upFunc ~= nil then
				upFunc()
			end
		end)
	else
		error("Widget is not allowed to be empty")
	end
end

function CHireWidget.SetTimeFunction(self, time, successFunc)
	if	time <= 0 then
		self.time_  = 0
	else
		self.time_ = time
	end
	self.successFunc_ = successFunc
end

function CHireWidget.Show(self)
	self.hireWidget_:SetVisibility(4)
end

function CHireWidget.Hide(self)
	self.hireWidget_:SetVisibility(2)
end

function CHireWidget.AddToParent(self, parent)
	parent:AddChild(self.hireWidget_)
end

function CHireWidget.RemoveFromParent(self)
	self.hireWidget_:RemoveFromParent()
end

function CHireWidget.TimeFunction(deltatime, timeId, myTable)
	if myTable.leftMouseButtonDown_ then
        myTable.downTime_ = myTable.downTime_ + deltatime
        local time =  myTable.downTime_/myTable.time_
        myTable.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', time) 
        if time >= 1 then
        	myTable.leftMouseButtonDown_ = false
            myTable.hireImage_:GetDynamicMaterial():SetScalarParameterValue('Progress', 0)                     
            myTable.downTime_ = 0  
            g_TimeCtrl:DelTimer(timeId)
            if myTable.successFunc_ ~= nil then
            	myTable.successFunc_()
            end
        end 
    else
        myTable.downTime_ = 0
        g_TimeCtrl:DelTimer(timeId)
    end  
end

return CHireWidget