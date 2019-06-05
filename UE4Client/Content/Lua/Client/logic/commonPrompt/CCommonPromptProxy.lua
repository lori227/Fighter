local CCommonPromptProxy = class("CCommonPromptProxy", CProxy)

function CCommonPromptProxy.ctor(self, name)
    CProxy.ctor(self, name)

    self.prompt_ = ""
end

function CCommonPromptProxy.SetPrompt(self, prompt)
	self.prompt_ = prompt
end

function CCommonPromptProxy.GetPrompt(self)
	return self.prompt_
end


return CCommonPromptProxy