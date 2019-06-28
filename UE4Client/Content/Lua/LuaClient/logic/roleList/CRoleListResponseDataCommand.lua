local CRoleListResponseDataCommand = class("CRoleListResponseDataCommand", CCommand)

function CRoleListResponseDataCommand.ctor(self)
	  CCommand.ctor(self)
end

function CRoleListResponseDataCommand.Execute(self, notification)
	  print("CRoleListResponseDataCommand.Execute...")

    self.roleListProxy_ = g_Facade:RetrieveProxy(ProxyEnum.ROLE_LIST)
    self.roleListMediator_ = CRoleListMediator:Get()

	  self:SetData(notification)
end

function CRoleListResponseDataCommand.SetData(self, notification)

    local roleItemData = CRoleListRoleItemData.New(1, 99)
    self.roleListProxy_:AddRoleItemData(roleItemData)
          roleItemData = CRoleListRoleItemData.New(2, 98)
    self.roleListProxy_:AddRoleItemData(roleItemData)
          roleItemData = CRoleListRoleItemData.New(3, 97)
    self.roleListProxy_:AddRoleItemData(roleItemData)
          roleItemData = CRoleListRoleItemData.New(4, 96)
    self.roleListProxy_:AddRoleItemData(roleItemData)
          roleItemData = CRoleListRoleItemData.New(5, 95)
    self.roleListProxy_:AddRoleItemData(roleItemData)
          roleItemData = CRoleListRoleItemData.New(6, 94)
    self.roleListProxy_:AddRoleItemData(roleItemData)
    
    self.roleListMediator_.hasNewRoleData_ = true
    self.roleListMediator_.needRefreshRoleList_ = true
    
    if self.roleListMediator_.needRefreshRoleList_ == true then

        g_Facade:SendNotification(NotifierEnum.ROLE_LIST_REFRESH_UI)
        
    end


end

return CRoleListResponseDataCommand