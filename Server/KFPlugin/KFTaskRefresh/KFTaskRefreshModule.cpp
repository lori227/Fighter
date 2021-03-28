#include "KFTaskRefreshModule.hpp"

namespace KFrame
{
    void KFTaskRefreshModule::BeforeRun()
    {
        _component = _kf_kernel->FindComponent( __STRING__( player ) );

        __REGISTER_RESET__( __STRING__( taskrefresh ), &KFTaskRefreshModule::OnResetTaskRefresh );

    }

    void KFTaskRefreshModule::BeforeShut()
    {

    }

    void KFTaskRefreshModule::AfterLoad()
    {
        for ( auto& iter : KFTaskConfig::Instance()->_setting_list._objects )
        {

        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_RESET_FUNCTION__( KFTaskRefreshModule::OnResetTaskRefresh )
    {

    }

}