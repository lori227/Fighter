#ifndef __KF_MATCH_CONFIG_H__
#define __KF_MATCH_CONFIG_H__

#include "KFrame.h"

namespace KFrame
{
    class KFMatchSetting : public KFIntSetting
    {
    public:
        // 最大玩家数量
        uint32 _max_count = 0u;

        // 上限分差
        uint32 _upper_grade = 0u;

        // 下限分差
        uint32 _lower_grade = 0u;

        // 添加机器人时间间隔
        uint32 _add_robot_time = 0u;

        // 添加机器人数量
        uint32 _add_robot_count = 0u;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchConfig : public KFConfigT< KFMatchSetting >, public KFInstance< KFMatchConfig >
    {
    public:
        KFMatchConfig()
        {
            _file_name = "match";
        }

    protected:
        // 读取配置
        void ReadSetting( KFXmlNode& xmlnode, KFMatchSetting* kfsetting )
        {
            kfsetting->_max_count = xmlnode.ReadUInt32( "MaxCount" );
            kfsetting->_upper_grade = xmlnode.ReadUInt32( "UpperGrade" );
            kfsetting->_lower_grade = xmlnode.ReadUInt32( "LowerGrade" );
            kfsetting->_add_robot_time = xmlnode.ReadUInt32( "AddRobotTime" );
            kfsetting->_add_robot_count = xmlnode.ReadUInt32( "AddRobotCount" );
        }
    };
}

#endif