#ifndef	__KF_MATCH_CONFIG_H__
#define	__KF_MATCH_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFMatchSetting : public KFIntSetting
	{
	public:
		// 最大参与数量
		uint32 _max_count = 0u;

		// 向上的积分差
		uint32 _upper_grade = 0u;

		// 向下的及分差
		uint32 _lower_grade = 0u;

		// 添加机器人间隔时间
		uint32 _add_robot_time = 0u;

		// 每次添加机器人数量
		uint32 _add_robot_count = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFMatchConfig : public KFConfigT< KFMatchSetting >, public KFInstance< KFMatchConfig >
	{
	public:
		KFMatchConfig()
		{
			_key_name = "id";
			_file_name = "match";
		}

		~KFMatchConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFMatchSetting* kfsetting )
		{
			kfsetting->_max_count = xmlnode.ReadUInt32( "maxcount", true );
			kfsetting->_upper_grade = xmlnode.ReadUInt32( "uppergrade", true );
			kfsetting->_lower_grade = xmlnode.ReadUInt32( "lowergrade", true );
			kfsetting->_add_robot_time = xmlnode.ReadUInt32( "addrobottime", true );
			kfsetting->_add_robot_count = xmlnode.ReadUInt32( "addrobotcount", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
