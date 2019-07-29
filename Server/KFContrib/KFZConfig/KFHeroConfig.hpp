#ifndef __KF_HERO_CONFIG_H__
#define __KF_HERO_CONFIG_H__

#include "KFrame.h"
#include "KFZConfig/KFConfig.h"

namespace KFrame
{
    class KFHeroSetting : public KFIntSetting
    {
    public:
        // 名字
        std::string _name;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFHeroConfig : public KFIntConfigT< KFHeroSetting >, public KFInstance< KFHeroConfig >
    {
    public:
        KFHeroConfig()
        {
            _file_name = "hero";
        }

        // 随机英雄
        uint32 RandHeroId();

    protected:
        // 读取配资
        void ReadSetting( KFNode& xmlnode, KFHeroSetting* kfsetting );
    };
}

#endif