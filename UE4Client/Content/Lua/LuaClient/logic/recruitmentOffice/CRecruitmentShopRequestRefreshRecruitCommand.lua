local CRecruitmentShopRequestRefreshRecruitCommand = class("CRecruitmentShopRequestRefreshRecruitCommand", CCommand)

function CRecruitmentShopRequestRefreshRecruitCommand.ctor(self)
	CCommand.ctor(self)
end

function CRecruitmentShopRequestRefreshRecruitCommand.Execute(self, notification)
	print("CRecruitmentShopRequestRefreshRecruitCommand.Execute...")

	self:RefreshRecruit(notification)
end

function CRecruitmentShopRequestRefreshRecruitCommand.RefreshRecruit(self, notification)
	if g_Facade:RetrieveProxy(ProxyEnum.RECRUITMENT_OFFICE):GetRecruitCount() > 0 then
		local MsgRecruitmentShopReqData = 
		{
			type = RefreshRecruitEnum.RefreshByCount
		}
		--table.print(MsgRecruitmentShopReqData)
		local str = pbc.encode("KFMsg.MsgRefreshRecruitReq", MsgRecruitmentShopReqData)
		g_Network:Send(ProtobufEnum.MSG_REFRESH_RECRUIT_REQ, str, #str)
	end
end

return CRecruitmentShopRequestRefreshRecruitCommand