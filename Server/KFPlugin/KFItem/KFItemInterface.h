#ifndef __KF_ITEM_INTERFACE_H__
#define __KF_ITEM_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    class KFItemSetting;
    typedef std::function< void( KFEntity*, KFData*, const KFItemSetting* ) > KFItemFunction;

    class KFItemInterface : public KFModule
    {
    public:
        // 初始化数据
        template< class T >
        void RegisteInitItemFunction( uint32 itemtype, T* object, void ( T::*handle )( KFEntity*, KFData*, const KFItemSetting* ) )
        {
            KFItemFunction function = std::bind( handle, object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
            BindInitItemFunction( itemtype, function );
        }
        virtual void UnRegisteInitItemFunction( uint32 itemtype ) = 0;

    protected:
        virtual void BindInitItemFunction( uint32 itemtype, KFItemFunction& function ) = 0;
    };
    __KF_INTERFACE__( _kf_item, KFItemInterface );
    //////////////////////////////////////////////////////////////////////////

#define __KF_INIT_ITEM_FUNCTION__( function )\
    void function( KFEntity* player, KFData* kfitem, const KFItemSetting* kfsetting )
#define __REGISTER_INIT_ITEM__( itemtype, function )\
    _kf_item->RegisteInitItemFunction( itemtype, this, function )
#define __UN_INIT_ITEM__( itemtype )\
    _kf_item->UnRegisteInitItemFunction( itemtype )
}



#endif