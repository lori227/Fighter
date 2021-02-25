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
	class KFMatchConfig : public KFConfigT<KFMatchSetting>, public KFInstance<KFMatchConfig>
	{
	public:
		KFMatchConfig()
		{
			_key_name = "id";
			_file_name = "match";
		}

		~KFMatchConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFMatchSetting> setting )
		{
			setting->_max_count = xml_node.ReadUInt32( "maxcount", true );
			setting->_upper_grade = xml_node.ReadUInt32( "uppergrade", true );
			setting->_lower_grade = xml_node.ReadUInt32( "lowergrade", true );
			setting->_add_robot_time = xml_node.ReadUInt32( "addrobottime", true );
			setting->_add_robot_count = xml_node.ReadUInt32( "addrobotcount", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
