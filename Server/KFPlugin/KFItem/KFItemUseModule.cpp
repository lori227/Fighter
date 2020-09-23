#include "KFItemUseModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFItemUseModule::BeforeRun()
    {
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_USE_ITEM_REQ, &KFItemUseModule::HandleUseItemReq );
    }

    void KFItemUseModule::BeforeShut()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_USE_ITEM_REQ );
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFItemUseModule::CheckCanUseItem( KFEntity* player, const KFItemSetting* kfsetting )
    {
        return true;
    }

    __KF_MESSAGE_FUNCTION__( KFItemUseModule::HandleUseItemReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgUseItemReq );

        // 判断是否有这个道具
        auto kfitem = player->Find( kfmsg.name(), kfmsg.uuid() );
        if ( kfitem == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::ItemDataNotExist );
        }

        auto itemid = kfitem->Get<uint32>( kfitem->_data_setting->_config_key_name  );
        auto kfsetting = KFItemConfig::Instance()->FindSetting( itemid );
        if ( kfsetting == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::ItemSettingNotExist, itemid );
        }

        if ( !kfsetting->CheckCanUse() )
        {
            return _kf_display->SendToClient( player, KFMsg::ItemCanNotUse );
        }

        if ( !CheckCanUseItem( player, kfsetting ) )
        {
            return _kf_display->SendToClient( player, KFMsg::ItemCanNotUseStatus );
        }

        auto ok = UseItem( player, kfitem, kfsetting );
        if ( !ok )
        {
            return _kf_display->SendToClient( player, KFMsg::ItemUseFailed );
        }

        // 扣除数量
        auto usecount = kfitem->Get<uint32>( __STRING__( usecount ) );
        if ( usecount + 1u >= kfsetting->_use_count )
        {
            player->UpdateObjectData( kfitem, __STRING__( count ), KFEnum::Dec, 1u );
        }
        else
        {
            player->UpdateObjectData( kfitem, __STRING__( usecount ), KFEnum::Add, 1u );
        }

        _kf_display->SendToClient( player, KFMsg::ItemUseOk, kfsetting->_id );
    }

    bool KFItemUseModule::UseItem( KFEntity* player, KFData* kfitem, const KFItemSetting* kfsetting )
    {
        switch ( kfsetting->_type )
        {
        case KFItemEnum::Gift:	// 礼包
            return UseGiftItem( player, kfitem, kfsetting );
            break;
        case KFItemEnum::Script:	// 脚本
            return UseScriptItem( player, kfitem, kfsetting );
            break;
        default:
            break;
        }

        return false;
    }

    bool KFItemUseModule::UseGiftItem( KFEntity* player, KFData* kfitem, const KFItemSetting* kfsetting )
    {
        // 判断各类资源是否满了
        if ( kfsetting->_drop_id != 0u )
        {
            _kf_drop->Drop( player, kfsetting->_drop_id, __STRING__( itemuse ), kfsetting->_id, __FUNC_LINE__ );
        }

        if ( !kfsetting->_reward.IsEmpty() )
        {
            player->AddElement( &kfsetting->_reward, _default_multiple, __STRING__( itemuse ), kfsetting->_id, __FUNC_LINE__ );
        }

        return true;
    }

    bool KFItemUseModule::UseScriptItem( KFEntity* player, KFData* kfitem, const KFItemSetting* kfsetting )
    {
        if ( kfsetting->_lua_file.empty() )
        {
            return false;
        }

        auto& luafunction = kfsetting->GetFunction( KFItemEnum::UseFunction );
        if ( luafunction.empty() )
        {
            return false;
        }

        auto playerid = player->GetKeyID();
        auto result = _kf_lua->Call( kfsetting->_lua_file, luafunction, playerid, kfsetting->_id, 1u );
        return result != 0u;
    }
}