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
		// Ãû×Ö
		std::string _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFEffectConfig : public KFConfigT< KFEffectSetting >, public KFInstance< KFEffectConfig >
	{
	public:
		KFEffectConfig()
		{
			_key_name = "id";
			_file_name = "effect";
		}

		~KFEffectConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFEffectSetting* kfsetting )
		{
			kfsetting->_name = xmlnode.ReadString( "name", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
