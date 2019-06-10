#include "KFMatchShardConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    bool KFMatchShardConfig::LoadConfig( const std::string& file )
    {
        //////////////////////////////////////////////////////////////////
        KFXml kfxml( file );
        auto config = kfxml.RootNode();
        auto xmlnode = config.FindNode( "Setting" );
        while ( xmlnode.IsValid() )
        {
            auto id = xmlnode.GetUInt32( "Id" );
            auto kfsetting = _settings.Create( id );

            kfsetting->_id = id;
            kfsetting->_max_count = xmlnode.GetUInt32( "MaxCount" );
            kfsetting->_upper_grade = xmlnode.GetUInt32( "UpperGrade" );
            kfsetting->_lower_grade = xmlnode.GetUInt32( "LowerGrade" );
            kfsetting->_add_robot_time = xmlnode.GetUInt32( "AddRobotTime" );
            kfsetting->_add_robot_count = xmlnode.GetUInt32( "AddRobotCount" );

            xmlnode.NextNode();
        }
        //////////////////////////////////////////////////////////////////

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////
    const KFMatchSetting* KFMatchShardConfig::FindMatchSetting( uint32 matchid ) const
    {
        return _settings.Find( matchid );
    }
}