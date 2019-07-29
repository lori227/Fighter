#include "KFMatchConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    void KFMatchConfig::ReadSetting( KFNode& xmlnode, KFMatchSetting* kfsetting )
    {
        kfsetting->_max_count = xmlnode.GetUInt32( "MaxCount" );
        kfsetting->_upper_grade = xmlnode.GetUInt32( "UpperGrade" );
        kfsetting->_lower_grade = xmlnode.GetUInt32( "LowerGrade" );
        kfsetting->_add_robot_time = xmlnode.GetUInt32( "AddRobotTime" );
        kfsetting->_add_robot_count = xmlnode.GetUInt32( "AddRobotCount" );
    }
}