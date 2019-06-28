---@class HeroRaceInfo
---@field Id number
---@field PhyleName string
---@field PhyleInfo string
local __default_values = 
{
		
}

local data = 
{

	[1] =
	{
		Id = 1601,
		PhyleName = "CHARACTER_BASIC_PHYIE_ORC",
		PhyleInfo = "CHARACTER_BASIC_PHYIE_ORC_INFO",
	},
	[2] =
	{
		Id = 1602,
		PhyleName = "CHARACTER_BASIC_PHYIE_HUMAN",
		PhyleInfo = "CHARACTER_BASIC_PHYIE_HUMAN_INFO",
	},
	[3] =
	{
		Id = 1603,
		PhyleName = "CHARACTER_BASIC_PHYIE_ELF",
		PhyleInfo = "CHARACTER_BASIC_PHYIE_ELF_INFO",
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
