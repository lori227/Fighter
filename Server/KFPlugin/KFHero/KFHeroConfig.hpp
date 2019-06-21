#ifndef __KF_HERO_CONFIG_H__
#define __KF_HERO_CONFIG_H__

#include "KFrame.h"

namespace KFrame
{
    class KFHeroSetting : public KFIntSetting
    {
    public:
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFHeroConfig : public KFIntConfigT< KFHeroSetting >, public KFSingleton< KFHeroConfig >
    {
    public:
        KFHeroConfig( const std::string& file, bool isclear )
            : KFIntConfigT< KFHeroSetting >( file, isclear )
        {
        }

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFHeroSetting* kfsetting );
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_hero_config = KFHeroConfig::Instance( "hero.xml", true );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif