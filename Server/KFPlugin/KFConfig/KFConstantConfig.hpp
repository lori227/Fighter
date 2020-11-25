#ifndef	__KF_CONSTANT_CONFIG_H__
#define	__KF_CONSTANT_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFConstantSetting : public KFIntSetting
	{
	public:
		// �ֶ���(���ܸ�����ֶ�)
		std::string _name;

		// ��ֵ
		uint32 _key = 0u;

		// ������ֵ
		std::string _value;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFConstantConfig : public KFConfigT< KFConstantSetting >, public KFInstance< KFConstantConfig >
	{
	public:
		KFConstantConfig()
		{
			_key_name = "id";
			_file_name = "constant";
		}

		~KFConstantConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFConstantSetting* kfsetting )
		{
			kfsetting->_name = xmlnode.ReadString( "name", true );
			kfsetting->_key = xmlnode.ReadUInt32( "key", true );
			kfsetting->_value = xmlnode.ReadString( "value", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
