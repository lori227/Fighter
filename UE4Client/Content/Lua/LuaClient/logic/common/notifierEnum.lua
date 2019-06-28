
local ToStr = function(value)
    if (type(value) == "string") then
        return "\"" .. value .. "\""
    end

    return tostring(value)
end

local SetErrorIndex = function(t)
    setmetatable(t, {
        __index = function(t, k)
            error("Can\'t index not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
        __newindex = function(t, k, v)
            error("Can\'t newindex not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
    })
end

NotifierEnum =
{
    ------------------通用提示---------------------
    RESOURCES_NOT_ENOUGH = "Resources_Not_Enough",
    RESPONSE_RESULT_DISPLAY = "Response_Result_Display",

    ------------------网络底层---------------------
    SOCKET_DISCONNECT = "SocketDisconnect",
    ------------------网络底层---------------------

    ------------------通用提示---------------------

    ------------------版本檢測---------------------
    REQUEST_VRESION_JSON = "RequestVersionJson",
    ------------------版本檢測---------------------

    ------------------版本更新---------------------
    ------------------版本更新---------------------

    -----------------服務器驗證-------------------
    REQUEST_AUTH_INFO = "RequestAuthInfo",
    -----------------服務器驗證-------------------

    -------------------登陸---------------------
    REQUEST_LOGIN = "RequestLogin",
    RESPONSE_LOGIN = "ResponseLogin",
    REQUEST_SET_DATA = "RequestSetData",
    RESPONSE_UPDATA_DATA = "ResponseUpdataData",
    -------------------登陸---------------------

    -------------------PVP匹配------------------
    REQUEST_PVP_MATCH_START = "RequestPVPMatchStart",
    REQUEST_PVP_MATCH_CANCEL = "RequestPVPMatchCancel",
    REQUEST_PVP_MATCH_CONFIRM = "RequestPVPMatchingConfirm",
    RESPONSE_MATCH_RESULT = "ResponseMatchResult",
    RESPONSE_BATTLE_REQ = "ResponseBattleReq",
    -------------------PVP匹配-------------------

    -------------------主营地--------------------
    REQUEST_PACK_DATA = "RequestPackData",
    REQUEST_RECRUITMENT_OFFICE_DATA = "RequestRecruitmentOfficeData",
    REQUEST_ROLE_LIST_DATA = "RequestRoleListData",
    -------------------主营地--------------------

    -------------------背包模块-------------------
    REQUEST_REFRESH_PACK = "RequestRefreshPack",
    -------------------背包模块-------------------

 
    -------------------角色列表--------------------
    ROLE_LIST_REFRESH_UI = "RoleListRefreshUI",
    ROLE_LIST_REQUEST_DATA = "RoleListRequestData",
    ROLE_LIST_RESPONSE_DATA = "RoleListResponseData",
    -------------------角色列表--------------------

    
    -------------------------角色详情界面--------------------
    ROLE_INFORMATION_REFRESH_UI = "RoleInformationRefreshUI",
    ROLE_INFORMATION_RESPONSE_DATA = "CRoleInformationResponseData",
    ROLE_INFORMATION_BUFF_REFRESH_UI = "CRoleInformationBuffRefreshUI",
    -------------------------角色详情界面--------------------

    COMMON_REQUEST_ADD_DATA = "CommonRequestAddData",
    

    ------------------招募所模块-------------------

    -------------------------招募偏向 
    DEVIATION_REQUEST_ADD_DATA = "DeviationRequestAddData",
    DEVIATION_REQUEST_REMOVE_DATA = "DeviationRequestRemoveData",
    DEVIATION_RESPONSE_UPDATE_DATA = "DeviationResponseUpdateData",

    -------------------------招募商店
    RECRUITMENT_SHOP_RESPONSE_UPDATE_DATA = "RecruitmentShopResponseUpdateData",
    RECRUITMENT_SHOP_REQUEST_RECRUIT_HERO = "RecruitmentShopRequestRecruitHero",
    RECRUITMENT_SHOP_REQUEST_REFRESH_RECRUIT = "RecruitmentShopRequestRefreshRecruit",
    
    -------------------------招募获得新角色

    ------------------招募所模块-------------------







    -------------------主营地----------------------------------------------------------------------------------------------------------------


    -------------------游戏设置---------------------
    -------------------游戏设置---------------------

    -------------------通用确认---------------------
    -------------------通用确认---------------------
}

SetErrorIndex(NotifierEnum)
