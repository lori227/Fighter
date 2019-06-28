local CCommonPromptResponseResultDisplayCommand = class("CCommonPromptResponseResultDisplayCommand", CCommand)
      
function CCommonPromptResponseResultDisplayCommand.ctor(self)
	CCommand.ctor(self)
end

function CCommonPromptResponseResultDisplayCommand.Execute(self, notification)
	print("CCommonPromptResponseResultDisplayCommand.Execute...")

	local body = notification:GetBody() 
    local t = pbc.decode("KFMsg.MsgResultDisplay", body["Data"], body["DataLength"])
    local result = t["result"]
	        
	print("*****************************服务器提示ID:" .. result .. "*****************************")

    if  12102 <= result and result <= 12107 then
    	--设置名字模块
	    local loginMediator = CLoginMediator:Get()

    	if loginMediator.uiResultText_ == nil then
       	 	return
   		else
        	loginMediator:SetTargetVisibility(loginMediator.uiResultText_, 4)
        	if result == 12102 then 
				loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_ALREADY_USE"].Des) 
	    	elseif result == 12103 then
	        	loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_SET_OK"].Des) 
	    	elseif result == 12104 then
	        	loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_TOO_LONG"].Des) 
	    	elseif result == 12105 then
	        	loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_NAME_FILTER_ERROR"].Des) 
	    	elseif result == 12106 then
	        	loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_NO_INPUT"].Des) 
	   		elseif result == 12107 then
	        	loginMediator.uiResultText_:SetText(g_LanguageCfg["NAME_ALREADY_SET"].Des) 
	    	end
   		end

   	elseif 31001 <= result and result <= 31005 then	
  		--PVP模块
  		local pvpMatchMediator = CPVPMatchMediator:Get()

  		if pvpMatchMediator.uiResultText_ == nil then
       	 	return
   		else
        	pvpMatchMediator:SetTargetVisibility(pvpMatchMediator.uiResultText_, 4)  	
			pvpMatchMediator.uiResultText_:SetText("服务器提示ID：" .. result) 
   		end
   	elseif 31101 <= result and result <= 31108 then
   		--偏好
   		
	end
 
end

return CCommonPromptResponseResultDisplayCommand