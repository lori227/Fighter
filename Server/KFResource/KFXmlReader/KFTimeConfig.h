﻿#ifndef __KF_TIME_CONFIG_H__
#define __KF_TIME_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
    // 时间段
    class KFTimeSection
    {
    public:
        // 开始时间
        KFTimeData _start_time;

        // 结束时间( 所有数据为0, 表示不需要判断结束时间 )
        KFTimeData _end_time;
    };

    class KFTimeSetting : public KFIntSetting
    {
    public:
        // 时间类型
        uint32 _type = 0u;

        // 时间段列表
        std::vector< KFTimeSection > _time_section_list;
    };

    class KFTimeConfig : public KFConfigT< KFTimeSetting >, public KFInstance< KFTimeConfig >
    {
    public:
        KFTimeConfig()
        {
            _file_name = "time";
        }

    protected:
        // 读取配置
        virtual void ReadSetting( KFXmlNode& xmlnode, KFTimeSetting* kfsetting )
        {
            kfsetting->_type = xmlnode.ReadUInt32( "Type" );

            KFTimeSection timesection;
            timesection._start_time._flag = xmlnode.ReadUInt32( "Flag" );
            timesection._start_time._year = xmlnode.ReadUInt32( "StartYear" );
            timesection._start_time._month = xmlnode.ReadUInt32( "StartMonth" );
            timesection._start_time._day = xmlnode.ReadUInt32( "StartDay" );
            timesection._start_time._day_of_week = xmlnode.ReadUInt32( "StartDayOfWeek" );
            timesection._start_time._hour = xmlnode.ReadUInt32( "StartHour" );
            timesection._start_time._minute = xmlnode.ReadUInt32( "StartMinute" );

            timesection._end_time._flag = xmlnode.ReadUInt32( "Flag" );
            timesection._end_time._year = xmlnode.ReadUInt32( "EndYear" );
            timesection._end_time._month = xmlnode.ReadUInt32( "EndMonth" );
            timesection._end_time._day = xmlnode.ReadUInt32( "EndDay" );
            timesection._end_time._day_of_week = xmlnode.ReadUInt32( "EndDayOfWeek" );
            timesection._end_time._hour = xmlnode.ReadUInt32( "EndHour" );
            timesection._end_time._minute = xmlnode.ReadUInt32( "EndMinute" );

            kfsetting->_time_section_list.emplace_back( timesection );
        }
    };
}

#endif