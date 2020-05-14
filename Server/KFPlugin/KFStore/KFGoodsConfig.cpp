﻿#include "KFGoodsConfig.hpp"

namespace KFrame
{
    void KFGoodsConfig::ReadSetting( KFNode& xmlnode, KFGoodsSetting* kfsetting )
    {
        kfsetting->_store_id = xmlnode.GetUInt32( "StoreId" );
        kfsetting->_goods_data._str_parse = xmlnode.GetString( "Item" );
        kfsetting->_buy_price._str_parse = xmlnode.GetString( "Price" );
        kfsetting->_discount_price._str_parse = xmlnode.GetString( "Discount" );
        kfsetting->_start_buy_time = KFDate::FromString( xmlnode.GetString( "BeginTime" ) );
        kfsetting->_end_buy_time = KFDate::FromString( xmlnode.GetString( "EndTime" ) );
        kfsetting->_start_discount_time = KFDate::FromString( xmlnode.GetString( "DiscountBeginTime" ) );
        kfsetting->_end_discount_time = KFDate::FromString( xmlnode.GetString( "DiscountEndTime" ) );
        kfsetting->_limit_buy_time_id = xmlnode.GetUInt32( "LimitTimeId" );
        kfsetting->_limit_buy_count = xmlnode.GetUInt32( "LimitCount" );
        kfsetting->_min_buy_count = xmlnode.GetUInt32( "MinBuyCount" );
        kfsetting->_max_buy_count = xmlnode.GetUInt32( "MaxBuyCount" );
        kfsetting->_group_id = xmlnode.GetUInt32( "GroupId" );
        kfsetting->_group_weight = xmlnode.GetUInt32( "GroupWeight" );
        kfsetting->_refresh_count = xmlnode.GetUInt32( "RefreshCount" );
    }

    void KFGoodsConfig::LoadAllComplete()
    {
        _goods_group_weight_list.Clear();

        for ( auto& iter : _settings._objects )
        {
            auto kfgoodssetting = iter.second;

            KFElementConfig::Instance()->ParseElement( kfgoodssetting->_goods_data, __FILE__, kfgoodssetting->_id );
            KFElementConfig::Instance()->ParseElement( kfgoodssetting->_buy_price, __FILE__, kfgoodssetting->_id );
            KFElementConfig::Instance()->ParseElement( kfgoodssetting->_discount_price, __FILE__, kfgoodssetting->_id );

            if ( kfgoodssetting->_group_id != 0u )
            {
                auto goodsgroupweight = _goods_group_weight_list.Create( kfgoodssetting->_group_id );
                auto goodsweightdata = goodsgroupweight->Create( kfgoodssetting->_id, kfgoodssetting->_group_weight );
                goodsweightdata->_refresh_count = kfgoodssetting->_refresh_count;
            }
        }
    }

    const KFGoodsGroupWeight* KFGoodsConfig::RandGroupGoods( uint32 groupid, UInt32Set& excludelist )
    {
        auto goodsgroupweightlist = _goods_group_weight_list.Find( groupid );
        if ( goodsgroupweightlist == nullptr )
        {
            return nullptr;
        }

        if ( excludelist.empty() )
        {
            return goodsgroupweightlist->Rand();
        }

        return goodsgroupweightlist->Rand( excludelist, true );
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFGoodsSetting::CheckInBuyTime( uint64 nowtime ) const
    {
        if ( _start_buy_time == _invalid_int || _end_buy_time == _invalid_int )
        {
            return true;
        }

        return KFDate::CheckInTime( _start_buy_time, _end_buy_time, nowtime );
    }

    bool KFGoodsSetting::CheckInDiscountTime( uint64 nowtime ) const
    {
        if ( _start_discount_time == _invalid_int || _end_discount_time == _invalid_int )
        {
            return true;
        }

        return KFDate::CheckInTime( _start_discount_time, _end_discount_time, nowtime );
    }

    bool KFGoodsSetting::IsLimitBuy() const
    {
        return _limit_buy_count > 0u;
    }

    const KFElements* KFGoodsSetting::CalcBuyPrice( uint64 nowtime ) const
    {
        if ( CheckInDiscountTime( nowtime ) )
        {
            return &_discount_price;
        }

        return &_buy_price;
    }
}