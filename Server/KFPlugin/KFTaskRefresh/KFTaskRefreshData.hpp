#ifndef __KF_TASK_REFRESH_DATA_H__
#define __KF_TASK_REFRESH_DATA_H__

#include "KFConfig/KFTaskConfig.hpp"

namespace KFrame {
    class KFTaskSettingList {
    public:
        std::shared_ptr<KFTaskSetting> RandTask() {
            auto task_count = _task_list.size();
            if (task_count == 0u) {
                return nullptr;
            }

            auto index = KFGlobal::Instance()->RandRatio(task_count);
            return _task_list[index];
        }

    public:
        // 任务列表
        std::vector<std::shared_ptr<KFTaskSetting>> _task_list;
    };

    class KFTaskTypeList {
    public:
        std::shared_ptr<KFTaskSetting> RandTaskSetting(UInt32Set& exclude_list) {
            UInt32Vector type_list;
            for (auto& iter : _type_task_list._objects) {
                if (exclude_list.count(iter.first) == 0) {
                    type_list.push_back(iter.first);
                }
            }

            auto type_count = type_list.size();
            if (type_count == 0) {
                __LOG_ERROR__("task quality=[{}] empty", _quality);
                return nullptr;
            }

            auto index = KFGlobal::Instance()->RandRatio(type_count);
            auto type = type_list[index];
            auto type_setting_list = _type_task_list.Find(type);
            if (type_setting_list == nullptr) {
                __LOG_ERROR__("task quality=[{}] type=[{}] empty", _quality, type);
                return nullptr;
            }

            return type_setting_list->RandTask();
        }

    public:
        uint32 _quality = 0u;

        // 类型对应的任务列表
        KFHashMap<uint32, KFTaskSettingList> _type_task_list;
    };
}


#endif