#include "KFMatchHeroConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    bool KFMatchHeroConfig::LoadConfig( const std::string& file )
    {
        _hero_list.clear();
        //////////////////////////////////////////////////////////////////
        KFXml kfxml( file );
        auto config = kfxml.RootNode();
        auto xmlnode = config.FindNode( "Setting" );
        while ( xmlnode.IsValid() )
        {
            auto id = xmlnode.GetUInt32( "Id" );
            _hero_list.push_back( id );

            xmlnode.NextNode();
        }
        //////////////////////////////////////////////////////////////////

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////
    uint32 KFMatchHeroConfig::RandHero() const
    {
        if ( _hero_list.empty() )
        {
            return _invalid_int;
        }

        auto index = KFGlobal::Instance()->RandRatio( _hero_list.size() );
        return _hero_list[ index ];
    }
}