
local weakid = 0
g_WeakObjs = setmetatable({}, {__mode="kv"})


function weakref(obj)
	local id = weakid
	g_WeakObjs[id] = obj
	weakid = weakid + 1
	return id
end


function getrefobj(id)
	if id then
		local o = g_WeakObjs[id]
		if isNil(o) then
			g_WeakObjs[id] = nil
		else
			return o
		end
	end
end

function isNil(o)
	if not o then
		return true
	end

	if type(o) == "userdata" then
		return tostring(o) == "null"
	end
	return false
end