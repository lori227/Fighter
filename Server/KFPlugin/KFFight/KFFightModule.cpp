#include "KFFightModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFFightModule::BeforeRun()
    {
        __REGISTER_RESET__( __STRING__( score ), &KFFightModule::OnResetFightScore );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMessageEnum::Player, KFMsg::MSG_UPDATE_SOCRE_REQ, &KFFightModule::HandleUpdateScoreReq );
    }

    void KFFightModule::ShutDown()
    {
        __UN_RESET__( __STRING__( score ) );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_UPDATE_SOCRE_REQ );
    }

    __KF_RESET_FUNCTION__( KFFightModule::OnResetFightScore )
    {
        auto score_record = player->Find( __STRING__( score ) );
        if ( score_record == nullptr )
        {
            return;
        }

        for ( auto score_data = score_record->First(); score_data != nullptr; score_data = score_record->Next() )
        {
            auto today_score = score_data->Get( __STRING__( today ) );

            player->UpdateObject( score_data, __STRING__( today ), KFEnum::Set, 0u );
            player->UpdateObject( score_data, __STRING__( yesterday ), KFEnum::Set, today_score );
        }
    }

    __KF_MESSAGE_FUNCTION__( KFFightModule::HandleUpdateScoreReq, KFMsg::MsgUpdateScoreReq )
    {
        auto score_record = player->Find( __STRING__( score ) );
        if ( score_record == nullptr )
        {
            return;
        }

        player->UpdateRecord( score_record, kfmsg->id(), __STRING__( today ), KFEnum::Greater, kfmsg->socre() );
        player->UpdateRecord( score_record, kfmsg->id(), __STRING__( ever ), KFEnum::Greater, kfmsg->socre() );
    }
}