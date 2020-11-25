#include "KFFightPlugin.hpp"
#include "KFFightModule.hpp"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFFightPlugin::Install()
    {
        __REGISTER_MODULE__( KFFight );
    }

    void KFFightPlugin::UnInstall()
    {
        __UN_MODULE__( KFFight );
    }

    void KFFightPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_reset, KFResetInterface );
        __FIND_MODULE__( _kf_player, KFPlayerInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
    }

    void KFFightPlugin::AddConfig()
    {
    }
}