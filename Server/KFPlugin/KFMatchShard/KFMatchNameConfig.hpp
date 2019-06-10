#ifndef __KF_MATCH_NAME_CONFIG_H__
#define __KF_MATCH_NAME_CONFIG_H__

#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    class KFMatchNameSetting
    {
    public:
        // 名字列表
        std::vector< std::string > _name_list;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchNameConfig : public KFConfig, public KFSingleton< KFMatchNameConfig >
    {
    public:
        KFMatchNameConfig()
        {
            _file = "name.config";
        }

        // 读取配置
        bool LoadConfig( const std::string& file );

        // 随机名字
        const std::string& RandName() const;

    private:
        // 名字列表
        KFHashMap< uint32, uint32, KFMatchNameSetting > _settings;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_name_config = KFMatchNameConfig::Instance();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif