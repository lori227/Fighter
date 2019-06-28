local CModel = class("CModel")


function CModel.ctor(self)
	self.proxyMap_ = {}
end


function CModel.RegisterProxy(self, proxy)
	if proxy == nil then
		error("CModel.RegisterProxy, proxy:", proxy)
		return
	end

	self.proxyMap_[proxy:GetProxyName()] = proxy
	proxy:OnRegister()
end


function CModel.RetrieveProxy(self, proxyName)
	return self.proxyMap_[proxyName]
end


function CModel.GetProxy(self, proxyName)
	return self.proxyMap_[proxyName]
end


function CModel.HasProxy(self, proxyName)
	return self.proxyMap_[proxyName] ~= nil
end


function CModel.RemoveProxy(self, proxyName)
	if proxyName == nil or proxyName == "" then
		error("CModel.RemoveProxy, proxyName:", proxyName)
		return
	end

	local proxy = nil

	if self.proxyMap_[proxyName] then
		proxy = self:RetrieveProxy(proxyName)
		self.proxyMap_[proxyName] = nil
	end

	if proxy then
 		proxy:OnRemove() 
	end
	return proxy
end


return CModel