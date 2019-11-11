﻿#ifndef __KF_KERNEL_INTERFACE_H__
#define __KF_KERNEL_INTERFACE_H__

#include "KFEntity.h"
#include "KFComponent.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    class KFKernelInterface : public KFModule
    {
    public:
        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        // 查找组件
        virtual KFComponent* FindComponent( const std::string& dataname ) = 0;

        // 查找实体
        virtual KFEntity* FindEntity( const std::string& dataname, uint64 key, const char* function, uint32 line ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////
        // 创建数据
        virtual KFData* CreateObject( const std::string& dataname ) = 0;
        virtual KFData* CreateObject( const KFDataSetting* datasetting ) = 0;
        virtual KFData* CreateObject( const std::string& classname, const std::string& dataname ) = 0;
        virtual KFData* CreateObject( const KFDataSetting* datasetting, const KFMsg::PBObject* proto ) = 0;

        // 释放数据
        virtual void ReleaseObject( KFData* kfdata ) = 0;

        // 初始化数组( kfarray )
        virtual void InitArray( KFData* kfarray, uint32 size ) = 0;

        // 添加数组元素( kfarray )
        virtual KFData* AddArray( KFData* kfarray, int64 value ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////
        // 反序列化
        virtual bool ParseFromProto( KFData* kfdata, const KFMsg::PBObject* proto ) = 0;

        // 序列化
        virtual KFMsg::PBObject* SerializeToClient( KFData* kfdata ) = 0;
        virtual KFMsg::PBObject* SerializeToData( KFData* kfdata ) = 0;
        virtual KFMsg::PBObject* SerializeToView( KFData* kfdata ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_kernel, KFKernelInterface );
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif