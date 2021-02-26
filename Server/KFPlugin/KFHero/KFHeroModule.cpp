#include "KFHeroModule.hpp"

namespace KFrame
{
    void KFHeroModule::BeforeRun()
    {
        _component = _kf_kernel->FindComponent( __STRING__( player ) );

        __REGISTER_ADD_ELEMENT__( __STRING__( hero ), &KFHeroModule::AddHeroElement );
        __REGISTER_ADD_ELEMENT__( __STRING__( effect ), &KFHeroModule::AddEffectElement );
        __REGISTER_ADD_ELEMENT__( __STRING__( foot ), &KFHeroModule::AddFootElement );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_FIGHTER_HERO_REQ, &KFHeroModule::HandleFighterHeroReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_EFFECT_USE_REQ, &KFHeroModule::HandleEffectUseReq );
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_FOOT_USE_REQ, &KFHeroModule::HandleFootUseReq );
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
        if ( !element_result->_element->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", element_result->_element->_data_name );
            return false;
        }

        auto element_object = std::dynamic_pointer_cast<KFElementObject>( element_result->_element );
        if ( element_object->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", element_result->_element->_data_name );
            return false;
        }

        auto setting = KFHeroConfig::Instance()->FindSetting( element_object->_config_id );
        if ( setting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", element_object->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto hero_data = parent_data->Find( element_object->_config_id );
        if ( hero_data != nullptr )
        {
            return false;
        }

        hero_data = player->CreateData( parent_data );
        player->SetElementToData( hero_data, element_object, element_result->_multiple );
        player->AddRecord( parent_data, element_object->_config_id, hero_data );

        return element_result->AddResult( element_object->_config_id, hero_data );
    }

    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddEffectElement )
    {
        if ( !element_result->_element->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", element_result->_element->_data_name );
            return false;
        }

        auto element_object = std::dynamic_pointer_cast<KFElementObject>( element_result->_element );
        if ( element_object->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", element_result->_element->_data_name );
            return false;
        }

        auto setting = KFEffectConfig::Instance()->FindSetting( element_object->_config_id );
        if ( setting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", element_object->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto effect_data = parent_data->Find( element_object->_config_id );
        if ( effect_data != nullptr )
        {
            return false;
        }

        effect_data = player->CreateData( parent_data );
        player->SetElementToData( effect_data, element_object, element_result->_multiple );
        player->AddRecord( parent_data, element_object->_config_id, effect_data );

        return element_result->AddResult( element_object->_config_id, effect_data );
    }

    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddFootElement )
    {
        if ( !element_result->_element->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", element_result->_element->_data_name );
            return false;
        }

        auto kfelementobject = std::dynamic_pointer_cast<KFElementObject>( element_result->_element );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", element_result->_element->_data_name );
            return false;
        }

        auto setting = KFFootConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( setting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return false;
        }

        // todo: 临时代码, 不重复添加英雄
        auto foot_data = parent_data->Find( kfelementobject->_config_id );
        if ( foot_data != nullptr )
        {
            return false;
        }

        foot_data = player->CreateData( parent_data );
        player->SetElementToData( foot_data, kfelementobject, element_result->_multiple );
        player->AddRecord( parent_data, kfelementobject->_config_id, foot_data );

        return element_result->AddResult( kfelementobject->_config_id, foot_data );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleFighterHeroReq, KFMsg::MsgFighterHeroReq )
    {
        // 判断是否存在英雄
        auto kfhero = entity->Find( __STRING__( hero ), kfmsg->heroid() );
        if ( kfhero == nullptr )
        {
            return _kf_display->SendToClient( entity, KFMsg::HeroNotExist );
        }

        entity->UpdateData( __STRING__( heroid ), KFEnum::Set, kfmsg->heroid() );
    }

    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleEffectUseReq, KFMsg::MsgEffectUseReq )
    {
        auto kfeffect = entity->Find( __STRING__( effect ), kfmsg->effectid() );
        if ( kfeffect == nullptr )
        {
            return _kf_display->SendToClient( entity, KFMsg::EffectNotExist );
        }

        entity->UpdateData( __STRING__( effectid ),  KFEnum::Set, kfmsg->effectid() );
    }

    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleFootUseReq, KFMsg::MsgFootUseReq )
    {
        auto kffoot = entity->Find( __STRING__( foot ), kfmsg->footid() );
        if ( kffoot == nullptr )
        {
            return _kf_display->SendToClient( entity, KFMsg::FootNotExist );
        }

        entity->UpdateData( __STRING__( footid ), KFEnum::Set, kfmsg->footid() );
    }
}