local progressTxt_lang_table = {}
if GlobalDataConfig.lang == "cnt" then
    local _lang = require ("configs/example/Example_progressTxt_cnt")
    setmetatable(progressTxt_lang_table, _lang)
end


if GlobalDataConfig.lang == "en" then
    local _lang = require ("configs/example/Example_progressTxt_en")
    setmetatable(progressTxt_lang_table, _lang)
end


if GlobalDataConfig.lang == "cn" then
    local _lang = require ("configs/example/Example_progressTxt_cn")
    setmetatable(progressTxt_lang_table, _lang)
end

local Picture_lang_table = {}
if GlobalDataConfig.lang == "cnt" then
    local _lang = require ("configs/example/Example_Picture_cnt")
    setmetatable(Picture_lang_table, _lang)
end


if GlobalDataConfig.lang == "en" then
    local _lang = require ("configs/example/Example_Picture_en")
    setmetatable(Picture_lang_table, _lang)
end


if GlobalDataConfig.lang == "cn" then
    local _lang = require ("configs/example/Example_Picture_cn")
    setmetatable(Picture_lang_table, _lang)
end

local text1_lang_table = {}
if GlobalDataConfig.lang == "cnt" then
    local _lang = require ("configs/example/Example_text1_cnt")
    setmetatable(text1_lang_table, _lang)
end


if GlobalDataConfig.lang == "en" then
    local _lang = require ("configs/example/Example_text1_en")
    setmetatable(text1_lang_table, _lang)
end


if GlobalDataConfig.lang == "cn" then
    local _lang = require ("configs/example/Example_text1_cn")
    setmetatable(text1_lang_table, _lang)
end

local title_lang_table = {}
if GlobalDataConfig.lang == "cnt" then
    local _lang = require ("configs/example/Example_title_cnt")
    setmetatable(title_lang_table, _lang)
end


if GlobalDataConfig.lang == "en" then
    local _lang = require ("configs/example/Example_title_en")
    setmetatable(title_lang_table, _lang)
end


if GlobalDataConfig.lang == "cn" then
    local _lang = require ("configs/example/Example_title_cn")
    setmetatable(title_lang_table, _lang)
end

---@class ExampleInfo
---@field activityId number
---@field seq number
---@field type number
---@field target number
---@field subTarget string
---@field targetValue number
---@field reward string
---@field priority number
---@field uiSwitch number
---@field rewardType number
---@field rewardMax number
---@field title string
---@field text1 string
---@field progressTxt string
---@field Picture string
---@field targetValueDisplay number
---@field blessBag_wx number
---@field blessBag_qq number
local __default_values = 
{
		Picture = Picture_lang_table[10001],
		reward = "{}",
		target = 0,
		seq = 1,
		title = title_lang_table[10001],
		rewardMax = 0,
		rewardType = 1,
		priority = 1,
		progressTxt = progressTxt_lang_table[10001],
		activityId = 1,
		text1 = text1_lang_table[10010001],
		uiSwitch = 3,
		blessBag_qq = 0,
		subTarget = 0,
		targetValue = 1.0,
		_id = 10010001,
		type = 0,
		targetValueDisplay = 0,
		blessBag_wx = 0,

}

local data = 
{

	[10010001] =
	{
		activityId = 1001,
		uiSwitch = 2,
		title = title_lang_table[10010001],
		progressTxt = progressTxt_lang_table[10010001],
		Picture = Picture_lang_table[10010001],
	},
	[10001] =
	{
		text1 = text1_lang_table[10001],
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
