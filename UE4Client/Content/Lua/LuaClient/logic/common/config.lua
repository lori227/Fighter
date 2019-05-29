local CConfig = class("CConfig")

function CConfig.ctor(self)
	self.clientBaseVersion_ = "1.0.2"
	self.versionJsonUrl_ = "http://193.112.103.109:8080/AHZQ/Version.json"
	self.serverPatchPakUrl_ = ""
end


function CConfig.GetClientBaseVersion(self)
	return self.clientBaseVersion_
end


function CConfig.GetVersionJsonUrl(self)
	return self.versionJsonUrl_
end


function CConfig.GetServerPatchPakUrl(self)
	return self.serverPatchPakUrl_
end

