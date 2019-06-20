#ifndef __KF_MATCH_NAME_CONFIG_H__
#define __KF_MATCH_NAME_CONFIG_H__

#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    class KFMatchNameSetting : public KFIntSetting
    {
    public:
        // 名字列表
        std::vector< std::string > _name_list;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchNameConfig : public KFIntConfigT< KFMatchNameSetting >, public KFSingleton< KFMatchNameConfig >
    {
    public:
        KFMatchNameConfig( const std::string& file, bool isclear )
            : KFIntConfigT< KFMatchNameSetting >( file, isclear )
        {
        }

        // 随机名字
        const std::string& RandName() const;

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFMatchNameSetting* kfsetting );
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_name_config = KFMatchNameConfig::Instance( "name.xml", true );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif