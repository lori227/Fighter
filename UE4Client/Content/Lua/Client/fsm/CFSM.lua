local CFSM = class("CFSM")

function CFSM.ctor(self, name)
	--当前状态机的模式
    self.curState_ = {}
    --存放状态机的所有模式
    self.states_ = {}
    --存放状态机的模式交换
    self.transitions_ = {}
    --模式栈
    self.stackStates_ = {}
end

--判断状态机中是否有目标模式
--有为true
function CFSM.ContainState(self, stateId)
	return self.states_[stateId] ~= nil
end

--获取当前的模式ID
function CFSM.GetCurStateId(self)
 	if self.curState_ then
 		return self.curState_:GetStateId()
	end
end
 
--获取当前模式的运行状态
function CFSM.GetCurStateStatus(self)
	if self.curState_ then                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
		return self.curState_:GetStatus()
	end
end

 
--向状态机添加模式
function CFSM.AddState(self, stateInstance)
	if stateInstance == nil then
		return
	end

	local stateId = stateInstance:GetStateId()
	if self:ContainState(stateId) then
		return 
	end

	self.states_[stateId] = stateInstance

	--print("CFSM.AddState, stateId:".. tostring(stateId))
	--table.print(self.states_)
end

--添加状态机的模式切换
function CFSM.AddTransition(self, fromStateId, toStateId)
	if self:ContainState(fromStateId) and self:ContainState(toStateId) then
		if self.transitions_[fromStateId] == nil then
			self.transitions_[fromStateId] = {}
		end
		if self.transitions_[fromStateId][toStateId] == nil then
			self.transitions_[fromStateId][toStateId] = {}
		end

		table.insert(self.transitions_[fromStateId][toStateId], CFSMTransition.New(fromStateId, toStateId))	
		--print("CFSM.AddTransition, fromStateId:".. tostring(fromStateId) .. " toStateId:" .. tostring(toStateId))
	end
end

--切换游戏模式
function CFSM.DoEvent(self, event)
	local stateStackCount = table.count(self.stackStates_)
	if stateStackCount <= 0 then
		return false
	end

	if event == nil then
		return false
	end

	local stackOp = event:GetStackOp()
	print("stackOp:"..stackOp)
	if stackOp == FSMStackOpEnum.POP then
		table.remove(self.stackStates_)

		local stackStatesCount = table.count(self.stackStates_)
		if stackStatesCount <= 0 then
			return false
		end

		local realToState = self.stackStates_[stackStatesCount]
		realToState:OnEnter(event)
	else
		local wantToStateId = event:GetToStateId()
		if not self:ContainState(wantToStateId) then
			return false
		end
		local curState = self.stackStates_[stateStackCount]

		local fromStateId = curState:GetStateId()
		local toState = self.states_[event:GetToStateId()]
		local toStateId = toState:GetStateId()
		if fromStateId ~= toStateId then
			if self.transitions_[fromStateId][toStateId] == nil then
				return false
			end

			if curState:CanTranstion(event) == false then
				return false
			end

			curState:OnExit(event)

			
			if stackOp == FSMStackOpEnum.SET then
				self.stackStates_ = {}
				table.insert(self.stackStates_, table.count(self.stackStates_)+1, toState)
			elseif stackOp == FSMStackOpEnum.Push then
				table.insert(self.stackStates_, table.count(self.stackStates_)+1, toState)
			end

			toState:OnEnter(event)
			self.curState_ = toState
		else
			if self.curState_ then
				self.curState_:DoEvent(event)
			end
		end
	end
end


function CFSM.Tick(self, deltaTime)
	if self.curState_ then
		self.curState_:Tick(deltaTime)
	end
end


function CFSM.Startup(self, stateId)
	if self:ContainState(stateId) then
		self.curState_ = self.states_[stateId]
		print("CFSM.Startup, stateId:"..tostring(stateId))
		table.insert(self.stackStates_, table.count(self.stackStates_)+1, self.curState_)
		self.curState_:OnEnter()
		return true
	end

	return false
end

return CFSM