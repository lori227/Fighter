#ifndef	__KF_NAME_CONFIG_H__
#define	__KF_NAME_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFNameSetting : public KFIntSetting
	{
	public:
		// ���ַ���
		StringVector _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFNameConfig : public KFConfigT<KFNameSetting>, public KFInstance<KFNameConfig>
	{
	public:
		KFNameConfig()
		{
			_key_name = "id";
			_file_name = "name";
		}

		~KFNameConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFNameSetting> setting )
		{
			setting->_name.push_back( xml_node.ReadString( "name", true ) );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
