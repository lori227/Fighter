local CRoleListRefreshUICommand = class("CRoleListRefreshUICommand", CCommand)

function CRoleListRefreshUICommand.ctor(self)
	CCommand.ctor(self)
end

function CRoleListRefreshUICommand.Execute(self, notification)
	print("CRoleListRefreshUICommand.Execute...")
    
    self.roleListProxy_ = g_Facade:RetrieveProxy(ProxyEnum.ROLE_LIST)
	self.roleListMediator_ = CRoleListMediator:Get()

	if self.roleListMediator_.hasNewRoleData_ == true then
		self:RefreshUI()
		self.roleListMediator_.hasNewRoleData_ = false
	else
		self:OpenUI()
	end
end

function CRoleListRefreshUICommand.RefreshUI(self)
	--复用
	if #self.roleListMediator_.roleItemList_ == 0 then
		self:CreateUI(1)
	-- else
	-- 	self:ReSetUI()
	end	
end

function CRoleListRefreshUICommand.OpenUI(self)

end

function CRoleListRefreshUICommand.CreateUI(self, num) 
	--获取容器
	local roleListMediator = CRoleListMediator:Get()
	local roleListUI = roleListMediator.userWidget_:FindWidget('RoleList')
	if self.roleListMediator_.roleListUI_ == nil then
		self.roleListMediator_.roleListUI_ = roleListMediator.userWidget_:FindWidget('RoleList')
	end
	local roleListUI = self.roleListMediator_.roleList_
	--载入Item
	for k,v in pairs(self.roleListProxy_.roleItemDataList_) do
	     	roleListMediator:AddItem(CRoleListRoleItem, v)
    end
end


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

return CRoleListRefreshUICommand