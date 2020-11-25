#ifndef	__KF_FOOT_CONFIG_H__
#define	__KF_FOOT_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFFootSetting : public KFIntSetting
	{
	public:
		// Ãû×Ö
		std::string _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFFootConfig : public KFConfigT< KFFootSetting >, public KFInstance< KFFootConfig >
	{
	public:
		KFFootConfig()
		{
			_key_name = "id";
			_file_name = "foot";
		}

		~KFFootConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFFootSetting* kfsetting )
		{
			kfsetting->_name = xmlnode.ReadString( "name", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
