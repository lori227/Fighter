local CRecruitmentShopRequestRecruitHeroCommand = class("CRecruitmentShopRequestRecruitHeroCommand", CCommand)

function CRecruitmentShopRequestRecruitHeroCommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentShopRequestRecruitHeroCommand.Execute(self, notification)
	print("CRecruitmentShopRequestRecruitHeroCommand.Execute...")

	self:RecruitHero(notification)
end

function CRecruitmentShopRequestRecruitHeroCommand.RecruitHero(self, notification)
	local uuid = notification:GetBody()
	print(uuid .. "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OK！")
	local heroData = g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE):GetRecruitShopHero(uuid)

	if heroData and tonumber(g_Facade:RetrieveProxy(ProxyEnum.MAIN_CAMPSITE):GetMoney()) >= tonumber(heroData.cost.money) then
		local MsgRecruitmentShopReqData = 
		{
			uuid = uuid
		}
		--table.print(MsgRecruitmentShopReqData)
		local str = pbc.encode("KFMsg.MsgRecruitHeroReq", MsgRecruitmentShopReqData)
		g_Network:Send(ProtobufEnum.MSG_RECRUIT_HERO_REQ, str, #str)
	else
		g_Facade:SendNotification(NotifierEnum.RESOURCES_NOT_ENOUGH, "金币不足！")
	end
end

return CRecruitmentShopRequestRecruitHeroCommand