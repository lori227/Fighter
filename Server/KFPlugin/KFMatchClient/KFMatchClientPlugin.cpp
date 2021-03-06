﻿#include "KFMatchClientPlugin.hpp"
#include "KFMatchClientModule.hpp"
#include "KFLoader/KFLoaderInterface.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFMatchClientPlugin::Install()
    {
        __REGISTER_MODULE__( KFMatchClient );
    }

    void KFMatchClientPlugin::UnInstall()
    {
        __UN_MODULE__( KFMatchClient );
    }

    void KFMatchClientPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_loader, KFLoaderInterface );
        __FIND_MODULE__( _kf_kernel, KFKernelInterface );
        __FIND_MODULE__( _kf_player, KFPlayerInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_route, KFRouteClientInterface );
    }

    void KFMatchClientPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFMatchConfig );
    }
}