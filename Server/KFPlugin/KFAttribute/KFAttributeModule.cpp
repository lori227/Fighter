﻿#include "KFAttributeModule.hpp"

namespace KFrame
{
    void KFAttributeModule::BeforeRun()
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_SET_NAME_REQ, &KFAttributeModule::HandleSetNameReq );
        __REGISTER_MESSAGE__( KFMsg::MSG_SET_SEX_REQ, &KFAttributeModule::HandleSetSexReq );
        __REGISTER_MESSAGE__( KFMsg::S2S_SET_PLAYERNAME_TO_GAME_ACK, &KFAttributeModule::HandleSetPlayerNameToGameAck );
    }

    void KFAttributeModule::BeforeShut()
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        __UNREGISTER_MESSAGE__( KFMsg::MSG_SET_NAME_REQ );
        __UNREGISTER_MESSAGE__( KFMsg::MSG_SET_SEX_REQ );
        __UNREGISTER_MESSAGE__( KFMsg::S2S_SET_PLAYERNAME_TO_GAME_ACK );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint32 KFAttributeModule::CheckNameValid( const std::string& name, uint32 maxlength )
    {
        if ( name.size() > maxlength )
        {
            return KFMsg::NameLengthError;
        }

        auto ok = _kf_filter->CheckFilter( name );
        if ( ok )
        {
            return KFMsg::NameFilterError;
        }

        return KFMsg::Ok;
    }

    __KF_MESSAGE_FUNCTION__( KFAttributeModule::HandleSetNameReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgSetNameReq );

        if ( kfmsg.name().empty() )
        {
            return _kf_display->SendToClient( player, KFMsg::NameEmpty );
        }

        auto kfobject = player->GetData();
        auto kfname = kfobject->FindData( __KF_STRING__( basic ), __KF_STRING__( name ) );
        auto name = kfname->GetValue<std::string>();
        if ( !name.empty() )
        {
            return _kf_display->SendToClient( player, KFMsg::NameAlreadySet );
        }

        // 检查名字的有效性
        auto result = CheckNameValid( kfmsg.name(), kfname->_data_setting->_logic_value );
        if ( result != KFMsg::Ok )
        {
            return _kf_display->SendToClient( player, result );
        }

        // 修改名字
        KFMsg::S2SSetPlayerNameToDataReq req;
        req.set_playerid( playerid );
        req.set_oldname( name );
        req.set_newname( kfmsg.name() );
        req.set_costdata( _invalid_str );
        auto ok = _kf_route->SendToRand( playerid, __KF_STRING__( public ), KFMsg::S2S_SET_PLAYERNAME_TO_DATA_REQ, &req, false );
        if ( !ok )
        {
            _kf_display->SendToClient( player, KFMsg::PublicServerBusy );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFAttributeModule::HandleSetPlayerNameToGameAck )
    {
        __PROTO_PARSE__( KFMsg::S2SSetPlayerNameToGameAck );

        auto player = _kf_player->FindPlayer( kfmsg.playerid() );
        if ( player == nullptr )
        {
            return __LOG_ERROR__( "player[{}] set name[{}] item[{}] failed!", kfmsg.playerid(), kfmsg.name(), kfmsg.costdata() );
        }

        _kf_display->SendToClient( player, kfmsg.result(), kfmsg.name() );
        if ( kfmsg.result() != KFMsg::NameSetOk )
        {
            return;
        }

        player->UpdateData( __KF_STRING__( basic ), __KF_STRING__( name ), kfmsg.name() );
        if ( kfmsg.costdata() != _invalid_str )
        {
            KFElements kfelements;
            auto ok = kfelements.Parse( kfmsg.costdata(), __FUNC_LINE__ );
            if ( ok )
            {
                player->RemoveElement( &kfelements, __FUNC_LINE__ );
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_MESSAGE_FUNCTION__( KFAttributeModule::HandleSetSexReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgSetSexReq );

        _kf_display->SendToClient( player, KFMsg::SexSetOK );
        player->UpdateData( __KF_STRING__( basic ), __KF_STRING__( sex ), KFEnum::Set, kfmsg.sex() );
    }


}