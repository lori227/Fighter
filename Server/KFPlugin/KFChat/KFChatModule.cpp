#include "KFChatModule.hpp"

namespace KFrame
{
    void KFChatModule::BeforeRun()
    {
        //__REGISTER_MESSAGE__( KFMsg::MSG_FOOT_USE_REQ, &KFHeroModule::HandleFootUseReq );
    }

    void KFChatModule::BeforeShut()
    {
        //__UN_MESSAGE__( KFMsg::MSG_FOOT_USE_REQ );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

}