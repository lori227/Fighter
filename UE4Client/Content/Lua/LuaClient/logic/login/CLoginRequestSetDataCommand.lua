local CLoginRequestSetDataCommand = class("CLoginRequestSetDataCommand", CCommand)

function CLoginRequestSetDataCommand.ctor(self)
	CCommand.ctor(self)
end

function CLoginRequestSetDataCommand.Execute(self, notification)
	print("CLoginRequestSetDataCommand.Execute...")

	self:SetData()
end

function CLoginRequestSetDataCommand.SetData(self)
	local loginProxy = g_Facade:RetrieveProxy(ProxyEnum.LOGIN)

	local name = loginProxy:GetEmporaryPlayerName()

	if self:characters(name, 2) <= 14 then
		
		local MsgSetNameReq = 
		{
		   name = loginProxy:GetEmporaryPlayerName()
		}
		
		local str = pbc.encode("KFMsg.MsgSetNameReq", MsgSetNameReq)
		g_Network:Send(ProtobufEnum.MSG_SET_NAME_REQ, str, #str)
	else
	    local loginMediator = g_Facade:RetrieveMediator(MediatorEnum.LOGIN)
	    loginMediator:SetTargetVisibility(loginMediator.uiResultText_, 4)
		loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_TOO_LONG"].Des) 
	end
end

function CLoginRequestSetDataCommand.characters(self, utf8Str, aChineseCharBytes)
    aChineseCharBytes = aChineseCharBytes or 2   
    local i = 1
    local characterSum = 0

    if utf8Str == nil then
    	return characterSum
    end
    while (i <= #utf8Str) do      -- 编码的关系
        local bytes4Character = self.Bytes4Character(string.byte(utf8Str, i))
        characterSum = characterSum + (bytes4Character > aChineseCharBytes and aChineseCharBytes or bytes4Character)
        i = i + bytes4Character
    end

    return characterSum
end

function CLoginRequestSetDataCommand.Bytes4Character(theByte)
    local seperate = {0, 0xc0, 0xe0, 0xf0}
    
    for i = #seperate, 1, -1 do
        if theByte >= seperate[i] then return i end   
    end

    return 1
end

return CLoginRequestSetDataCommand

