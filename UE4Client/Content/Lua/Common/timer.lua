local CTimer = class( "CTimer" )

local tableinsert = table.insert
local unpack = unpack or table.unpack

------------------------------------------------------
------------------------------------------------------
-- 循环定时器
local _loop_type = 1   

-- 次数定时器
local _count_type = 2
------------------------------------------------------
------------------------------------------------------
function CTimer:ctor()
    -- 最大的槽数
    self._max_slot = 1000

    -- 每个槽的时间( 20ms )
    self._slot_time = 0.02

    -- 每一圈的总时间
    self._wheel_time = self._max_slot * self._slot_time

    -- 当前的槽索引
    self._now_slot = 0

    -- 定时器列表
    self._timer_list = {}

    -- 时间轮
    self._wheel_list = {}
    for i = 1, self._max_slot do
        self._wheel_list[ i ] = {}
	end

    -- 经历时间
    self._tick_time = 0

    -- 需要添加的定时器列表
    self._add_list = {}

    -- 需要删除的定时器列表
    self._remove_list = {}
end

-- 添加循环定时器
function CTimer:AddLoopTimer( name, intervaltime, delaytime, cbfunc, ... )
    local data = {}
    data.name = name
    data.type = _loop_type
    data.intervaltime = intervaltime
    data.delaytime = delaytime
    data.cbfunc = cbfunc
    data.args = { ... }
    tableinsert( self._add_list, data )
end

-- 添加次数定时器
function CTimer:AddCountTimer( name, intervaltime, count, delaytime, cbfunc, ... )
    local data = {}
    data.name = name
    data.type = _count_type
    data.count = count
    data.intervaltime = intervaltime
    data.delaytime = delaytime
    data.cbfunc = cbfunc
    data.args = { ... }
    tableinsert( self._add_list, data )
end

-- 添加一个延迟执行( 只执行一次 )
function CTimer:AddDelayTimer( name, delaytime, cbfunc, ... )
    self:AddCountTimer( name, delaytime, 1, delaytime, cbfunc, ... )
end

function CTimer:RunAddTimer()
    for _, v in pairs( self._add_list ) do
        -- 先删除原有的定时器
        self:RemoveTimerData( v.name )

        -- 添加到时间轮
        local slot = self:AddToWheel( v )
        
        -- 添加到定时器列表
        local data = {}
        data.slot = slot;
        self._timer_list[ v.name ] = data
    end

    self._add_list = {}
end

function CTimer:AddToWheel( data )
    -- 计算时间轮刻度
    local slots = 0
    if data.delaytime ~= 0 then
        slots = data.delaytime / self._slot_time
        data.delaytime = 0
    else
        slots = data.intervaltime / self._slot_time
    end

    -- 至少需要1个刻度
    if slots == 0 then
        slots = 1
    end

    -- 时间轮圈数
    data.rotation = math.modf( slots / self._max_slot )
    
    -- 时间轮刻度位置
    local slot = slots % self._max_slot;
    data.slot = ( ( slot + self._now_slot ) % self._max_slot )
    if data.slot == 0 then
        data.slot = self._max_slot
    end

    -- 加入时间轮
    self._wheel_list[ data.slot ][ data.name ] = data

    return data.slot
end

function CTimer:RemoveTimer( name )
    local data = {}
    data.name = name
    tableinsert( self._remove_list, data )
end

function CTimer:RunRemoveTimer()
    for _, v in pairs( self._remove_list ) do
        self:RemoveTimerData( v.name )
    end

    self._remove_list = {}
end

function CTimer:RemoveTimerData( name )
    local data = self._timer_list[ name ]
    if data ~= nil then
        self._wheel_list[ data.slot ][ name ] = nil
        self._timer_list[ name ] = nil
    end
end

function CTimer:RunTimers( deltatime )
    self._tick_time = self._tick_time + deltatime 
    local slots = math.modf( self._tick_time / self._slot_time )
    if slots == 0 then
        return
    end

    -- 剩余时间
    self._tick_time = self._tick_time - ( slots * self._slot_time )

    -- 执行定时器
    for i = 1, slots do
        self._now_slot = ( self._now_slot + 1 ) % self._max_slot
        if self._now_slot == 0 then
            self._now_slot = self._max_slot
        end

        local executes = {}
        local timers = self._wheel_list[ self._now_slot ]
        for _, v in pairs( timers ) do
            -- 判断时间轮圈数
            if v.rotation > 0 then
                v.rotation = v.rotation - 1
            else
                tableinsert( executes, v )
            end
        end

        -- 可以执行的定时器
        for _, v in pairs( executes ) do
            -- 先删除时间轮
            timers[ v.name ] = nil

            -- 执行定时器
            self:RumTimerData( v )
        end

    end
end

function CTimer:RumTimerData( data )
    -- 执行定时器
    xpcall( data.cbfunc( unpack( data.args, select( "#", data.args ) ) ), printerror );

    -- 执行完后重新注册
    if data.type == _loop_type then
        local slot = self:AddToWheel( data )
        self._timer_list[ data.name ].slot = slot
    else
        data.count = data.count - 1
        if data.count == 0 then
            self:RemoveTimer( data.name )
        else
            local slot = self:AddToWheel( data )
            self._timer_list[ data.name ].slot = slot
        end
    end
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

function CTimer:Tick( deltatime )
    -- 删除定时器
    self:RunRemoveTimer()

    -- 添加定时器
    self:RunAddTimer()

    -- 更新定时器
    self:RunTimers( deltatime )
end

return CTimer


-- _timer:AddLoopTimer( "main", 5, 0, Main.Test, 1 , 3 )
-- function Main.Test( id1, id2 )
--  x = x +1
--  print( "id1="..id1.."id2="..id2.."x="..x )
--  if x == 10 then
--      _timer:RemoveTimer("main")
--  end
-- end

-- _timer:AddCountTimer( "display",3, 10, 0, function( id1, id2, id3, id4 ) 
--     self:TestTimer( id1, id2, id3, id4 ) 
-- end, 1, 3, 5, 7 )


-- function CDisplay:TestTimer( id1, id2, id3, id4 )
--    print( id1 )
--    print( id2 )
--    print( id3 )
--    print( id4 )
--    print( self.x )
-- end