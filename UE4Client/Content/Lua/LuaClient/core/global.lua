local setmetatable = setmetatable
local table = table
local pairs = pairs
local ipairs = ipairs
local select = select
local tinsert = table.insert
local assert = assert
local tostring = tostring
local xpcall = xpcall


--用lua的闭包实现回调
function callback(luaobj, funcname, ...)
	assert(luaobj[funcname], "callback error!not defind funcname:"..funcname)
	local args = {...}
	local len1 = select("#", ...)
	local id = weakref(luaobj)
	local function f(...)
		local real = getrefobj(id)
		if not real then
			return false
		end
		local len2 = select("#", ...)
		for i=1, len2 do
			args[len1 + i] = select(i, ...)
		end
		return real[funcname](real, unpack(args, 1, len1+len2))
	end

	return f
end