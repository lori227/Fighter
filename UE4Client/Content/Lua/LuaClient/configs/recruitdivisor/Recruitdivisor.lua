---@class RecruitdivisorInfo
---@field Type number
---@field TypeName string
---@field Value number
---@field Probability number
---@field MaxCount number
---@field Name string
local __default_values = 
{
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_3",
		Type = 3,
		Probability = 60,
		MaxCount = 5,

}

local data = 
{

	[1] =
	{
		Type = 1,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_1",
		Value = 1601,
		Probability = 80,
		MaxCount = 3,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_1_ORC",
	},
	[2] =
	{
		Type = 1,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_1",
		Value = 1602,
		Probability = 80,
		MaxCount = 3,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_1_HUMAN",
	},
	[3] =
	{
		Type = 1,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_1",
		Value = 1603,
		Probability = 80,
		MaxCount = 3,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_1_ELF",
	},
	[4] =
	{
		Type = 2,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_2",
		Value = 1701,
		Probability = 70,
		MaxCount = 4,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_2_WALK",
	},
	[5] =
	{
		Type = 2,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_2",
		Value = 1702,
		Probability = 70,
		MaxCount = 4,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_2_RIDING",
	},
	[6] =
	{
		Type = 2,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_2",
		Value = 1703,
		Probability = 70,
		MaxCount = 4,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_2_FLYING",
	},
	[7] =
	{
		Type = 2,
		TypeName = "RECRUITMENT_CHARACTER_TENDENCY_2",
		Value = 1704,
		Probability = 70,
		MaxCount = 4,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_2_HEAVY",
	},
	[8] =
	{
		Value = 1801,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_3_SWORD",
	},
	[9] =
	{
		Value = 1802,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_3_AXE",
	},
	[10] =
	{
		Value = 1803,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_3_LANCE",
	},
	[11] =
	{
		Value = 1804,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_3_BOW",
	},
	[12] =
	{
		Value = 1805,
		Name = "RECRUITMENT_CHARACTER_TENDENCY_3_CANE",
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
