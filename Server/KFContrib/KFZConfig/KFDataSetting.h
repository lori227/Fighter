﻿#ifndef __KF_DATA_SETTING_H__
#define __KF_DATA_SETTING_H__

#include "KFrame.h"
#include "KFSetting.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////
    namespace KFDataDefine
    {
        enum MyEnum
        {
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            // 数据类型
            Type_Unknow = 0,
            Type_Int32 = 1,
            Type_UInt32 = 2,
            Type_Int64 = 3,
            Type_UInt64 = 4,
            Type_Double = 5,
            Type_String = 6,
            Type_Vector3D = 7,
            Type_Object = 8,
            Type_Record = 9,
            Type_Array = 10,
            ////////////////////////////////////////////////////////////////////////////
            Array_Index = 1,		// kfarray的起始索引
            ////////////////////////////////////////////////////////////////////////////

            Mask_Null = 0,				// 无效值
            Mask_Create = 1 << 1,		// 是否需要创建
            Mask_Client = 1 << 2,		// 更新同步玩家
            Mask_View = 1 << 3,			// 同步给附近玩家
            Mask_Save = 1 << 4,			// 同步给附近玩家
            Mask_Log = 1 << 5,			// 打印日志
            Mask_Multiple = 1 << 6,		// 是否支持倍数
            Mask_Show = 1 << 7,			// 是否显示给客户端
            Mask_Delay = 1 << 8,		// 延迟同步到客户端
            Mask_AddCall = 1 << 9,		// 是否添加回调
            Mask_RemoveCall = 1 << 10,	// 是否删除回调
            Mask_UpdataCall = 1 << 11,	// 是否更新回调

            Mask_Public = 1 << 20,		// 公共属性
            Mask_Relation = 1 << 21,	// 关系属性
            Mask_Team = 1 << 22,		// 队伍属性
            Mask_Guild = 1 << 23,		// 帮派属性
            Mask_Rank = 1 << 24,		// 排行榜属性
            ////////////////////////////////////////////////////////////////////////////
            Data_Delete_None  = 0,		// 需要保存
            Data_Delete_Save = 1,		// 保存数据库
            Data_Delete_Remove = 2,		// 删除数据库
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            Show_None = 1,					// 不显示
            Show_Element = 2,				// 使用Element显示
            Show_Data = 3,					// 使用Data显示
        };

        static uint32 ConvertDataType( const std::string& stringtype )
        {
            if ( stringtype == "int32" )
            {
                return Type_Int32;
            }

            if ( stringtype == "uint32" )
            {
                return Type_UInt32;
            }

            if ( stringtype == "int64" )
            {
                return Type_Int64;
            }

            if ( stringtype == "uint64" )
            {
                return Type_UInt64;
            }

            if ( stringtype == "double" )
            {
                return Type_Double;
            }

            if ( stringtype == "string" )
            {
                return Type_String;
            }

            if ( stringtype == "vector3d" )
            {
                return Type_Vector3D;
            }

            if ( stringtype == "object" )
            {
                return Type_Object;
            }

            if ( stringtype == "record" )
            {
                return Type_Record;
            }

            if ( stringtype == "array" )
            {
                return Type_Array;
            }

            return Type_Unknow;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class KFClassSetting;
    class KFDataSetting
    {
    public:
        // 属性标记
        inline bool HaveMask( uint32 mask ) const
        {
            return KFUtility::HaveBitMask( _data_mask, mask );
        }

    public:
        // 属性名字
        std::string _name;

        // 逻辑名字
        std::string _logic_name;

        // 属性类型
        uint32 _type = 0u;
        uint32 _logic_type = 0u;

        // 包含类型
        std::string _contain_class;
        const KFClassSetting* _class_setting = nullptr;

        // 初始值
        std::string _str_init_value;
        uint32 _int_init_value = 0u;

        // 最小值
        std::string _str_min_value;
        uint32 _int_min_value = 0u;

        // 最大值
        std::string _str_max_value;
        uint32 _int_max_value = __MAX_UINT32__;

        // 逻辑值
        std::string _str_logic_value;
        uint32 _int_logic_value = 0u;

        // 属性标记
        uint32 _data_mask = 0u;

        // 延迟保存时间
        uint32 _delay_save_time = 0u;

        // 删除时操作
        uint32 _delete_type = 0u;

        // 索引字段
        std::string _key_name;

        // 配置索引值
        std::string _config_key_name;

        // 数值属性字段
        std::string _value_key_name;

        // 脚本文件
        std::string _lua_file;

        // 脚本函数
        std::string _update_function;
        std::string _add_function;
        std::string _remove_function;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 对象类定义
    class KFClassSetting : public KFStrSetting
    {
    public:
        // 查找配置
        inline const KFDataSetting* FindSetting( const std::string& name ) const
        {
            return _static_data.Find( name );
        }

        // 是否是子节点
        inline bool IsChildData( const std::string& name ) const
        {
            return _static_data.Find( name ) != nullptr;
        }

        // 查找属性
        inline const KFDataSetting* TraversalSetting( const std::string& name ) const
        {
            for ( auto& iter : _static_data._objects )
            {
                auto kfdatassetting = iter.second;
                if ( kfdatassetting->_name == name )
                {
                    return kfdatassetting;
                }

                if ( kfdatassetting->_class_setting != nullptr )
                {
                    auto kfchildsetting = kfdatassetting->_class_setting->TraversalSetting( name );
                    if ( kfchildsetting != nullptr )
                    {
                        return kfchildsetting;
                    }
                }
            }

            return nullptr;
        }

    public:
        // 属性列表
        KFHashMap< std::string, const std::string&, KFDataSetting > _static_data;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
