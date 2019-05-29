
--[[
	UE4:UserWidget对应控制脚本
]]--

local CUIPanleBase = class("CUIPanleBase", CObjectBase)

--[[ 构造 ]]--
function CUIPanleBase.ctor(self)
	CObjectBase.ctor(self)
end

--[[ 初始化回调 ]]--
function CUIPanleBase.Init(self, inUserWidget, bUseMask)
	asset(nil ~= inUserWidget)

    self.userWidget_ = inUserWidget
    self.bUseMask_ = bUseMask or false
	self.trsMask_ = self.userWidget_:FindWidget("TrsMask")
	self:SetMaskVisible(self.bUseMask_)

	if nil ~= self.userWidget_.OnBeginDestroy then
		self.userWidget_.OnBeginDestroy:Add(function()
	        if self.OnDestroyed then self:OnDestroyed() end
	    end)
	end

	CObjectBase.Init(self)
end

--[[ 初始化回调 ]]--
function CUIPanleBase.OnInit(self)
	CObjectBase.OnInit(self)

    if self._OnInitReference then self:_OnInitReference() end
    if self._OnInitListener then self:_OnInitListener() end
end

--[[ 销毁回调 ]]--
function CUIPanleBase.OnDestroyed(self)
	CObjectBase.OnDestroyed(self)
	
    self.userWidget_ = nil
    self.bUseMask_ = false
    self.trsMask_ = nil

    if self._OnDestroyListener then self:_OnDestroyListener() end
    if self._OnDestroyReference then self:_OnDestroyReference() end
end


--[[ 播放动画 ]]--
function CUIPanleBase.PlayAnimationByName(self, inAnimName)

end

--[[ 获取UserWidget对象 ]]--
function CUIPanleBase.GetUserWidget(self)
    return self.userWidget_
end

--[[ 设置UserWidget可见性 ]]--
function CUIPanleBase.SetPanelVisible(self, bNewVisible)
	-- TODO: Set Position?
	if nil ~= self.userWidget_ then
		if bNewVisible then
			UIUtil.SetWidgetVisibility(self.userWidget_, ESlateVisibility.SelfHitTestInvisible)
		else
			UIUtil.SetWidgetVisibility(self.userWidget_, ESlateVisibility.Collapsed)
		end
	end
end

--[[ 获取遮罩大小 ]]--
local maskSize_ = nil
function CUIPanleBase.GetMaskSize(self)
    if nil ~= maskSize_ then
        return maskSize_
    end

    maskSize_ = FVector2D.New(2500, 2500)
    return maskSize_
end

--[[ 获取Mask对象 ]]--
function CUIPanleBase.GetMask(self)
    return self.trsMask_
end

--[[ 设置Mask可见性 ]]--
function CUIPanleBase.SetMaskVisible(self, bNewVisible)
	if nil ~= self.trsMask_ then
		if bNewVisible then
			UIUtil.SetWidgetVisibility(self.trsMask_, ESlateVisibility.SelfHitTestInvisible)
		else
			UIUtil.SetWidgetVisibility(self.trsMask_, ESlateVisibility.Collapsed)
		end
	end
end

--[[ 显示金钱信息 ]]
function CUIPanleBase.ShowCoinBar(self, bShowBar)
	-- TODO: New CoinBar UserWidget
end

return CUIPanleBase
