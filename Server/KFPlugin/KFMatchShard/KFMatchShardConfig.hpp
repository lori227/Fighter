#ifndef __KF_MATCH_SHARD_CONFIG_H__
#define __KF_MATCH_SHARD_CONFIG_H__

#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    class KFMatchSetting
    {
    public:
        // id
        uint32 _id = 0u;

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
    class KFMatchShardConfig : public KFConfig, public KFSingleton< KFMatchShardConfig >
    {
    public:
        KFMatchShardConfig()
        {
            _file = "match.config";
        }

        // 读取配置
        bool LoadConfig();

        // 查找配置
        const KFMatchSetting* FindMatchSetting( uint32 matchid ) const;

    public:
        // 品质列表
        KFHashMap< uint32, uint32, KFMatchSetting > _settings;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_shard_config = KFMatchShardConfig::Instance();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif