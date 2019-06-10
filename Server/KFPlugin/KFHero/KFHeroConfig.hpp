#ifndef __KF_HERO_CONFIG_H__
#define __KF_HERO_CONFIG_H__

#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    class KFHeroSetting
    {
    public:
        // id
        uint32 _id = 0u;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFHeroConfig : public KFConfig, public KFSingleton< KFHeroConfig >
    {
    public:
        KFHeroConfig()
        {
            _file = "hero.config";
        }

        // 读取配置
        bool LoadConfig( const std::string& file );

        // 查找配置
        const KFHeroSetting* FindHeroSetting( uint32 heroid ) const;

    private:
        // 品质列表
        KFHashMap< uint32, uint32, KFHeroSetting > _settings;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_hero_config = KFHeroConfig::Instance();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif