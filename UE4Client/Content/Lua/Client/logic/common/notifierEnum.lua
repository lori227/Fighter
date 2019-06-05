
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
    OPEN_COMMON_PROMPT = "OpenCommonPrompt",
    CLOSE_COMMON_PROMPT = "CloseCommonPrompt",

    RESPONSE_RESULT_DISPLAY = "Response_Result_Display",
    ------------------通用提示---------------------

    ------------------版本檢測---------------------
    OPEN_CHECK_VERSION = "OpenCheckVersion",
    CLOSE_CHECK_VERSION = "CloseCheckVersion",

    REQUEST_VRESION_JSON = "RequestVersionJson",
    ------------------版本檢測---------------------

    ------------------版本更新---------------------
    OPEN_BATCH_UPDATE = "OpenBatchUpdate",
    CLOSE_BATCH_UPDATE = "CloseBatchUpdate",
    ------------------版本更新---------------------

    -----------------服務器驗證-------------------
    OPEN_SERVER_AUTH = "OpenServerAuth",
    CLOSE_SERVER_AUTH = "CloseServerAuth",

    REQUEST_AUTH_INFO = "RequestAuthInfo",
    -----------------服務器驗證-------------------

    -------------------登陸---------------------
    OPEN_LOGIN = "OpenLogin",
    CLOSE_LOGIN = "CloseLogin",

    REQUEST_LOGIN = "RequestLogin",
    RESPONSE_LOGIN = "ResponseLogin",
    -------------------登陸---------------------

    -------------------PVP匹配-------------------
    OPEN_PVP_MATCH = "OpenPVPMatch",
    CLOSE_PVP_MATCH = "ClosePVPMatch",
    
    REQUEST_PVP_MATCH_START = "RequestPVPMatchStart",
    REQUEST_PVP_MATCH_CANCEL = "RequestPVPMatchCancel",
    REQUEST_PVP_MATCH_CONFIRM = "RequestPVPMatchingConfirm",
    RESPONSE_MATCH_RESULT = "ResponseMatchResult",
    RESPONSE_BATTLE_REQ = "ResponseBattleReq",
    -------------------PVP匹配-------------------

    -------------------主营地----------------------------------------------------------------------------------------------------------------
    OPEN_MAIN_CAMPSITE = "OpenMainCampsite",
    CLOSE_MAIN_CAMPSITE = "CloseMainCampsite",

    REQUEST_PACK_DATA = "RequestPackData",
    REQUEST_RECRUITMENT_OFFICE_DATA = "RequestRecruitmentOfficeData",

    --背包模块--
    OPEN_PACK = "OpenPack",
    CLOSE_PACK = "ClosePack",

    REQUEST_REFRESH_PACK = "RequestRefreshPack",


    --招募所模块--
    OPEN_RECRUITMENT_OFFICE = "OpenRecruitmentOffice",
    CLOSE_RECRUITMENT_OFFICE = "CloseRecruitmentOffice",

    -------------------------招募偏向 
    RECRUITMENTT_DEVIATION_REFRESH_UI = "RecruitmentDeviationRefreshUI",
    RECRUITMENTT_DEVIATION_REQUEST_DATA = "RecruitmentDeviationRequestData",
    RECRUITMENTT_DEVIATION_RESPONSE_DATA = "RecruitmentDeviationResponseData",
    -------------------------招募商店
    RECRUITMENT_SHOP_REFRESH_UI = "RecruitmentShopReFreshUI",
    RECRUITMENT_SHOP_REQUEST_DATA = "RecruitmentShopRequestData",
    RECRUITMENT_SHOP_RESPONSE_DATA = "RecruitmentShopResponseData",
    -------------------------招募获得新角色
    REQUEST_REFRESH_Get_New_Role = "RequestRefreshGetNewRole",



    -------------------主营地----------------------------------------------------------------------------------------------------------------


    -------------------游戏设置---------------------
    OPEN_GAMESETTING = "OPEN_GAMESETTING",
    CLOSE_GAMESETTING = "CLOSE_GAMESETTING",
    -------------------游戏设置---------------------

    -------------------通用确认---------------------
    OPEN_COMMCONFIRM = "OPEN_COMMCONFIRM",
    CLOSE_COMMCONFIRM = "CLOSE_COMMCONFIRM",
    -------------------通用确认---------------------
}

SetErrorIndex(NotifierEnum)
