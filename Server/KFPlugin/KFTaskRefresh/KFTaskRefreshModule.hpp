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
#include "KFTask/KFTaskInterface.h"
#include "KFConfig/KFWeightConfig.hpp"

namespace KFrame {
    class KFTaskRefreshModule : public KFTaskRefreshInterface {
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
        __KF_RESET_FUNCTION__(OnResetTaskRefresh);

        // 刷新任务
        std::shared_ptr<KFTaskSetting> TaskRefresh(EntityPtr player, UInt32Set& exclude_quality_list, UInt32Set& exclude_type_list);

        // 删除任务回调
        __KF_REMOVE_DATA_FUNCTION__( OnRemoveTask );

    protected:
        // 玩家组件
        std::shared_ptr<KFComponent> _component = nullptr;

        // 任务刷新数据
        KFHashMap<uint32, KFTaskTypeList> _quality_task_list;
    };
}


#endif