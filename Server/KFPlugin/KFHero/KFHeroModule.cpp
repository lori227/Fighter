#include "KFHeroModule.hpp"

namespace KFrame
{
    void KFHeroModule::BeforeRun()
    {
        _kf_component = _kf_kernel->FindComponent( __STRING__( player ) );

        __REGISTER_ADD_ELEMENT__( __STRING__( hero ), &KFHeroModule::AddHeroElement );
        __REGISTER_ADD_DATA_1__( __STRING__( hero ), &KFHeroModule::OnAddHero );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ, &KFHeroModule::HandleFighterHeroReq );
    }

    void KFHeroModule::BeforeShut()
    {
        __UN_ADD_DATA_1__( __STRING__( hero ) );
        __UN_ADD_ELEMENT__( __STRING__( hero ) );
        //////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_FIGHTER_HERO_REQ );
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

        auto kfsetting = KFHeroConfig::Instance()->FindSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "hero id=[{}] no setting!", kfelementobject->_config_id );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        // todo: 临时代码, 不重复添加英雄
        auto kfhero = kfparent->Find( kfelementobject->_config_id );
        if ( kfhero != nullptr )
        {
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        kfhero = _kf_kernel->CreateObject( kfparent->_data_setting );
        player->SetElementToData( kfelementobject, kfhero, multiple );

        player->AddData( kfparent, kfelementobject->_config_id, kfhero );
        return std::make_tuple( KFDataDefine::Show_Element, kfhero );
    }

    __KF_ADD_DATA_FUNCTION__( KFHeroModule::OnAddHero )
    {
        auto herocount = kfparent->Size();
        player->UpdateData( __STRING__( herocount ), KFEnum::Set, herocount );
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
}