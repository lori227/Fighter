#ifndef	__KF_CONDITIONDEFINE_CONFIG_H__
#define	__KF_CONDITIONDEFINE_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	class ConditionTrigger
	{
	public:
		// ���»ص���ʽ
		uint32 _call_type = 0u;

		// ��������
		uint32 _trigger_type = 0u;

		// �������ʽ
		uint32 _trigger_check = 0u;

		// ����ֵʹ������
		uint32 _trigger_use = 0u;

		// ����ֵ
		uint32 _trigger_value = 0u;

		// ��������
		uint32 _use_operate = 0u;

		// ʹ�õ�����
		uint32 _use_type = 0u;

		// ���õ�ʹ����ֵ
		uint32 _use_value = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFConditionDefineSetting : public KFStrSetting
	{
	public:
		// ��������
		std::string _parent_name;

		// ��������
		std::string _data_name;

		// ��ʼֵ
		uint32 _init_calc_type = 0u;

		// �Ƿ񱣴�uuid
		bool _save_uuid = false;

		// ������������
		std::vector<ConditionTrigger> _condition_trigger;
	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFConditionDefineConfig : public KFConfigT<KFConditionDefineSetting>, public KFInstance<KFConditionDefineConfig>
	{
	public:
		KFConditionDefineConfig()
		{
			_key_name = "id";
			_file_name = "conditiondefine";
		}

		~KFConditionDefineConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFConditionDefineSetting> setting )
		{
			setting->_parent_name = xml_node.ReadString( "parentname", true );
			setting->_data_name = xml_node.ReadString( "dataname", true );
			setting->_init_calc_type = xml_node.ReadUInt32( "initcalctype", true );
			setting->_save_uuid = xml_node.ReadBoolen( "saveuuid", true );
		
			ConditionTrigger condition_trigger;
			condition_trigger._call_type = xml_node.ReadUInt32( "calltype", true );
			condition_trigger._trigger_type = xml_node.ReadUInt32( "triggertype", true );
			condition_trigger._trigger_check = xml_node.ReadUInt32( "triggercheck", true );
			condition_trigger._trigger_use = xml_node.ReadUInt32( "triggeruse", true );
			condition_trigger._trigger_value = xml_node.ReadUInt32( "triggervalue", true );
			condition_trigger._use_operate = xml_node.ReadUInt32( "useoperate", true );
			condition_trigger._use_type = xml_node.ReadUInt32( "usetype", true );
			condition_trigger._use_value = xml_node.ReadUInt32( "usevalue", true );
			setting->_condition_trigger.push_back( condition_trigger );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
