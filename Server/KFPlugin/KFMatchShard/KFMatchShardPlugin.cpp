#include "KFMatchShardPlugin.hpp"
#include "KFMatchShardModule.hpp"
#include "KFLoader/KFLoaderInterface.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFMatchShardPlugin::Install()
    {
        __REGISTER_MODULE__( KFMatchShard );
    }

    void KFMatchShardPlugin::UnInstall()
    {
        __UN_MODULE__( KFMatchShard );
    }

    void KFMatchShardPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_loader, KFLoaderInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_route, KFRouteClientInterface );
    }

    void KFMatchShardPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFMatchConfig );
        __KF_ADD_CONFIG__( KFHeroConfig );
        __KF_ADD_CONFIG__( KFNameConfig );
    }
}