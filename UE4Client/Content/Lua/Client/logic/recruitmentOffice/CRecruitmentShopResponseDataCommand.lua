local CRecruitmentShopResponseDataCommand = class("CRecruitmentShopResponseDataCommand", CCommand)

function CRecruitmentShopResponseDataCommand.ctor(self)
	  CCommand.ctor(self)
end

function CRecruitmentShopResponseDataCommand.Execute(self, notification)
	  print("CRecruitmentShopResponseDataCommand.Execute...")

    self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
    self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

	  self:ToSetData(notification)
end

function CRecruitmentShopResponseDataCommand.ToSetData(self, notification)
    -- local body = notification:GetBody()
    -- local t = pb.decode("KFMsg.MsgLoginAck", body["Data"])
    -- local playerId = t["playerid"]

    -- local loginProxy = g_Facade:RetrieveProxy(ProxyEnum.LOGIN)
    -- loginProxy:SetPlayerId(playerId)

          local shopItem = CRecruitmentShopItem.New(1, 999999, 999999, 999999)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)
                  shopItem = CRecruitmentShopItem.New(2, 888888, 888888, 888888)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)
                  shopItem = CRecruitmentShopItem.New(3, 777777, 777777, 777777)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)
                  shopItem = CRecruitmentShopItem.New(4, 666666, 666666, 666666)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)
                  shopItem = CRecruitmentShopItem.New(5, 555555, 555555, 555555)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)
                  shopItem = CRecruitmentShopItem.New(6, 0, 0, 0)
          self.recruitmentOfficeProxy_:AddShopItem(shopItem)

    self.recruitmentOfficeMediator_.hasNewShopData_ = true

    if self.recruitmentOfficeMediator_.needRefreshShop_ == true then

        g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_REFRESH_UI)
        
    end

end

return CRecruitmentShopResponseDataCommand