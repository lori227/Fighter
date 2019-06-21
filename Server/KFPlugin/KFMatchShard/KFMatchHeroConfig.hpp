#ifndef __KF_MATCH_HERO_CONFIG_H__
#define __KF_MATCH_HERO_CONFIG_H__

#include "KFrame.h"

namespace KFrame
{
    class KFMatchHeroSetting : public KFIntSetting
    {
    public:
        // 名字
        std::string _name;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchHeroConfig : public KFIntConfigT< KFMatchHeroSetting >, public KFSingleton< KFMatchHeroConfig >
    {
    public:
        KFMatchHeroConfig( const std::string& file, bool isclear )
            : KFIntConfigT< KFMatchHeroSetting >( file, isclear )
        {
        }

        // 随机英雄
        uint32 RandHero();

    protected:
        // 读取配资
        void ReadSetting( KFNode& xmlnode, KFMatchHeroSetting* kfsetting );
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_hero_config = KFMatchHeroConfig::Instance( "hero.xml", true );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif