local CProxy = class("CProxy", CNotifier)

CProxy.NAME = "Proxy"
function CProxy.ctor(self, proxyName, data)
	if not proxyName then 
		proxyName = CProxy.NAME 
	end

	self.proxyName_ = proxyName
	self.data_ = data
end


function CProxy.OnRegister(self)
end


function CProxy.OnRemove(self)
end


function CProxy.GetProxyName(self)
	return self.proxyName_
end


function CProxy.GetData(self)
	return self.data_
end


function CProxy.SetData(self, value)
	--local oldData = self.data_
	self.data_ = value
	--self:SendNotification(..., self.data_, oldData)
end


return CProxy
