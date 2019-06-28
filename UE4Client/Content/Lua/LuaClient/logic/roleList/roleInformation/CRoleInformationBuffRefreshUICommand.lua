local CRoleInformationBuffRefreshUICommand = class("CRoleInformationBuffRefreshUICommand", CCommand)

function CRoleInformationBuffRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRoleInformationBuffRefreshUICommand.Execute(self, notification)
	print("CRoleInformationBuffRefreshUICommand.Execute...")
    
    self.roleInformationProxy_ = g_Facade:RetrieveProxy(ProxyEnum.ROLE_INFORMATION)
	self.roleInformationMediator_ = CRoleInformationMediator:Get()

	if self.roleInformationMediator_.hasNewRoleBuffData_ == true then
		self:RefreshUI()
		self.roleInformationMediator_.hasNewRoleBuffData_ = false
	else
		self:OpenUI()
	end
end

function CRoleInformationBuffRefreshUICommand.RefreshUI(self)
	--复用
	if #self.roleInformationMediator_.roleBuffList_ == 0 then
		self:CreateUI(1)
	-- else
	-- 	self:ReSetUI()
	end	
end

function CRoleInformationBuffRefreshUICommand.OpenUI(self)

end

function CRoleInformationBuffRefreshUICommand.CreateUI(self, num) 
	--获取容器
	local roleInformationMediator = CRoleListMediator:Get()
	local roleBuffUI = roleInformationMediator.userWidget_:FindWidget('BuffBox')
	if self.roleInformationMediator_.roleBuffUI_ == nil then
		self.roleInformationMediator_.roleBuffUI_ = roleInformationMediator.userWidget_:FindWidget('BuffBox')
	end
	local roleBuffUI = self.roleInformationMediator_.roleBuffList_
	--载入Item
	for k,v in pairs(self.roleInformationProxy_.roleBuffDataList_) do
	        local roleBuffItem = CRoleBuffItem.New(v)
	        roleBuffItem:AddItemUIToParent(roleBuffUI)
	     	table.insert(self.roleInformationMediator_.roleBuffList_, roleBuffItem)
	     	-- roleListMediator:AddItem(CRoleListRoleItem)

	end

end


	--鼠标按下
    -- roleItem.RoleItemOnMouseButtonDown:Add(function (geometry, mouseEvent)
  


-- function CRoleListRefreshUICommand.ReSetUI(self)
-- 	for k,v in pairs(self.roleListProxy_.roleItemDataList_) do
-- 		local roleItem = self.roleListMediator_.roleItemList_[k]
-- 		if roleItem ~= nil then
-- 	        roleItem:ShowOrRefreshUI(v)
-- 	    else
-- 	    	self:CreateUI(k)
-- 		end
-- 	end
-- 	if #self.roleListProxy_.roleItemDataList_ < #self.roleListMediator_.roleItemList_ then
-- 		for k,v in pairs(self.roleListMediator_.roleItemList_) do
-- 			if k > #self.roleListProxy_.roleItemDataList_ then
-- 				v:RemoveItemUIFromParent()
-- 			end
-- 		end
-- 	end	
-- end

return CRoleInformationBuffRefreshUICommand