#ifndef	__KF_EFFECT_CONFIG_H__
#define	__KF_EFFECT_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFEffectSetting : public KFIntSetting
	{
	public:
		// ����
		std::string _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFEffectConfig : public KFConfigT<KFEffectSetting>, public KFInstance<KFEffectConfig>
	{
	public:
		KFEffectConfig()
		{
			_key_name = "id";
			_file_name = "effect";
		}

		~KFEffectConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFEffectSetting> setting )
		{
			setting->_name = xml_node.ReadString( "name", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
