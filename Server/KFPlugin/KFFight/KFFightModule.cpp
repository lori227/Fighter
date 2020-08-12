#include "KFFightModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFFightModule::BeforeRun()
    {
        auto timeid = KFGlobal::Instance()->GetUInt32( "scoreresettime" );
        __REGISTER_RESET__( timeid, &KFFightModule::OnResetFightScore );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_UPDATE_SOCRE_REQ, &KFFightModule::HandleUpdateScoreReq );
    }

    void KFFightModule::ShutDown()
    {
        __UN_RESET__();
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_UPDATE_SOCRE_REQ );
    }

    __KF_RESET_FUNCTION__( KFFightModule::OnResetFightScore )
    {
        auto kfscorerecord = player->Find( __STRING__( score ) );
        if ( kfscorerecord == nullptr )
        {
            return;
        }

        for ( auto kfsocre = kfscorerecord->First(); kfsocre != nullptr; kfsocre = kfscorerecord->Next() )
        {
            auto todayscore = kfsocre->Get( __STRING__( today ) );

            player->UpdateData( kfsocre, __STRING__( today ), KFEnum::Set, 0u );
            player->UpdateData( kfsocre, __STRING__( yestoday ), KFEnum::Set, todayscore );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFFightModule::HandleUpdateScoreReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgUpdateScoreReq );

        auto kfscorerecord = player->Find( __STRING__( score ) );
        if ( kfscorerecord == nullptr )
        {
            return;
        }

        player->UpdateData( kfscorerecord, kfmsg.id(), __STRING__( today ), KFEnum::Greater, kfmsg.socre() );
        player->UpdateData( kfscorerecord, kfmsg.id(), __STRING__( ever ), KFEnum::Greater, kfmsg.socre() );
    }
}