﻿#ifndef __KF_ITEM_INTERFACE_H__
#define __KF_ITEM_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    class KFItemInterface : public KFModule
    {
    public:

    };
    __KF_INTERFACE__( _kf_item, KFItemInterface );
    //////////////////////////////////////////////////////////////////////////
    class KFItemUseInterface : public KFModule
    {
    public:

    };
    __KF_INTERFACE__( _kf_item_use, KFItemUseInterface );
    //////////////////////////////////////////////////////////////////////////
}



#endif