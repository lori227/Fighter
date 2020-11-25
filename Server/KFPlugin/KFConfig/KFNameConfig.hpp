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
		// Ãû×Ö·ûºÅ
		StringVector _name;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFNameConfig : public KFConfigT< KFNameSetting >, public KFInstance< KFNameConfig >
	{
	public:
		KFNameConfig()
		{
			_key_name = "id";
			_file_name = "name";
		}

		~KFNameConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFNameSetting* kfsetting )
		{
			kfsetting->_name.push_back( xmlnode.ReadString( "name", true ) );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
