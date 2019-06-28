local CTimeCtrl = class("CTimeCtrl")
local tinsert = table.insert
local tremove = table.remove
local ipairs = ipairs

function CTimeCtrl.ctor(self)
	self.m_TimerDict = {}
	self.m_TimerIDList = {}
	--预留1000个特殊id
	self.m_UniqueID = 1000
end

--递增不重复id
function CTimeCtrl.GetUniqueID(self)
	self.m_UniqueID = self.m_UniqueID  + 1
	return self.m_UniqueID
end

function CTimeCtrl.AddTimer(self, cbfunc, delta, delay, ...)
	local iTimerID = self:GetUniqueID()
	self.m_TimerDict[iTimerID] = {
		cbfunc = cbfunc,
		delta = delta,
		delay = delay,
		next_call_time = delay,
		deltaTimeTotal = 0,
		myargs = {...}
	}
	tinsert(self.m_TimerIDList, iTimerID)
	return iTimerID
end

function CTimeCtrl.DelTimer(self, iTimerID)
	self.m_TimerDict[iTimerID] = nil
end

function CTimeCtrl.UpdateList(self, list, deltatime)
	if not next(list) then
		return
	end
	local lDel = {}

	for i, id in ipairs(list) do
		local v = self.m_TimerDict[id]
		if v then 
			v.deltaTimeTotal = v.deltaTimeTotal + deltatime
			if v.deltaTimeTotal - v.next_call_time >= -0.005 then
				local callDelta = v.deltaTimeTotal - v.next_call_time
				local unpack = unpack or table.unpack
				local sucess, ret = xxpcall(v.cbfunc, v.deltaTimeTotal, id, unpack(v.myargs, 1, select("#", v.myargs)))
				if sucess == true then
					v.deltaTimeTotal = 0
					v.next_call_time = v.delta
				else
					v.deltaTimeTotal = 0
					tinsert(lDel, i)
					self.m_TimerDict[id] = nil
				end
			end
		else
			tinsert(lDel, i)
		end
	end
	for j=#lDel, 1, -1 do
		tremove(list, lDel[j])
	end
end

function CTimeCtrl.Update(self, deltatime)
	self:UpdateList(self.m_TimerIDList, deltatime)
end

function xxpcall(f, ...)
	local args = {...}
	local len = select("#", ...)
	local unpack = unpack or table.unpack
	return xpcall(function() return f(unpack(args, 1, len)) end, printerror)
end

function printerror(...)
	local args = {}
	local len = select("#", ...)
	for i=1, len do
		local v = select(i, ...)
		tinsert(args, tostring(v))
	end
	local msg = table.concat(args, " ")
	msg = msg.."\n"..debug.traceback()
	print(msg)
end

return CTimeCtrl