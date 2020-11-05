#ifndef __KF_ITEM_CONFIG_H__
#define __KF_ITEM_CONFIG_H__

#include "KFItemSetting.hpp"
#include "KFConfig.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFItemConfig : public KFConfigT< KFItemSetting >, public KFInstance< KFItemConfig >
    {
    public:
        KFItemConfig()
        {
            _file_name = "item";
        }
    protected:
        // 读取配置
        virtual void ReadSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {
            switch ( kfsetting->_type )
            {
            case KFItemEnum::Normal:
                break;
            case KFItemEnum::Gift:
                ReadGiftSetting( xmlnode, kfsetting );
                break;
            case KFItemEnum::Drug:
                ReadDrugSetting( xmlnode, kfsetting );
                break;
            case KFItemEnum::Equip:
                ReadEquipSetting( xmlnode, kfsetting );
                break;
            case KFItemEnum::Material:
                ReadMaterialSetting( xmlnode, kfsetting );
                break;
            case KFItemEnum::Other:
                ReadOtherSetting( xmlnode, kfsetting );
                break;
            default:
                ReadCommonSetting( xmlnode, kfsetting );
                break;
            }
        }

        // 读取通用道具
        void ReadCommonSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_type = xmlnode.GetUInt32( "Type" );
            kfsetting->_quality = xmlnode.GetUInt32( "Quality" );
            kfsetting->_use_count = xmlnode.GetUInt32( "UseCount", true );
            kfsetting->_use_limit = xmlnode.GetUInt32( "UseLimit", true, KFItemEnum::UseInAll );
            kfsetting->_overlay_type = xmlnode.GetUInt32( "OverlayType" );
            kfsetting->_overlay_count = xmlnode.GetUInt32( "OverlayCount" );

            auto strsell = xmlnode.GetString( "Sell", true );
            kfsetting->_sell_elements.Parse( strsell, __FUNC_LINE__ );

            kfsetting->_lua_file = xmlnode.GetString( "LuaFile", true );
            auto addfunction = xmlnode.GetString( "AddFunction", true );
            if ( !addfunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::AddFunction ] = addfunction;
            }

            auto usefunction = xmlnode.GetString( "UseFunction", true );
            if ( !usefunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::UseFunction ] = usefunction;
            }

            auto removefunction = xmlnode.GetString( "RemoveFunction", true );
            if ( !removefunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::RemoveFunction ] = removefunction;
            }
        }

        // 读取礼包配置
        void ReadGiftSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_drop_id = xmlnode.GetUInt32( "DropId", true );

            auto strreward = xmlnode.GetString( "Reward", true );
            if ( !strreward.empty() )
            {
                kfsetting->_reward.Parse( strreward, __FUNC_LINE__ );
            }
        }


        // 读取药品配置
        void ReadDrugSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_drug_type = xmlnode.GetUInt32( "DrugType" );

            auto strrestore = xmlnode.GetString( "Restore" );
            __JSON_PARSE_STRING__( kfjson, strrestore );
            for ( auto iter = kfjson.MemberBegin(); iter != kfjson.MemberEnd(); ++iter )
            {
                if ( iter->value.IsNumber() )
                {
                    kfsetting->_drug_values[ iter->name.GetString() ] = iter->value.GetInt();
                }
                else
                {
                    __LOG_ERROR__( "drug=[{}] values=[{}] not int!", kfsetting->_id, iter->name.GetString() );
                }
            }
        }

        // 读取装备配置
        void ReadEquipSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_equip_type = xmlnode.GetUInt32( "EquipType" );
            kfsetting->_weapon_type = xmlnode.GetUInt32( "WeaponType" );
            kfsetting->_level_limit = xmlnode.GetUInt32( "LevelLimit", true );
            kfsetting->_durability = xmlnode.GetUInt32( "Durability", true );

            auto strskill = xmlnode.GetString( "Skill", true );
            KFUtility::SplitSet( kfsetting->_skills, strskill, __SPLIT_STRING__ );
        }

        // 读取材料配置
        void ReadMaterialSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {

        }

        // 读取其他配置
        void ReadOtherSetting( KFNode& xmlnode, KFItemSetting* kfsetting )
        {

        }
    };
}

#endif