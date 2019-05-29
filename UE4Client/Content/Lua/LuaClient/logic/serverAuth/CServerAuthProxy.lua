local CServerAuthProxy = class("CServerAuthProxy", CProxy)

function CServerAuthProxy.ctor(self, name)
    CProxy.ctor(self, name)

    self.account_ = ""
    self.token_ = ""
	self.accountId_ = nil
	self.serverTable_ = {}
end

function CServerAuthProxy.SetAccount(self, account)
	self.account_ = account
end

function CServerAuthProxy.GetAccount(self)
	return self.account_
end

function CServerAuthProxy.SetToken(self, token)
	self.token_ = token
end


function CServerAuthProxy.GetToken(self)
	return self.token_
end


function CServerAuthProxy.SetAccountId(self, accountId)
	self.accountId_ = accountId
end


function CServerAuthProxy.GetAccountId(self)
	return self.accountId_
end

function CServerAuthProxy.SetServerTable(self, serverTable)
	self.serverTable_ = serverTable
end


function CServerAuthProxy.GetServerTable(self)
	return self.serverTable_
end

return CServerAuthProxy