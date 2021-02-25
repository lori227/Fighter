﻿#ifndef __KF_NET_DATA_H__
#define __KF_NET_DATA_H__

#include "KFDefine.h"

namespace KFrame
{
    // 网络连接数据
    class KFNetData
    {
    public:
        // 名字
        std::string _name;

        //类型
        std::string _type;

        // id
        uint64 _id = 0;
        std::string _str_id;

        // 连接id
        uint64 _session = 0;

        // 服务器ip
        std::string _ip;

        // 端口类型
        uint32 _port_type = 0;

        // 服务器端口
        uint32 _port = 0;
    };
    typedef std::vector< const KFNetData* > NetDataList;

    // 网络事件函数
    // 参数1 : 网络连接数据
    typedef std::function< void( const KFNetData* ) > KFNetEventFunction;
#define __KF_NET_EVENT_FUNCTION__( function )  void function( const KFNetData* net_data )
    //////////////////////////////////////////////////////////////////////////////
}

#endif // !__KF_NET_DATA_H__
