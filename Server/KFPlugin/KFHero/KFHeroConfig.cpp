#include "KFHeroConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    bool KFHeroConfig::LoadConfig( const std::string& file )
    {
        _settings.Clear();
        //////////////////////////////////////////////////////////////////
        KFXml kfxml( file );
        auto config = kfxml.RootNode();
        auto xmlnode = config.FindNode( "item" );
        while ( xmlnode.IsValid() )
        {
            auto id = xmlnode.GetUInt32( "Id" );
            auto kfsetting = _settings.Create( id );

            kfsetting->_id = id;
            xmlnode.NextNode();
        }
        //////////////////////////////////////////////////////////////////

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////
    const KFHeroSetting* KFHeroConfig::FindHeroSetting( uint32 heroid ) const
    {
        return _settings.Find( heroid );
    }
}