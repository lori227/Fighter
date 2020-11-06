﻿#ifndef __KF_EFFECT_CONFIG_H__
#define __KF_EFFECT_CONFIG_H__

#include "KFrame.h"
#include "KFConfig.h"

namespace KFrame
{
    class KFEffectSetting : public KFIntSetting
    {
    public:
        // 名字
        std::string _name;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFEffectConfig : public KFConfigT< KFEffectSetting >, public KFInstance< KFEffectConfig >
    {
    public:
        KFEffectConfig()
        {
            _file_name = "effect";
        }

    protected:
        // 读取配资
        void ReadSetting( KFXmlNode& xmlnode, KFEffectSetting* kfsetting )
        {
            kfsetting->_name = xmlnode.ReadString( "Name" );
        }
    };
}

#endif