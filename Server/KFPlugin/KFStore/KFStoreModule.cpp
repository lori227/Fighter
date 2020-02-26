#include "KFStoreModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFStoreModule::BeforeRun()
    {
        __REGISTER_MESSAGE__( KFMsg::MSG_BUY_STORE_REQ, &KFStoreModule::HandleBuyStoreReq );
        __REGISTER_MESSAGE__( KFMsg::MSG_QUERY_STORE_REQ, &KFStoreModule::HandleQueryStoreReq );
    }

    void KFStoreModule::BeforeShut()
    {
        //////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_BUY_STORE_REQ );
        __UN_MESSAGE__( KFMsg::MSG_QUERY_STORE_REQ );
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFStoreModule::HandleQueryStoreReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgQueryStoreReq );

        // 版本号一直就不更新了
        auto version = KFStoreConfig::Instance()->GetVersion();
        if ( kfmsg.version() == version )
        {
            return;
        }

        KFMsg::MsgQueryStoreAck ack;
        ack.set_version( version );
        //ack.set_data( _kf_store_config->_store_xml->Data(), _kf_store_config->_store_xml->Size() );
        _kf_player->SendToClient( player, KFMsg::MSG_QUERY_STORE_ACK, &ack );
    }

    __KF_MESSAGE_FUNCTION__( KFStoreModule::HandleBuyStoreReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgBuyStoreReq );

        auto result = ProcessBuyStore( player, kfmsg.buytype(), kfmsg.id(), kfmsg.count() );
        _kf_display->SendToClient( player, result, kfmsg.id() );
    }

    uint32 KFStoreModule::ProcessBuyStore( KFEntity* player, const std::string& buytype, uint32 id, uint32 count )
    {
        auto kfsetting = KFStoreConfig::Instance()->FindSetting( id );
        if ( kfsetting == nullptr )
        {
            return KFMsg::StoreNotFind;
        }

        if ( count == 0 || count > kfsetting->_buy_max_count )
        {
            return KFMsg::StoreBuyCountError;
        }

        // 判断是否限购
        if ( CheckBuyLimit( player, kfsetting, count ) )
        {
            return KFMsg::StoreOutOfLimits;
        }

        // 获得商品价格
        auto kfagents = kfsetting->FindCostElements( buytype, KFGlobal::Instance()->_real_time );
        if ( kfagents == nullptr )
        {
            return KFMsg::StoreBuyTypeError;
        }

        // 检测扣除物品是否足够
        auto& dataname = player->RemoveElement( kfagents, count, __STRING__( store ), kfsetting->_id, __FUNC_LINE__ );
        if ( !dataname.empty() )
        {
            return KFMsg::StoreLackCost;
        }

        // 发送道具
        player->AddElement( &kfsetting->_buy_elements, count, __STRING__( store ), kfsetting->_id, __FUNC_LINE__ );

        // 记录购买次数
        SaveBuyLimit( player, kfsetting, count );
        return KFMsg::StoreBuyOK;
    }

    bool KFStoreModule::CheckBuyLimit( KFEntity* player, const KFStoreSetting* kfsetting, uint32 count )
    {
        // 不限制
        if ( kfsetting->_buy_limit_type.empty() )
        {
            return false;
        }

        auto kfstore = player->Find( kfsetting->_buy_limit_type, kfsetting->_id );
        if ( kfstore == nullptr )
        {
            return false;
        }

        // 比较购买次数
        auto datacount = kfstore->Get( __STRING__( count ) );
        if ( ( datacount + count ) <= kfsetting->_buy_limit_count )
        {
            return false;
        }

        return true;
    }

    void KFStoreModule::SaveBuyLimit( KFEntity* player, const KFStoreSetting* kfsetting, uint32 count )
    {
        // 不限制
        if ( kfsetting->_buy_limit_type.empty() )
        {
            return;
        }

        // 更新数量
        player->UpdateData( kfsetting->_buy_limit_type, kfsetting->_id, __STRING__( count ), KFEnum::Add, count );
    }
}
