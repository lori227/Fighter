local CDeviationItem = class("CDeviationItem")

function CDeviationItem.ctor(self, id, deviation, lock)
	--偏向ID
    self.id_ = id
    --偏向
    self.deviation_ = deviation
    --是否解锁
    self.lock_ = lock
    --解锁条件
    --self.condition_ = condition
end

function CDeviationItem.GetId(self)
	return self.id_
end

function CDeviationItem.SetDeviationId(self, id)
	self.id_ = id
end

function CDeviationItem.GetDeviation(self)
	return self.deviation_
end

function CDeviationItem.SetDeviation(self, deviation)
	self.deviation_ = deviation
end

function CDeviationItem.GetLock(self)
	return self.lock_
end

function CDeviationItem.SetLock(self, lock)
	self.lock_ = lock
end

-- function CDeviationItem.GetCondition(self)
-- 	return self.condition_
-- end

-- function CDeviationItem.SetCondition(self, condition)
-- 	self.condition_ = condition
-- end

return CDeviationItem