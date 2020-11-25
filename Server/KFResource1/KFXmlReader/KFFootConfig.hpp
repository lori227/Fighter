#ifndef __KF_FOOT_CONFIG_H__
#define __KF_FOOT_CONFIG_H__

#include "KFrame.h"

namespace KFrame
{
    class KFFootSetting : public KFIntSetting
    {
    public:
        // 名字
        std::string _name;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFFootConfig : public KFConfigT< KFFootSetting >, public KFInstance< KFFootConfig >
    {
    public:
        KFFootConfig()
        {
            _file_name = "foot";
        }

    protected:
        // 读取配资
        void ReadSetting( KFXmlNode& xmlnode, KFFootSetting* kfsetting )
        {
            kfsetting->_name = xmlnode.ReadString( "Name" );
        }
    };
}

#endif