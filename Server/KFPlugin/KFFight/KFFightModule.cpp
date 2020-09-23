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

            player->UpdateObjectData( kfsocre, __STRING__( today ), KFEnum::Set, 0u );
            player->UpdateObjectData( kfsocre, __STRING__( yesterday ), KFEnum::Set, todayscore );
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

        player->UpdateRecordData( kfscorerecord, kfmsg.id(), __STRING__( today ), KFEnum::Greater, kfmsg.socre() );
        player->UpdateRecordData( kfscorerecord, kfmsg.id(), __STRING__( ever ), KFEnum::Greater, kfmsg.socre() );
    }
}