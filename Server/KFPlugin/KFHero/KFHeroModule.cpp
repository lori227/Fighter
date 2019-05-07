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
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_parent->_data );
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_parent->_data );
        }

        auto kfsetting = _kf_hero_config->FindHeroSetting( kfelementobject->_config_id );
        if ( kfsetting == nullptr )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no setting!", kfelement->_parent->_data );
        }

        // todo: 临时代码, 不重复添加英雄
        auto kfchild = kfparent->FindData( kfelementobject->_config_id );
        if ( kfchild != nullptr )
        {
            return;
        }

        kfchild = _kf_kernel->CreateObject( kfparent->GetDataSetting() );
        for ( auto& iter : kfelementobject->_values._objects )
        {
            auto& name = iter.first;
            auto value = iter.second->CalcUInt64( multiple );
            kfchild->OperateValue( name, kfelementobject->_operate, value );
        }

        player->AddData( kfparent, kfelementobject->_config_id, kfchild );
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