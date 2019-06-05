local CPVPMatchProxy = class("CPVPMatchProxy", CProxy)

function CPVPMatchProxy.ctor(self, name)
    CProxy.ctor(self, name)

    self.roomId_ = 0
    self.battleId_ = 0
    self.ip_ = ""
    self.port_ = 0
end

function CPVPMatchProxy.SetRoomId(self, roomId)
	self.roomId_ = roomId
end

function CPVPMatchProxy.GetRoomId(self)
	return self.roomId_
end

function CPVPMatchProxy.SetBattleId(self, battleId)
	self.battleId_ = battleId
end

function CPVPMatchProxy.GetBattleId(self)
	return self.battleId_
end

function CPVPMatchProxy.SetIp(self, ip)
	self.ip_ = ip
end

function CPVPMatchProxy.GetIp(self)
	return self.ip_
end

function CPVPMatchProxy.SetPort(self, port)
	self.port_ = port
end

function CPVPMatchProxy.GetPort(self)
	return self.port_
end

return CPVPMatchProxy