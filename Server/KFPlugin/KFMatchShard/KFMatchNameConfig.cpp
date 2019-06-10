#include "KFMatchNameConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    bool KFMatchNameConfig::LoadConfig( const std::string& file )
    {
        _settings.Clear();
        //////////////////////////////////////////////////////////////////
        KFXml kfxml( file );
        auto config = kfxml.RootNode();
        auto xmlnode = config.FindNode( "Setting" );
        while ( xmlnode.IsValid() )
        {
            auto type = xmlnode.GetUInt32( "Type" );
            auto name = xmlnode.GetString( "Name" );

            auto kfsetting = _settings.Create( type );
            kfsetting->_name_list.push_back( name );

            xmlnode.NextNode();
        }
        //////////////////////////////////////////////////////////////////

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////
    const std::string& KFMatchNameConfig::RandName() const
    {
        static std::string _name = "";
        _name.clear();

        for ( auto iter : _settings._objects )
        {
            auto kfsetting = iter.second;
            if ( kfsetting->_name_list.empty() )
            {
                continue;
            }

            auto index = KFGlobal::Instance()->RandRatio( kfsetting->_name_list.size() );
            _name += kfsetting->_name_list[ index ];
        }

        return _name;
    }
}