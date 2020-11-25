#ifndef	__KF_LEAVE_CONFIG_H__
#define	__KF_LEAVE_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFLeaveSetting : public KFIntSetting
	{
	public:
		// lua�ű�
		std::string _lua_file;

		// ���ú���
		std::string _lua_function;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFLeaveConfig : public KFConfigT< KFLeaveSetting >, public KFInstance< KFLeaveConfig >
	{
	public:
		KFLeaveConfig()
		{
			_key_name = "id";
			_file_name = "leave";
		}

		~KFLeaveConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFLeaveSetting* kfsetting )
		{
			kfsetting->_lua_file = xmlnode.ReadString( "luafile", true );
			kfsetting->_lua_function = xmlnode.ReadString( "luafunction", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
