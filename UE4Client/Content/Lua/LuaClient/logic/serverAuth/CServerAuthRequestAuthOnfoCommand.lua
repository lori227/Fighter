local CServerAuthRequestAuthOnfoCommand = class("CServerAuthRequestAuthOnfoCommand", CCommand)

function CServerAuthRequestAuthOnfoCommand.ctor(self)
	print("CServerAuthRequestAuthOnfoCommand.ctor...-----------&&&&&&&&&&&&&&&&&&&&&&---")

	CCommand.ctor(self)
end


function CServerAuthRequestAuthOnfoCommand.Execute(self, notification)
	print("CServerAuthRequestAuthOnfoCommand.Execute...----------------------------------------------")
	local serverAuthProxy = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
	local serverAuthMediator_ = g_Facade:RetrieveMediator(MediatorEnum.SERVER_AUTH)
	local uiPanel_ = serverAuthMediator_.uiPanel_
    -- self.serverAuthProxy_ = g_Facade:RetrieveProxy(ProxyEnum.SERVER_AUTH)
    -- self.serverAuthMediator_ = g_Facade:RetrieveMediator(MediatorEnum.SERVER_AUTH)

    -- self.uiPanel_ = self.serverAuthMediator_.uiPanel_

    print("self.uiLoginButton_:" .. tostring(uiLoginButton_))
    uiAccountEditText_ = uiPanel_:FindWidget('EditTextAccount')
    print("self.upriAccountEditText_:" .. tostring(uiAccountEditText_))
    uiPasswordEditText_ = uiPanel_:FindWidget('EditTextPassword')

        local count = math.random(10000,9999999)
        uiAccountEditText_:SetText(count)
        local password = math.random(10000,99999)
        uiPanel_.Password = password
 end
 return CServerAuthRequestAuthOnfoCommand