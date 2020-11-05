#ifndef __KF_NAME_CONFIG_H__
#define __KF_NAME_CONFIG_H__

#include "KFrame.h"
#include "KFConfig.h"

namespace KFrame
{
    class KFNameSetting : public KFIntSetting
    {
    public:
        // 名字列表
        StringVector _name_list;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFNameConfig : public KFConfigT< KFNameSetting >, public KFInstance< KFNameConfig >
    {
    public:
        KFNameConfig()
        {
            _file_name = "name";
        }

        // 随机名字
        const std::string& RandName() const
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

                auto index = KFGlobal::Instance()->RandRatio( ( uint32 )kfsetting->_name_list.size() );
                _name += kfsetting->_name_list[ index ];
            }

            return _name;
        }

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFNameSetting* kfsetting )
        {
            auto name = xmlnode.GetString( "Name" );
            kfsetting->_name_list.push_back( name );
        }
    };
}

#endif