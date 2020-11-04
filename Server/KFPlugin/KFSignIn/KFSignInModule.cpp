#include "KFSignInModule.hpp"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    void KFSignInModule::BeforeRun()
    {
        __REGISTER_RESET__( __STRING__( signin ), &KFSignInModule::OnResetSigninData );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::MSG_SEVEN_SIGNIN_REWARD_REQ, &KFSignInModule::HandleReceiveSevenRewardReq );
    }

    void KFSignInModule::ShutDown()
    {
        __UN_RESET__( __STRING__( signin ) );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        __UN_MESSAGE__( KFMsg::MSG_SEVEN_SIGNIN_REWARD_REQ );
    }

    __KF_MESSAGE_FUNCTION__( KFSignInModule::HandleReceiveSevenRewardReq )
    {
        __CLIENT_PROTO_PARSE__( KFMsg::MsgSevenSignInRewardReq );

        auto day = player->Get< uint32 >( __STRING__( sevenday ) );
        if ( day < kfmsg.day() )
        {
            return _kf_display->SendToClient( player, KFMsg::SignInNotDay );
        }

        auto kfsetting = KFSignInConfig::Instance()->FindSetting( kfmsg.day() );
        if ( kfsetting == nullptr )
        {
            return _kf_display->SendToClient( player, KFMsg::SignInCanNotFind );
        }

        auto sevenflag = player->Get< uint32 >( __STRING__( sevenreward ) );
        auto flag = 1u << kfmsg.day();
        if ( KFUtility::HaveBitMask< uint32 >( sevenflag, flag ) )
        {
            return _kf_display->SendToClient( player, KFMsg::SignInRewardAlready );
        }

        // 设置标记
        player->UpdateData( __STRING__( sevenreward ), KFEnum::Or, kfmsg.day() );

        // 添加奖励
        player->AddElement( &kfsetting->_reward, _default_multiple, __STRING__( signin ), kfmsg.day(), __FUNC_LINE__ );

        // 额外的奖励
        if ( KFGlobal::Instance()->RandCheck( KFRandEnum::TenThousand, kfsetting->_probability ) )
        {
            player->AddElement( &kfsetting->_extend, _default_multiple, __STRING__( signin ), kfmsg.day(), __FUNC_LINE__ );
        }

        _kf_display->SendToClient( player, KFMsg::SignInRewardOk );
    }

    __KF_RESET_FUNCTION__( KFSignInModule::OnResetSigninData )
    {
        // 计算签到
        CalcSignin( player );

        // 计算连续签到
        CalcContinuousSignin( player, lastresettime, nowresettime );
    }

    void KFSignInModule::CalcSignin( KFEntity* player )
    {
        // 签到逻辑, 只有到前一天奖励领取了, 才算成功签到
        auto day = player->Get< uint32 >( __STRING__( sevenday ) );
        if ( day > 0u )
        {
            auto sevenflag = player->Get< uint32 >( __STRING__( sevenreward ) );
            auto flag = 1u << day;
            if ( !KFUtility::HaveBitMask< uint32 >( sevenflag, flag ) )
            {
                return;
            }
        }

        player->UpdateData( __STRING__( sevenday ), KFEnum::Add, 1u );
    }

    void KFSignInModule::CalcContinuousSignin( KFEntity* player, uint64 lastresettime, uint64 nowresettime )
    {
        auto kfsignintime = player->Find( __STRING__( signintime ) );

        // 判断连续签到
        auto lastsignintime = kfsignintime->Get();
        if ( lastsignintime == lastresettime )
        {
            player->UpdateData( __STRING__( continuoussignin ), KFEnum::Add, 1u );
        }
        else
        {
            player->UpdateData( __STRING__( continuoussignin ), KFEnum::Set, 1u );
        }

        // 更新本次签到
        player->UpdateData( kfsignintime, KFEnum::Set, nowresettime );
    }
}