
local CGameSettingProxy = class("CGameSettingProxy", CProxy)

function CGameSettingProxy.ctor(self, name)
    CProxy.ctor(self, name)
end

function CGameSettingProxy.OnRegister(self)
	-- Read Cfg Data
	print("----------------------------Start Cfg--------------------------------")
	self.operateAct_cfg = require ("configs/example/Example")
	--self.operateAct_cfg = require("configs.example.Example")

	table.print(self.operateAct_cfg)
	print(self.operateAct_cfg[10010001].Picture)
	print("----------------------------End Cfg--------------------------------")
end

function CGameSettingProxy.OnRemove(self)
end

function requireEx(name)
	print("----------------------------Start Test--------------------------------")
	-- package.loaded的类型
	print(type(package.loaded))      -- table
	-- 没有require模块文件
	for i, v in pairs(package.loaded) do
	print(i,v)
	end

	print("package.path路径相关：")
	print(package.path)

	print("package.cpath路径相关：")
	print(package.cpath)

    -- 判定模块是否已加载
    if not package.loaded[name] then 
        local loader = findloader(name)
        if loader == nil then 
            error("unable to load module " .. name)
        end
        -- 将模块标记为已加载
        package.loaded[name] = true
        -- 初始化模块
        local res = loader(name)
        if res ~= nil then 
            package.loaded[name] = res
        end 
    end 
	print("----------------------------End Test--------------------------------")
    -- 返回模块数据
    return package.loaded[name]
end

return CGameSettingProxy