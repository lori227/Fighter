#include "KFMatchHeroConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    void KFMatchHeroConfig::ReadSetting( KFNode& xmlnode, KFMatchHeroSetting* kfsetting )
    {
        kfsetting->_name = xmlnode.GetString( "Name" );
    }

    /////////////////////////////////////////////////////////////////////////////////
    uint32 KFMatchHeroConfig::RandHero()
    {
        auto size = _settings.Size();
        if ( size == 0u )
        {
            return _invalid_int;
        }

        auto index = KFGlobal::Instance()->RandRatio( size );
        auto begin = _settings._objects.begin();
        std::advance( begin, index );
        return begin->second->_id;
    }
}