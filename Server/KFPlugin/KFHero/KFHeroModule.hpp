#ifndef __KF_HERO_MOUDLE_H__
#define __KF_HERO_MOUDLE_H__

/************************************************************************
//    @Moudle			:    英雄包裹系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2017-4-14
************************************************************************/
#include "KFrameEx.h"
#include "KFHeroInterface.h"
#include "KFProtocol/KFProtocol.h"
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFZConfig/KFHeroConfig.hpp"
#include "KFZConfig/KFFootConfig.hpp"
#include "KFZConfig/KFEffectConfig.hpp"

namespace KFrame
{
    class KFHeroModule : public KFHeroInterface
    {
    public:
        KFHeroModule() = default;
        ~KFHeroModule() = default;

        // 逻辑
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
    protected:
        // 添加英雄回调
        __KF_ADD_DATA_FUNCTION__( OnAddHero );

        // 添加英雄
        __KF_ADD_ELEMENT_FUNCTION__( AddHeroElement );

        // 添加特效
        __KF_ADD_ELEMENT_FUNCTION__( AddEffectElement );

        // 添加脚印
        __KF_ADD_ELEMENT_FUNCTION__( AddFootElement );
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 选择出战英雄
        __KF_MESSAGE_FUNCTION__( HandleFighterHeroReq );

        // 选择特效
        __KF_MESSAGE_FUNCTION__( HandleEffectUseReq );

        // 选择脚印
        __KF_MESSAGE_FUNCTION__( HandleFootUseReq );
    protected:
        KFComponent* _kf_component = nullptr;
    };
}



#endif