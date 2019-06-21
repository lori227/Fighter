#ifndef __KF_MATCH_SHARD_CONFIG_H__
#define __KF_MATCH_SHARD_CONFIG_H__

#include "KFrame.h"

namespace KFrame
{
    class KFMatchSetting : public KFIntSetting
    {
    public:
        // 最大玩家数量
        uint32 _max_count = 0u;

        // 上限分差
        uint32 _upper_grade = 0u;

        // 下限分差
        uint32 _lower_grade = 0u;

        // 添加机器人时间间隔
        uint32 _add_robot_time = 0u;

        // 添加机器人数量
        uint32 _add_robot_count = 0u;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchShardConfig : public KFIntConfigT< KFMatchSetting >, public KFSingleton< KFMatchShardConfig >
    {
    public:
        KFMatchShardConfig( const std::string& file, bool isclear )
            : KFIntConfigT< KFMatchSetting >( file, isclear )
        {
        }

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFMatchSetting* kfsetting );
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_shard_config = KFMatchShardConfig::Instance( "match.xml", true );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif