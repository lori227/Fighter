#include "KFHeroModule.hpp"
#include "KFHeroConfig.hpp"

namespace KFrame
{
    void KFHeroModule::InitModule()
    {
        __KF_ADD_CONFIG__( _kf_hero_config, true );
    }

    void KFHeroModule::BeforeRun()
    {
        _kf_component = _kf_kernel->FindComponent( __KF_STRING__( player ) );
        _kf_component->RegisterAddElementFunction( __KF_STRING__( hero ), this, &KFHeroModule::AddHeroElement );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ, &KFHeroModule::HandleFighterHeroReq );
    }

    void KFHeroModule::BeforeShut()
    {
        __KF_REMOVE_CONFIG__( _kf_hero_config );
        _kf_component->UnRegisterAddElementFunction( __KF_STRING__( hero ) );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UNREGISTER_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_ADD_ELEMENT_FUNCTION__( KFHeroModule::AddHeroElement )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        auto kfsetting = _kf_hero_config->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        // todo: 临时代码, 不重复添加英雄
        auto kfhero = kfparent->FindData( kfelementobject->_config_id );
        if ( kfhero != nullptr )
        {
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        kfhero = _kf_kernel->CreateObject( kfparent->GetDataSetting() );
        player->SetElementToData( kfelementobject, kfhero, multiple );

        player->AddData( kfparent, kfelementobject->_config_id, kfhero );
        return std::make_tuple( KFDataDefine::Show_Element, kfhero );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFHeroModule::HandleFighterHeroReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgFighterHeroReq );

        // 判断是否存在英雄
        auto kfobject = player->GetData();
        auto kfhero = kfobject->FindData( __KF_STRING__( hero ), kfmsg.heroid() );
        if ( kfhero == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::HeroNotExist );
        }

        player->UpdateData( __KF_STRING__( heroid ), KFEnum::Set, kfmsg.heroid() );
    }
}