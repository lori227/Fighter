#ifndef	__KF_HERO_CONFIG_H__
#define	__KF_HERO_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFHeroSetting : public KFIntSetting
	{
	public:
		// ����
		std::string _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFHeroConfig : public KFConfigT< KFHeroSetting >, public KFInstance< KFHeroConfig >
	{
	public:
		KFHeroConfig()
		{
			_key_name = "id";
			_file_name = "hero";
		}

		~KFHeroConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFHeroSetting* kfsetting )
		{
			kfsetting->_name = xmlnode.ReadString( "name", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
