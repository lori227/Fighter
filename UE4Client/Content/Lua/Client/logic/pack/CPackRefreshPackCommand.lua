local CPackRefreshPackCommand = class("CPackRefreshPackCommand", CCommand)

function CPackRefreshPackCommand.ctor(self)
	CCommand.ctor(self)
end


function CPackRefreshPackCommand.Execute(self, notification)
	print("CPackRefreshPackCommand.Execute...")
	
	self:RefreshPack()
end

function CPackRefreshPackCommand.RefreshPack(self)
	local packProxy = g_Facade:RetrieveProxy(ProxyEnum.PACK)

	for k,v in pairs(packProxy.goodsList_) do
		packProxy.gridsList_[k]:SetGoodObj(v)
		packProxy.gridsList_[k]:SetGoodNum(v:GetGoodNum())
	end

	for k,v in pairs(packProxy.gridsList_) do
		local goodobj = v:GetGoodObj()
		if goodobj ~= nil then
			local gridobj = v:GetGridObj()		
			gridobj:FindWidget('TextName'):SetText(goodobj:GetGoodName())
			gridobj:FindWidget('TextNum'):SetText(goodobj:GetGoodNum())
		end
	end
end

return CPackRefreshPackCommand
