#ifndef __KF_TASK_REFRESH_DATA_H__
#define __KF_TASK_REFRESH_DATA_H__

#include "KFConfig/KFTaskConfig.hpp"

namespace KFrame
{
    class KFTaskSettingList
    {
    public:
        std::vector<std::shared_ptr<KFTaskSetting>> _task_list;
    };
}



#endif