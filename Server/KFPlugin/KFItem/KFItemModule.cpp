#include "KFItemModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFItemModule::BeforeRun()
    {
        _kf_component = _kf_kernel->FindComponent( __STRING__( player ) );
        __REGISTER_GET_CONFIG_VALUE__( __STRING__( item ), &KFItemModule::GetItemTotalCount );
        __REGISTER_ADD_DATA_1__( __STRING__( item ), &KFItemModule::OnAddItemCallBack );
        __REGISTER_REMOVE_DATA_1__( __STRING__( item ), &KFItemModule::OnRemoveItemCallBack );
        __REGISTER_UPDATE_DATA_2__( __STRING__( item ), __STRING__( count ), &KFItemModule::OnItemCountUpdateCallBack );
        __REGISTER_UPDATE_DATA_2__( __STRING__( item ), __STRING__( time ), &KFItemModule::OnItemTimeUpdateCallBack );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_CHECK_ADD_ELEMENT__( __STRING__( item ), &KFItemModule::CheckAddItemElement );
        __REGISTER_ADD_ELEMENT__( __STRING__( item ), &KFItemModule::AddItemElement );
        __REGISTER_CHECK_REMOVE_ELEMENT__( __STRING__( item ), &KFItemModule::CheckRemoveItemElement );
        __REGISTER_REMOVE_ELEMENT__( __STRING__( item ), &KFItemModule::RemoveItemElement );
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_ENTER_PLAYER__( &KFItemModule::OnEnterItemModule );
        __REGISTER_LEAVE_PLAYER__( &KFItemModule::OnLeaveItemModule );
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_REMOVE_ITEM_REQ, &KFItemModule::HandleRemoveItemReq );
    }

    void KFItemModule::BeforeShut()
    {
        __UN_TIMER_0__();
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_GET_CONFIG_VALUE__( __STRING__( item ) );
        __UN_ADD_DATA_1__( __STRING__( item ) );
        __UN_REMOVE_DATA_1__( __STRING__( item ) );
        __UN_UPDATE_DATA_2__( __STRING__( item ), __STRING__( count ) );
        __UN_UPDATE_DATA_2__( __STRING__( item ), __STRING__( time ) );

        __UN_CHECK_ADD_ELEMENT__( __STRING__( item ) );
        __UN_ADD_ELEMENT__( __STRING__( item ) );
        __UN_CHECK_REMOVE_ELEMENT__( __STRING__( item ) );
        __UN_REMOVE_ELEMENT__( __STRING__( item ) );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_ENTER_PLAYER__();
        __UN_LEAVE_PLAYER__();
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_REMOVE_ITEM_REQ );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFItemModule::BindInitItemFunction( uint32 itemtype, KFItemFunction& function )
    {
        auto kffunction = _init_item_function.Create( itemtype );
        kffunction->_function = function;
    }

    void KFItemModule::UnRegisteInitItemFunction( uint32 itemtype )
    {
        _init_item_function.Remove( itemtype );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_GET_CONFIG_VALUE_FUNCTION__( KFItemModule::GetItemTotalCount )
    {
        auto kfsetting = KFItemConfig::Instance()->FindSetting( id );
        if ( kfsetting == nullptr )
        {
            return 0u;
        }

        auto totalcount = 0u;
        auto kfitemrecord = player->Find( __STRING__( item ) );
        for ( auto kfitem = kfitemrecord->First(); kfitem != nullptr; kfitem = kfitemrecord->Next() )
        {
            auto itemid = kfitem->Get<uint32>( __STRING__( id ) );
            if ( itemid != id )
            {
                continue;
            }

            totalcount += kfitem->Get<uint32>( __STRING__( count ) );
            if ( totalcount >= maxvalue )
            {
                break;
            }
        }

        return totalcount;
    }

    __KF_CHECK_ADD_ELEMENT_FUNCTION__( KFItemModule::CheckAddItemElement )
    {
        if ( !kfelement->IsObject() )
        {
            return false;
        }

        // 计算物品数量
        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        auto itemcount = kfelementobject->CalcValue( kfparent->_data_setting, __STRING__( count ), multiple );
        if ( itemcount == _invalid_int || kfelementobject->_config_id == _invalid_int )
        {
            return false;
        }

        auto kfsetting = KFItemConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            return false;
        }

        return !CheckItemRecordFull( kfparent, kfsetting, itemcount );
    }

    bool KFItemModule::CheckItemRecordFull( KFData* kfitemrecord, const KFItemSetting* kfsetting, uint32 itemcount )
    {
        // 计算占用格子数
        uint32 usesize = ( itemcount + kfsetting->_overlay_count - 1 ) / kfsetting->_overlay_count;
        auto leftsize = kfitemrecord->MaxSize() - kfitemrecord->Size();
        if ( leftsize >= usesize )
        {
            return false;
        }

        // 不能叠加
        if ( kfsetting->IsOverlay() )
        {
            // 剩余格子可叠加物品数
            auto canaddcount = leftsize * kfsetting->_overlay_count;
            for ( auto kfitem = kfitemrecord->First(); kfitem != nullptr; kfitem = kfitemrecord->Next() )
            {
                auto itemid = kfitem->Get<uint32>( kfitemrecord->_data_setting->_config_key_name );
                if ( itemid != kfsetting->_id )
                {
                    continue;
                }

                auto oldcount = kfitem->Get( __STRING__( count ) );
                canaddcount += kfsetting->_overlay_count - __MIN__( oldcount, kfsetting->_overlay_count );
                if ( canaddcount >= itemcount )
                {
                    return false;
                }
            }
        }

        return true;
    }

    __KF_ADD_ELEMENT_FUNCTION__( KFItemModule::AddItemElement )
    {
        auto kfelement = kfresult->_element;
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return false;
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return false;
        }

        auto kfsetting = KFItemConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "id=[{}] itemsetting = null!", kfelementobject->_config_id );
            return false;
        }

        // 计算物品数量
        auto itemcount = kfelementobject->CalcValue( kfparent->_data_setting, __STRING__( count ), kfresult->_multiple );
        if ( itemcount == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "item id=[{}] count = 0!", kfelementobject->_config_id );
            return false;
        }

        // 添加道具调用脚本
        CallItemLuaFunction( player, KFItemEnum::AddFunction, kfsetting, itemcount );

        // 添加道具
        if ( kfsetting->_overlay_type == KFItemEnum::OverlayByTime )
        {
            // 计算时间
            auto itemtime = kfelementobject->CalcValue( kfparent->_data_setting, __STRING__( time ), kfresult->_multiple );
            if ( itemtime == 0u )
            {
                __LOG_ERROR_FUNCTION__( function, line, "time item id=[{}] count = 0", kfelementobject->_config_id );
                return false;
            }

            AddOverlayTimeItem( player, kfparent, kfresult, kfsetting, itemcount, itemtime );
        }
        else if ( kfsetting->_overlay_type == KFItemEnum::OverlayByCount )
        {
            // 按数量叠加道具
            if ( kfsetting->IsOverlay() )
            {
                AddOverlayCountItem( player, kfparent, kfresult, kfsetting, itemcount );
            }
            else
            {
                AddNotOverlayItem( player, kfparent, kfresult, kfsetting, itemcount );
            }
        }

        return true;
    }

    void KFItemModule::AddOverlayTimeItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count, uint32 time )
    {
        std::list< KFData* > finditem;
        kfparent->Find( kfparent->_data_setting->_config_key_name, kfsetting->_id, finditem, false );

        KFData* kfitem = nullptr;
        if ( !finditem.empty() )
        {
            kfitem = finditem.front();
            player->UpdateData( kfitem, __STRING__( time ), KFEnum::Add, count * time );
        }
        else
        {
            kfitem = AddNewItemData( player, kfparent, kfsetting, count, time );
        }

        kfresult->AddResult( kfsetting->_id, kfitem );
    }

    void KFItemModule::AddOverlayCountItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count )
    {
        // 查找相同道具的id
        auto totaladdcount = 0u;
        for ( auto kfitem = kfparent->First(); kfitem != nullptr; kfitem = kfparent->Next() )
        {
            auto itemid = kfitem->Get<uint32>( kfitem->_data_setting->_config_key_name );
            if ( itemid != kfsetting->_id )
            {
                continue;
            }

            auto oldcount = kfitem->Get( __STRING__( count ) );
            auto addcount = CalcItemAddCount( count, oldcount, kfsetting->_overlay_count );
            if ( addcount == 0u )
            {
                continue;
            }

            // 更新数量
            player->UpdateData( kfitem, __STRING__( count ), KFEnum::Add, addcount );
            count -= addcount;
            totaladdcount += addcount;
            if ( count == 0u )
            {
                break;
            }
        }

        // 显示添加数量
        if ( totaladdcount != 0u )
        {
            kfresult->AddResult( kfsetting->_id, kfparent->_data_setting->_name, __STRING__( count ), totaladdcount );
        }

        // 添加完成, 直接返回
        if ( count == 0u )
        {
            return;
        }

        // 添加新物品
        do
        {
            auto kfitem = AddNewItemData( player, kfparent, kfsetting, count, 0u );
            kfresult->AddResult( kfsetting->_id, kfitem->_data_setting->_name, __STRING__( count ), kfitem->Get<uint32>( __STRING__( count ) ) );
        } while ( count > 0u );
    }

    void KFItemModule::AddNotOverlayItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count )
    {
        // 添加新物品
        do
        {
            auto kfitem = AddNewItemData( player, kfparent, kfsetting, count, 0u );
            kfresult->AddResult( kfsetting->_id, kfitem );
        } while ( count > 0u );
    }
    KFData* KFItemModule::AddNewItemData( KFEntity* player, KFData* kfparent, const KFItemSetting* kfsetting, uint32& count, uint32 time )
    {
        auto addcount = __MIN__( count, kfsetting->_overlay_count );

        auto kfitem = player->CreateData( kfparent );

        // count
        kfitem->Set( __STRING__( count ), addcount );

        // id
        kfitem->Set( kfparent->_data_setting->_config_key_name, kfsetting->_id );

        // time
        if ( time != 0u )
        {
            kfitem->Set( __STRING__( time ), KFGlobal::Instance()->_real_time + time * count );
        }

        // 初始化数据
        auto kffunction = _init_item_function.Find( kfsetting->_type );
        if ( kffunction != nullptr )
        {
            kffunction->_function( player, kfitem, kfsetting );
        }

        // uuid
        auto uuid = KFGlobal::Instance()->STMakeUUID( __STRING__( item ) );

        // 添加新的物品
        count -= addcount;
        player->AddData( kfparent, uuid, kfitem );
        return kfitem;
    }

    __KF_UPDATE_DATA_FUNCTION__( KFItemModule::OnItemCountUpdateCallBack )
    {
        if ( newvalue > _invalid_int )
        {
            return;
        }

        // 数量为0, 删除道具
        player->RemoveData( kfdata->GetParent()->GetParent(), key );
    }

    bool KFItemModule::CallItemLuaFunction( KFEntity* player, uint32 functiontype, const KFItemSetting* kfsetting, uint32 itemcount )
    {
        if ( kfsetting->_lua_file.empty() )
        {
            return false;
        }

        auto& luafunction = kfsetting->GetFunction( functiontype );
        if ( luafunction.empty() )
        {
            return false;
        }

        auto playerid = player->GetKeyID();
        auto result = _kf_lua->Call( kfsetting->_lua_file, luafunction, playerid, kfsetting->_id, itemcount );
        return result != 0u;
    }

    __KF_CHECK_REMOVE_ELEMENT_FUNCTION__( KFItemModule::CheckRemoveItemElement )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return false;
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return false;
        }

        // 判断数量
        auto itemcount = kfelementobject->CalcValue( kfparent->_data_setting, __STRING__( count ), multiple );
        if ( itemcount == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "item id=[{}] count = 0!", kfelementobject->_config_id );
            return false;
        }

        auto kfsetting = KFItemConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "item id=[{}] setting = nullptr!", kfelementobject->_config_id );
            return false;
        }

        // 累计数量
        auto totalcount = 0u;
        for ( auto kfitem = kfparent->First(); kfitem != nullptr; kfitem = kfparent->Next() )
        {
            auto itemid = kfitem->Get( kfparent->_data_setting->_config_key_name );
            if ( itemid != kfsetting->_id )
            {
                continue;
            }

            totalcount += kfitem->Get<uint32>( __STRING__( count ) );
            if ( totalcount >= itemcount )
            {
                return true;
            }
        }

        return false;
    }

    __KF_REMOVE_ELEMENT_FUNCTION__( KFItemModule::RemoveItemElement )
    {
        auto kfelement = kfresult->_element;
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return false;
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return false;
        }

        auto itemcount = kfelementobject->CalcValue( kfparent->_data_setting, __STRING__( count ), kfresult->_multiple );
        if ( itemcount == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "item id=[{}] count = 0!", kfelementobject->_config_id );
            return false;
        }

        auto kfsetting = KFItemConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            return false;
        }

        std::list< KFData* > finditem;
        kfparent->Find( kfparent->_data_setting->_config_key_name, kfelementobject->_config_id, finditem, true );
        for ( auto kfitem : finditem )
        {
            auto removecount = __MIN__( itemcount, kfitem->Get<uint32>( __STRING__( count ) ) );
            player->UpdateData( kfitem, __STRING__( count ), KFEnum::Dec, removecount );
            itemcount -= removecount;
            kfresult->AddResult( kfsetting->_id, kfitem->_data_setting->_name, __STRING__( count ), removecount );
            if ( itemcount == _invalid_int )
            {
                break;
            }
        }

        return true;
    }

    __KF_ADD_DATA_FUNCTION__( KFItemModule::OnAddItemCallBack )
    {
        auto itemtime = kfdata->Get< uint64 >();
        if ( itemtime != 0u )
        {
            StartItemCheckTimer( player, kfdata );
        }
    }

    __KF_UPDATE_DATA_FUNCTION__( KFItemModule::OnItemTimeUpdateCallBack )
    {
        if ( newvalue == 0u )
        {
            // 如果变成永久道具, 取消定时器
            __UN_TIMER_2__( player->GetKeyID(), key );
        }
        else
        {
            // 更新定时器
            StartItemCheckTimer( player, kfdata->GetParent() );
        }
    }

    __KF_ENTER_PLAYER_FUNCTION__( KFItemModule::OnEnterItemModule )
    {
        auto kfitemrecord = player->Find( __STRING__( item ) );
        for ( auto kfitem = kfitemrecord->First(); kfitem != nullptr; kfitem = kfitemrecord->Next() )
        {
            auto time = kfitem->Get<uint64>( __STRING__( time ) );
            if ( time != 0u )
            {
                StartItemCheckTimer( player, kfitem );
            }
        }
    }

    __KF_LEAVE_PLAYER_FUNCTION__( KFItemModule::OnLeaveItemModule )
    {
        __UN_TIMER_1__( player->GetKeyID() );
    }

    void KFItemModule::StartItemCheckTimer( KFEntity* player, KFData* kfitem )
    {
        auto intervaltime = 1000u;
        auto nowtime = KFGlobal::Instance()->_real_time;
        auto itemtime = kfitem->Get<uint64>( __STRING__( time ) );
        if ( itemtime > nowtime )
        {
            intervaltime = ( itemtime - nowtime + 1 ) * 1000;
        }

        __LIMIT_TIMER_2__( player->GetKeyID(), kfitem->GetKeyID(), intervaltime, 1, &KFItemModule::OnTimerRemoveTimeItem );
    }

    __KF_TIMER_FUNCTION__( KFItemModule::OnTimerRemoveTimeItem )
    {
        auto player = _kf_player->FindPlayer( objectid );
        if ( player == nullptr )
        {
            return;
        }

        player->RemoveData( __STRING__( item ), subid );
    }

    __KF_MESSAGE_FUNCTION__( KFItemModule::HandleRemoveItemReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgRemoveItemReq );

        __LOG_INFO__( "player=[{}] remove item=[{}:{}]", playerid, kfmsg.sourcename(), kfmsg.uuid() );

        if ( kfmsg.uuid() == 0u )
        {
            player->CleanData( __STRING__( item ) );
        }
        else
        {
            player->RemoveData( __STRING__( item ), kfmsg.uuid() );
        }
    }

    __KF_REMOVE_DATA_FUNCTION__( KFItemModule::OnRemoveItemCallBack )
    {
        auto itemid = kfdata->Get( kfdata->_data_setting->_config_key_name );
        auto kfsetting = KFItemConfig::Instance()->FindSetting( itemid );
        if ( kfsetting == nullptr )
        {
            return;
        }

        auto count = kfdata->Get<uint32>( __STRING__( count ) );
        CallItemLuaFunction( player, KFItemEnum::RemoveFunction, kfsetting, __MAX__( count, 1 ) );
    }

    uint32 KFItemModule::CalcItemAddCount( uint32 sourcecount, uint32 targetcount, uint32 maxcount )
    {
        if ( targetcount >= maxcount )
        {
            return 0u;
        }

        auto canaddcount = maxcount - targetcount;
        return sourcecount <= canaddcount ? sourcecount : canaddcount;
    }
}