#include "KFTaskRefreshModule.hpp"

namespace KFrame {
    void KFTaskRefreshModule::BeforeRun() {
        _component = _kf_kernel->FindComponent(__STRING__(player));

        __REGISTER_RESET__(__STRING__(taskrefresh), &KFTaskRefreshModule::OnResetTaskRefresh);
        __REGISTER_REMOVE_DATA_1__(__STRING__(task), &KFTaskRefreshModule::OnRemoveTask);
    }

    void KFTaskRefreshModule::BeforeShut() {
        __UN_RESET__(__STRING__(taskrefresh));
        __UN_REMOVE_DATA_1__(__STRING__(task));
    }

    void KFTaskRefreshModule::AfterLoad() {
        _quality_task_list.Clear();
        for (auto& iter : KFTaskConfig::Instance()->_setting_list._objects) {
            auto task_setting = iter.second;
            auto quality_task_data = _quality_task_list.Create(task_setting->_quality);
            quality_task_data->_quality = task_setting->_quality;
            auto type_task_data = quality_task_data->_type_task_list.Create(task_setting->_type);
            type_task_data->_task_list.push_back(task_setting);
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_RESET_FUNCTION__(KFTaskRefreshModule::OnResetTaskRefresh) {
        auto task_record = player->Find(__STRING__(task));
        player->ClearRecord(task_record, false);

        // 刷新任务的数量
        static auto _refresh_task_count_constant = KFGlobal::Instance()->FindConstant(__STRING__(refreshtaskcount));
        static auto _no_repeat_quality_constant = KFGlobal::Instance()->FindConstant(__STRING__(norepeatquality));

        UInt32Set exclude_type_list;
        UInt32Set exclude_quality_list;
        for (auto i = 0u; i < _refresh_task_count_constant->_uint32_value; ++i) {
            auto task_setting = TaskRefresh(player, exclude_quality_list, exclude_type_list);
            if (task_setting != nullptr) {
                exclude_type_list.insert(task_setting->_type);
                if (task_setting->_quality >= _no_repeat_quality_constant->_uint32_value) {
                    exclude_quality_list.insert(task_setting->_quality);
                }
            }
        }
    }

    std::shared_ptr<KFTaskSetting> KFTaskRefreshModule::TaskRefresh(EntityPtr player, UInt32Set& exclude_quality_list, UInt32Set& exclude_type_list) {
        static auto _refresh_task_pool_constant = KFGlobal::Instance()->FindConstant(__STRING__(refreshtaskpool));
        auto weight_setting = KFWeightConfig::Instance()->FindSetting(_refresh_task_pool_constant->_uint32_value);
        if (weight_setting == nullptr) {
            __LOG_ERROR__("weight pool=[{}] can't find setting", _refresh_task_pool_constant->_uint32_value);
            return nullptr;
        }

        auto weight_data = weight_setting->_weight.RandExcludeList(exclude_quality_list);
        if (weight_data == nullptr) {
            __LOG_ERROR__("weight pool=[{}] can't rand value", _refresh_task_pool_constant->_uint32_value);
            return nullptr;
        }

        auto quality_data_list = _quality_task_list.Find(weight_data->_value);
        if (quality_data_list == nullptr) {
            __LOG_ERROR__("task quality=[{}] no setting", _refresh_task_pool_constant->_uint32_value);
            return nullptr;
        }

        auto task_setting = quality_data_list->RandTaskSetting(exclude_type_list);
        if (task_setting == nullptr) {
            return nullptr;
        }

        _kf_task->OpenTask(player, task_setting->_id, KFMsg::ExecuteStatus);
        return task_setting;
    }

    __KF_REMOVE_DATA_FUNCTION__(KFTaskRefreshModule::OnRemoveTask) {
        UInt32Set exclude_type_list;
        UInt32Set exclude_quality_list;
        auto task_record = player->Find(__STRING__(task));
        for (auto task_data = task_record->First(); task_data != nullptr; task_data = task_record->Next()) {
            exclude_type_list.insert(task_data->Get<uint32>(__STRING__(type)));
        }

        TaskRefresh(player, exclude_quality_list, exclude_type_list);
    }

}