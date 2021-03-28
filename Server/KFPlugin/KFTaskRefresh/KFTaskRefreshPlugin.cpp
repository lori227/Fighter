#include "KFTaskRefreshPlugin.hpp"
#include "KFTaskRefreshModule.hpp"
#include "KFLoader/KFLoaderInterface.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFTaskRefreshPlugin::Install()
    {
        __REGISTER_MODULE__( KFTaskRefresh );
    }

    void KFTaskRefreshPlugin::UnInstall()
    {
        __UN_MODULE__( KFTaskRefresh );
    }

    void KFTaskRefreshPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_reset, KFResetInterface );
        __FIND_MODULE__( _kf_loader, KFLoaderInterface );
        __FIND_MODULE__( _kf_kernel, KFKernelInterface );
        __FIND_MODULE__( _kf_player, KFPlayerInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
    }

    void KFTaskRefreshPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFTaskConfig );
    }
}