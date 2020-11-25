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
        virtual void ReadSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
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
        void ReadCommonSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_type = xmlnode.ReadUInt32( "Type" );
            kfsetting->_quality = xmlnode.ReadUInt32( "Quality" );
            kfsetting->_use_count = xmlnode.ReadUInt32( "UseCount", true );
            kfsetting->_use_limit = xmlnode.ReadUInt32( "UseLimit", true, KFItemEnum::UseInAll );
            kfsetting->_overlay_type = xmlnode.ReadUInt32( "OverlayType" );
            kfsetting->_overlay_count = xmlnode.ReadUInt32( "OverlayCount" );

            auto strsell = xmlnode.ReadString( "Sell", true );
            kfsetting->_sell_elements.Parse( strsell, __FUNC_LINE__ );

            kfsetting->_lua_file = xmlnode.ReadString( "LuaFile", true );
            auto addfunction = xmlnode.ReadString( "AddFunction", true );
            if ( !addfunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::AddFunction ] = addfunction;
            }

            auto usefunction = xmlnode.ReadString( "UseFunction", true );
            if ( !usefunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::UseFunction ] = usefunction;
            }

            auto removefunction = xmlnode.ReadString( "RemoveFunction", true );
            if ( !removefunction.empty() )
            {
                kfsetting->_function[ KFItemEnum::RemoveFunction ] = removefunction;
            }
        }

        // 读取礼包配置
        void ReadGiftSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_drop_id = xmlnode.ReadUInt32( "DropId", true );

            auto strreward = xmlnode.ReadString( "Reward", true );
            if ( !strreward.empty() )
            {
                kfsetting->_reward.Parse( strreward, __FUNC_LINE__ );
            }
        }


        // 读取药品配置
        void ReadDrugSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_drug_type = xmlnode.ReadUInt32( "DrugType" );

            auto strrestore = xmlnode.ReadString( "Restore" );
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
        void ReadEquipSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {
            kfsetting->_equip_type = xmlnode.ReadUInt32( "EquipType" );
            kfsetting->_weapon_type = xmlnode.ReadUInt32( "WeaponType" );
            kfsetting->_level_limit = xmlnode.ReadUInt32( "LevelLimit", true );
            kfsetting->_durability = xmlnode.ReadUInt32( "Durability", true );

            auto strskill = xmlnode.ReadString( "Skill", true );
            KFUtility::SplitSet( kfsetting->_skills, strskill, __SPLIT_STRING__ );
        }

        // 读取材料配置
        void ReadMaterialSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {

        }

        // 读取其他配置
        void ReadOtherSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
        {

        }
    };
}

#endif