#ifndef __KF_TASK_REFRESH_MOUDLE_H__
#define __KF_TASK_REFRESH_MOUDLE_H__

/************************************************************************
//    @Moudle			:    英雄包裹系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2017-4-14
************************************************************************/
#include "KFrameEx.h"
#include "KFTaskRefreshInterface.h"
#include "KFProtocol/KFProtocol.h"
#include "KFTaskRefreshData.hpp"
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFReset/KFResetInterface.h"

namespace KFrame
{
    class KFTaskRefreshModule : public KFTaskRefreshInterface
    {
    public:
        KFTaskRefreshModule() = default;
        ~KFTaskRefreshModule() = default;

        // 加载
        virtual void AfterLoad();

        // 逻辑
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
    protected:
        __KF_RESET_FUNCTION__( OnResetTaskRefresh );

    protected:
        // 玩家组件
        std::shared_ptr<KFComponent> _component = nullptr;

        // 任务刷新数据
    };
}



#endif