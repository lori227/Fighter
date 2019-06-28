local CMediatorFactory = class("CMediatorFactory")

function CMediatorFactory.ctor(self)
	self.map_ = {}
end

function CMediatorFactory.CreateMediator(self, cls)
	if self.map_[cls.classname] == nil then
		error("CMediatorFactory.CreateMediator fail, cls.classname:"..cls.classname)
		return nil
	end
	
	local m = self.map_[cls.classname].New()
	return m
end


function CMediatorFactory.RegisterMediator(self, cls)
	self.map_[cls.classname] = cls

	g_View:CreateMediator(cls)
end


function CMediatorFactory.RemoveMediator(self, cls)
	g_View:DestroyMediator(cls)

	self.map_[cls.classname] = nil
end

return CMediatorFactory

