function NewPlayerFunction( playerid )
	-- 添加默认的模型

    -- 英雄
    local addhero = "[{\"hero\":{\"id\":\"1\"}},{\"hero\":{\"id\":\"2\"}}]"
    KFrame:AddData( playerid, addhero, false );
end