local Des_lang_table = {}
if GlobalDataConfig.lang == "cnt" then
    local _lang = require ("configs/language/Language_Des_cnt")
    setmetatable(Des_lang_table, _lang)
end


if GlobalDataConfig.lang == "en" then
    local _lang = require ("configs/language/Language_Des_en")
    setmetatable(Des_lang_table, _lang)
end


if GlobalDataConfig.lang == "cn" then
    local _lang = require ("configs/language/Language_Des_cn")
    setmetatable(Des_lang_table, _lang)
end

---@class LanguageInfo
---@field Des string
local __default_values = 
{
		
}

local data = 
{

	["NAME_INPUT_DES"] =
	{
		Des = Des_lang_table["NAME_INPUT_DES"],
	},
	["NAME_NO_INPUT"] =
	{
		Des = Des_lang_table["NAME_NO_INPUT"],
	},
	["NAME_ALREADY_USE"] =
	{
		Des = Des_lang_table["NAME_ALREADY_USE"],
	},
	["NAME_TOO_LONG"] =
	{
		Des = Des_lang_table["NAME_TOO_LONG"],
	},
	["NAME_BUTTON_CONFIRM"] =
	{
		Des = Des_lang_table["NAME_BUTTON_CONFIRM"],
	},
	["NAME_BUTTON_RETURN"] =
	{
		Des = Des_lang_table["NAME_BUTTON_RETURN"],
	},
	["NAME_QUERY_PALYER_FAILED"] =
	{
		Des = Des_lang_table["NAME_QUERY_PALYER_FAILED"],
	},
	["NAME_NAME_FILTER_ERROR"] =
	{
		Des = Des_lang_table["NAME_NAME_FILTER_ERROR"],
	},
	["NAME_SET_OK"] =
	{
		Des = Des_lang_table["NAME_SET_OK"],
	},
	["NAME_ALREADY_SET"] =
	{
		Des = Des_lang_table["NAME_ALREADY_SET"],
	},
	["SEX_SET_OK"] =
	{
		Des = Des_lang_table["SEX_SET_OK"],
	},
}

do
    local base = {
        __index = __default_values,
        __newindex = function()
            error( "Attempt to modify read-only table" )
        end
    }
    for k, v in pairs(data) do
        setmetatable(v, base)
    end
    base.__metatable = false
end

return data
