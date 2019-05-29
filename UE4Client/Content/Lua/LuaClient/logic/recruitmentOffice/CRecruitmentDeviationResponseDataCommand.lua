local CRecruitmentDeviationResponseDataCommand = class("CRecruitmentDeviationResponseDataCommand", CCommand)

function CRecruitmentDeviationResponseDataCommand.ctor(self)
    CCommand.ctor(self)
end

function CRecruitmentDeviationResponseDataCommand.Execute(self, notification)
    print("CRecruitmentDeviationResponseDataCommand.Execute...")

    self.recruitmentOfficeProxy_ = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE)
    self.recruitmentOfficeMediator_ = g_Facade:RetrieveMediator(MediatorEnum.RECRUITMENT_OFFICE)

    self:ToSetData(notification)
end

function CRecruitmentDeviationResponseDataCommand.ToSetData(self, notification)
    -- local body = notification:GetBody()
    -- local t = pb.decode("KFMsg.MsgLoginAck", body["Data"])
    -- local playerId = t["playerid"]

    -- local loginProxy = g_Facade:RetrieveProxy(ProxyEnum.LOGIN)
    -- loginProxy:SetPlayerId(playerId)

           local deviationItem = CRecruitmentDeviationItem.New(1, 1, 1)
           self.recruitmentOfficeProxy_:AddDeviation(deviationItem)
                 deviationItem = CRecruitmentDeviationItem.New(2, 3, 1)  
           self.recruitmentOfficeProxy_:AddDeviation(deviationItem)
                 deviationItem = CRecruitmentDeviationItem.New(3, 1, 1)  
           self.recruitmentOfficeProxy_:AddDeviation(deviationItem)
                 deviationItem = CRecruitmentDeviationItem.New(4, 0, 0)  
           self.recruitmentOfficeProxy_:AddDeviation(deviationItem) 
           
    self.recruitmentOfficeMediator_.hasNewDeviationData_ = true

    if self.recruitmentOfficeMediator_.needRefreshDeviation_ == true then

        --g_Facade:SendNotification(NotifierEnum.RECRUITMENT_SHOP_REFRESH_UI)
        
    end

end

return CRecruitmentDeviationResponseDataCommand