local CRoleInformationResponseDataCommand = class("CRoleInformationResponseDataCommand", CCommand)

function CRoleInformationResponseDataCommand.ctor(self)
	  CCommand.ctor(self)
end

function CRoleInformationResponseDataCommand.Execute(self, notification)
	  print("CRoleInformationResponseDataCommand.Execute...")

    self.roleInformationProxy_ = g_Facade:RetrieveProxy(ProxyEnum.ROLE_INFORMATION)
    self.roleInformationMediator_ = CRoleInformationMediator:Get()

	  self:SetData(notification)
end

function CRoleInformationResponseDataCommand.SetData(self, notification)


    local roleBuffItemData_ = CRoleBuffItemData.New(1, 999)
    self.roleInformationProxy_:AddBuffItemData(roleBuffItemData)
          roleBuffItemData = CRoleBuffItemData.New(2, 998)
    self.roleInformationProxy_:AddBuffItemData(roleBuffItemData)
    
    self.roleMediator_.hasNewBuffData_ = true
    self.roleMediator_.needRefreshBuff_ = true
    
    if self.roleMediator_.needRefreshBuff_ == true then

        g_Facade:SendNotification(NotifierEnum.ROLE_BUFF_REFRESH_UI)
        
    end


end

return CRoleInformationResponseDataCommand