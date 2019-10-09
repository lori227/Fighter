﻿#ifndef __KF_SIGNIN_MODULE_H__
#define __KF_SIGNIN_MODULE_H__

/************************************************************************
//    @Module			:    签到模块
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2018-7-28
************************************************************************/

#include "KFrameEx.h"
#include "KFSignInInterface.h"
#include "KFGame/KFGameInterface.h"
#include "KFOption/KFOptionInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFReset/KFResetInterface.h"
#include "KFSignInConfig.hpp"

namespace KFrame
{
    class KFSignInModule : public KFSignInInterface
    {
    public:
        KFSignInModule() = default;
        ~KFSignInModule() = default;

        virtual void BeforeRun();

        virtual void ShutDown();

    protected:
        // 领取7天签到奖励
        __KF_MESSAGE_FUNCTION__( HandleReceiveSevenRewardReq );

        // 签到逻辑
        __KF_RESET_FUNCTION__( OnResetSigninData );

        // 计算签到天数
        void CalcSignin( KFEntity* player );

        // 计算连续签到
        void CalcContinuousSignin( KFEntity* player, const KFTimeData* timedata, uint64 nowtime );
    };
}



#endif