#ifndef __KF_MATCH_CONFIG_H__
#define __KF_MATCH_CONFIG_H__

#include "KFrame.h"
#include "KFZConfig/KFConfig.h"

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
    class KFMatchConfig : public KFIntConfigT< KFMatchSetting >, public KFInstance< KFMatchConfig >
    {
    public:
        KFMatchConfig()
        {
            _file_name = "match";
        }

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFMatchSetting* kfsetting );
    };
}

#endif