#include "KFHeroModule.hpp"

namespace KFrame
{
    void KFHeroModule::BeforeRun()
    {
        _kf_component = _kf_kernel->FindComponent( __STRING__( player ) );

        __REGISTER_ADD_ELEMENT__( __STRING__( hero ), &KFHeroModule::AddHeroElement );
        __REGISTER_ADD_ELEMENT__( __STRING__( effect ), &KFHeroModule::AddEffectElement );
        __REGISTER_ADD_ELEMENT__( __STRING__( foot ), &KFHeroModule::AddFootElement );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ, &KFHeroModule::HandleFighterHeroReq );
        __REGISTER_MESSAGE__( KFMsg::MSG_EFFECT_USE_REQ, &KFHeroModule::HandleEffectUseReq );
        __REGISTER_MESSAGE__( KFMsg::MSG_FOOT_USE_REQ, &KFHeroModule::HandleFootUseReq );
    }

    void KFHeroModule::BeforeShut()
    {
        __UN_ADD_ELEMENT__( __STRING__( hero ) );
        __UN_ADD_ELEMENT__( __STRING__( effect ) );
        __UN_ADD_ELEMENT__( __STRING__( foot ) );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ );
        __UN_MESSAGE__( KFMsg::MSG_EFFECT_USE_REQ );
        __UN_MESSAGE__( KFMsg::MSG_FOOT_USE_REQ );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddHeroElement )
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

        auto kfsetting = KFHeroConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto kfhero = kfparent->Find( kfelementobject->_config_id );
        if ( kfhero != nullptr )
        {
            return false;
        }

        kfhero = player->CreateData( kfparent );
        player->SetElementToData( kfhero, kfelementobject, kfresult->_multiple );
        player->AddRecord( kfparent, kfelementobject->_config_id, kfhero );

        return kfresult->AddResult( kfelementobject->_config_id, kfhero );
    }

    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddEffectElement )
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

        auto kfsetting = KFEffectConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto kfeffect = kfparent->Find( kfelementobject->_config_id );
        if ( kfeffect != nullptr )
        {
            return false;
        }

        kfeffect = player->CreateData( kfparent );
        player->SetElementToData( kfeffect, kfelementobject, kfresult->_multiple );
        player->AddRecord( kfparent, kfelementobject->_config_id, kfeffect );

        return kfresult->AddResult( kfelementobject->_config_id, kfeffect );
    }

    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddFootElement )
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

        auto kfsetting = KFFootConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto kffoot = kfparent->Find( kfelementobject->_config_id );
        if ( kffoot != nullptr )
        {
            return false;
        }

        kffoot = player->CreateData( kfparent );
        player->SetElementToData( kffoot, kfelementobject, kfresult->_multiple );
        player->AddRecord( kfparent, kfelementobject->_config_id, kffoot );

        return kfresult->AddResult( kfelementobject->_config_id, kffoot );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleFighterHeroReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgFighterHeroReq );

        // 判断是否存在英雄
        auto kfhero = player->Find( __STRING__( hero ), kfmsg.heroid() );
        if ( kfhero == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::HeroNotExist );
        }

        player->UpdateData( __STRING__( heroid ), KFEnum::Set, kfmsg.heroid() );
    }

    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleEffectUseReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgEffectUseReq );

        auto kfeffect = player->Find( __STRING__( effect ), kfmsg.effectid() );
        if ( kfeffect == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::EffectNotExist );
        }

        player->UpdateData( __STRING__( effectid ),  KFEnum::Set, kfmsg.effectid() );
    }

    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleFootUseReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgFootUseReq );

        auto kffoot = player->Find( __STRING__( foot ), kfmsg.footid() );
        if ( kffoot == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::FootNotExist );
        }

        player->UpdateData( __STRING__( footid ), KFEnum::Set, kfmsg.footid() );
    }
}