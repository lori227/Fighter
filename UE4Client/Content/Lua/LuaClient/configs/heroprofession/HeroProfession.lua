---@class HeroProfessionInfo
---@field Id number
---@field ClassName string
---@field ClassInfo string
---@field WeaponType string
---@field MoveType number
---@field Mobility number
---@field MaxEP number
---@field ClassLv number
local __default_values = 
{
		Mobility = 5,
		MaxEP = 4,
		WeaponType = "1801|1802|1803|1804",
		MoveType = 1701,

}

local data = 
{

	[1] =
	{
		Id = 1100,
		ClassName = "CHARACTER_BASIC_CLASS_SOLDIER",
		ClassInfo = "CHARACTER_BASIC_CLASS_SOLDIER_INFO",
		ClassLv = 1,
	},
	[2] =
	{
		Id = 1101,
		ClassName = "CHARACTER_BASIC_CLASS_MERCENARY",
		ClassInfo = "CHARACTER_BASIC_CLASS_MERCENARY_INFO",
		ClassLv = 2,
	},
	[3] =
	{
		Id = 1102,
		ClassName = "CHARACTER_BASIC_CLASS_SWORDMASTER",
		ClassInfo = "CHARACTER_BASIC_CLASS_SWORDMASTER_INFO",
		ClassLv = 3,
	},
	[4] =
	{
		Id = 1103,
		ClassName = "CHARACTER_BASIC_CLASS_GUARD",
		ClassInfo = "CHARACTER_BASIC_CLASS_GUARD_INFO",
		ClassLv = 2,
	},
	[5] =
	{
		Id = 1104,
		ClassName = "CHARACTER_BASIC_CLASS_ROYALGUARD",
		ClassInfo = "CHARACTER_BASIC_CLASS_ROYALGUARD_INFO",
		ClassLv = 3,
	},
	[6] =
	{
		Id = 1105,
		ClassName = "CHARACTER_BASIC_CLASS_CAVALRY",
		ClassInfo = "CHARACTER_BASIC_CLASS_CAVALRY_INFO",
		ClassLv = 1,
	},
	[7] =
	{
		Id = 1106,
		ClassName = "CHARACTER_BASIC_CLASS_SCOUT",
		ClassInfo = "CHARACTER_BASIC_CLASS_SCOUT_INFO",
		ClassLv = 2,
	},
	[8] =
	{
		Id = 1107,
		ClassName = "CHARACTER_BASIC_CLASS_FREELANCER",
		ClassInfo = "CHARACTER_BASIC_CLASS_FREELANCER_INFO",
		ClassLv = 3,
	},
	[9] =
	{
		Id = 1108,
		ClassName = "CHARACTER_BASIC_CLASS_KNIGHT",
		ClassInfo = "CHARACTER_BASIC_CLASS_KNIGHT_INFO",
		ClassLv = 2,
	},
	[10] =
	{
		Id = 1109,
		ClassName = "CHARACTER_BASIC_CLASS_CONQUEROR",
		ClassInfo = "CHARACTER_BASIC_CLASS_CONQUEROR_INFO",
		ClassLv = 3,
	},
	[11] =
	{
		Id = 1110,
		ClassName = "CHARACTER_BASIC_CLASS_ARCHER",
		ClassInfo = "CHARACTER_BASIC_CLASS_ARCHER_INFO",
		ClassLv = 1,
	},
	[12] =
	{
		Id = 1111,
		ClassName = "CHARACTER_BASIC_CLASS_ARBALEST",
		ClassInfo = "CHARACTER_BASIC_CLASS_ARBALEST_INFO",
		ClassLv = 2,
	},
	[13] =
	{
		Id = 1112,
		ClassName = "CHARACTER_BASIC_CLASS_HAWKEYE",
		ClassInfo = "CHARACTER_BASIC_CLASS_HAWKEYE_INFO",
		ClassLv = 3,
	},
	[14] =
	{
		Id = 1113,
		ClassName = "CHARACTER_BASIC_CLASS_RONIN",
		ClassInfo = "CHARACTER_BASIC_CLASS_RONIN_INFO",
		ClassLv = 2,
	},
	[15] =
	{
		Id = 1114,
		ClassName = "CHARACTER_BASIC_CLASS_RANGER",
		ClassInfo = "CHARACTER_BASIC_CLASS_RANGER_INFO",
		ClassLv = 3,
	},
	[16] =
	{
		Id = 1115,
		ClassName = "CHARACTER_BASIC_CLASS_PRIEST",
		ClassInfo = "CHARACTER_BASIC_CLASS_PRIEST_INFO",
		ClassLv = 1,
	},
	[17] =
	{
		Id = 1116,
		ClassName = "CHARACTER_BASIC_CLASS_HOLYHEALER",
		ClassInfo = "CHARACTER_BASIC_CLASS_HOLYHEALER_INFO",
		ClassLv = 2,
	},
	[18] =
	{
		Id = 1117,
		ClassName = "CHARACTER_BASIC_CLASS_BISHOP",
		ClassInfo = "CHARACTER_BASIC_CLASS_BISHOP_INFO",
		ClassLv = 3,
	},
	[19] =
	{
		Id = 1118,
		ClassName = "CHARACTER_BASIC_CLASS_WARLOCK",
		ClassInfo = "CHARACTER_BASIC_CLASS_WARLOCK_INFO",
		ClassLv = 1,
	},
	[20] =
	{
		Id = 1119,
		ClassName = "CHARACTER_BASIC_CLASS_SOURCES",
		ClassInfo = "CHARACTER_BASIC_CLASS_SOURCES_INFO",
		ClassLv = 2,
	},
	[21] =
	{
		Id = 1120,
		ClassName = "CHARACTER_BASIC_CLASS_WIZARD",
		ClassInfo = "CHARACTER_BASIC_CLASS_WIZARD_INFO",
		ClassLv = 3,
	},
	[22] =
	{
		Id = 1121,
		ClassName = "CHARACTER_BASIC_CLASS_HOLYPRIEST",
		ClassInfo = "CHARACTER_BASIC_CLASS_HOLYPRIEST_INFO",
		ClassLv = 2,
	},
	[23] =
	{
		Id = 1122,
		ClassName = "CHARACTER_BASIC_CLASS_SAGE",
		ClassInfo = "CHARACTER_BASIC_CLASS_SAGE_INFO",
		ClassLv = 3,
	},
	[24] =
	{
		Id = 1123,
		ClassName = "CHARACTER_BASIC_CLASS_ARCHER",
		ClassInfo = "CHARACTER_BASIC_CLASS_ARCHER_INFO",
		ClassLv = 1,
	},
	[25] =
	{
		Id = 1124,
		ClassName = "CHARACTER_BASIC_CLASS_SHOOTER",
		ClassInfo = "CHARACTER_BASIC_CLASS_SHOOTER_INFO",
		ClassLv = 2,
	},
	[26] =
	{
		Id = 1125,
		ClassName = "CHARACTER_BASIC_CLASS_HAWKEYE",
		ClassInfo = "CHARACTER_BASIC_CLASS_HAWKEYE_INFO",
		ClassLv = 3,
	},
	[27] =
	{
		Id = 1126,
		ClassName = "CHARACTER_BASIC_CLASS_DRAGONTAMER",
		ClassInfo = "CHARACTER_BASIC_CLASS_DRAGONTAMER_INFO",
		ClassLv = 1,
	},
	[28] =
	{
		Id = 1127,
		ClassName = "CHARACTER_BASIC_CLASS_DRAGONKNIGHT",
		ClassInfo = "CHARACTER_BASIC_CLASS_DRAGONKNIGHT_INFO",
		ClassLv = 2,
	},
	[29] =
	{
		Id = 1128,
		ClassName = "CHARACTER_BASIC_CLASS_DRAGONSLAYER",
		ClassInfo = "CHARACTER_BASIC_CLASS_DRAGONSLAYER_INFO",
		ClassLv = 3,
	},
	[30] =
	{
		Id = 1129,
		ClassName = "CHARACTER_BASIC_CLASS_WARRIOR",
		ClassInfo = "CHARACTER_BASIC_CLASS_WARRIOR_INFO",
		ClassLv = 1,
	},
	[31] =
	{
		Id = 1130,
		ClassName = "CHARACTER_BASIC_CLASS_BERSERKER",
		ClassInfo = "CHARACTER_BASIC_CLASS_BERSERKER_INFO",
		ClassLv = 2,
	},
	[32] =
	{
		Id = 1131,
		ClassName = "CHARACTER_BASIC_CLASS_MADORC",
		ClassInfo = "CHARACTER_BASIC_CLASS_MADORC_INFO",
		ClassLv = 3,
	},
	[33] =
	{
		Id = 1132,
		ClassName = "CHARACTER_BASIC_CLASS_URUKHAI",
		ClassInfo = "CHARACTER_BASIC_CLASS_URUKHAI_INFO",
		ClassLv = 2,
	},
	[34] =
	{
		Id = 1133,
		ClassName = "CHARACTER_BASIC_CLASS_IRONORC",
		ClassInfo = "CHARACTER_BASIC_CLASS_IRONORC_INFO",
		ClassLv = 3,
	},
	[35] =
	{
		Id = 1134,
		ClassName = "CHARACTER_BASIC_CLASS_WOLFRAIDER",
		ClassInfo = "CHARACTER_BASIC_CLASS_WOLFRAIDER_INFO",
		ClassLv = 1,
	},
	[36] =
	{
		Id = 1135,
		ClassName = "CHARACTER_BASIC_CLASS_LIGHTWOLF",
		ClassInfo = "CHARACTER_BASIC_CLASS_LIGHTWOLF_INFO",
		ClassLv = 2,
	},
	[37] =
	{
		Id = 1136,
		ClassName = "CHARACTER_BASIC_CLASS_HURRICANE",
		ClassInfo = "CHARACTER_BASIC_CLASS_HURRICANE_INFO",
		ClassLv = 3,
	},
	[38] =
	{
		Id = 1137,
		ClassName = "CHARACTER_BASIC_CLASS_PIONEER",
		ClassInfo = "CHARACTER_BASIC_CLASS_PIONEER_INFO",
		ClassLv = 2,
	},
	[39] =
	{
		Id = 1138,
		ClassName = "CHARACTER_BASIC_CLASS_BASTION",
		ClassInfo = "CHARACTER_BASIC_CLASS_BASTION_INFO",
		ClassLv = 3,
	},
	[40] =
	{
		Id = 1139,
		ClassName = "CHARACTER_BASIC_CLASS_ARCHER",
		ClassInfo = "CHARACTER_BASIC_CLASS_ARCHER_INFO",
		ClassLv = 1,
	},
	[41] =
	{
		Id = 1140,
		ClassName = "CHARACTER_BASIC_CLASS_HUNTER",
		ClassInfo = "CHARACTER_BASIC_CLASS_HUNTER_INFO",
		ClassLv = 2,
	},
	[42] =
	{
		Id = 1141,
		ClassName = "CHARACTER_BASIC_CLASS_HAWKEYE",
		ClassInfo = "CHARACTER_BASIC_CLASS_HAWKEYE_INFO",
		ClassLv = 3,
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
