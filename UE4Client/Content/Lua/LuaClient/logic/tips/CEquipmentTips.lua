local CEquipmentTips = class("CEquipmentTips",CTips)

function CEquipmentTips.ctor(self)
	CTips.ctor(self, slua.loadUI("/Game/Blueprints/UI/Widget/Tips/WB_EquipmentTips.WB_EquipmentTips"))
	self.equipmentIcon_ = self.tipsWidget_.EquipmentIcon
	self.equipmentName_ = self.tipsWidget_.EquipmentName
	self.equipmentDescription_ = self.tipsWidget_.EquipmentDescription
	self.backGround_ = self.tipsWidget_.Background
end

function CEquipmentTips.CreateTips(self, data)
	return self:CreateEquipmentTips(data)
end

function CEquipmentTips.CreateEquipmentTips(self, data)
	self:SetEquipmentIcon(data["EquipmentIcon"])
	self:SetEquipmentName(data["EquipmentName"])
 	self:SetEquipmentDescription(data["EquipmentDescription"])

	
	
	self:SetEquipmentTipsSize()

	return self.tipsWidget_
end

function CEquipmentTips.RemoveTips(self)
	CTips.RemoveTips(self)
end

function CEquipmentTips.SetEquipmentIcon(self, data)
	local str = nil
	if data ~= nil then
		str = "<Img id=\"" .. data .. "\"/>" 
	else
		str = "<Img id=\"Default\"/>" 
	end
	self:SetWidgetText(self.equipmentIcon_, str)
end

function CEquipmentTips.SetEquipmentName(self, data)
	local str = nil
	if data ~= nil then
		str = "<orange>" .. data .. "</>" 
	else
		str = "<orange>装备名称</>"
	end
	self:SetWidgetText(self.equipmentName_, str)
end

function CEquipmentTips.SetEquipmentDescription(self, data)
	local str = nil
	if data ~= nil then
		str = "<green>" .. data .. "</>" 
	else
		str = "<green>主要目的是增加物理吸血，吸取敌方的生命值或者增加自身血量。当英雄的伤害提高到一定程度上，就要购买吸血刀，做到能抗能打。</>"
	end
	self:SetWidgetText(self.equipmentDescription_, str)
end

function CEquipmentTips.SetEquipmentTipsSize(self)
	local v2 = KismetMathLibrary.MakeVector2D(2, 2)
	self.equipmentIcon_:SetRenderScale(v2)
	self.equipmentIcon_:ForceLayoutPrepass()
	local equipmentIconSizeV2 = self.equipmentIcon_:GetDesiredSize()
	--self.equipmentIcon_.Slot:SetPosition(equipmentIconSizeV2*(2-1)*1/2)
	v2.X = equipmentIconSizeV2.X*2 + 20
	v2.Y = 0
	self.equipmentName_.Slot:SetPosition(v2)
	local equipmentNameSizeV2 = self.equipmentName_:GetDesiredSize()
	self.equipmentDescription_:ForceLayoutPrepass()
	v2.X = 0
	v2.Y = equipmentIconSizeV2.Y*2
	self.equipmentDescription_.Slot:SetPosition(v2)
	local equipmentDescriptionSizeV2 = self.equipmentDescription_:GetDesiredSize()
	v2.X = 500
	v2.Y = equipmentIconSizeV2.Y*2+ equipmentDescriptionSizeV2.Y
	self:SetWidgetSize(self.backGround_, v2.X + 25, v2.Y + 25)
	v2.X = -12.5
	v2.Y = -12.5
	self.backGround_.Slot:SetPosition(v2)
end


return CEquipmentTips