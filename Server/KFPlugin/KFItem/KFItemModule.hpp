#ifndef __KF_ITEM_MOUDLE_H__
#define __KF_ITEM_MOUDLE_H__

/************************************************************************
//    @Module			:    物品系统
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2017-1-22
************************************************************************/

#include "KFItemInterface.h"
#include "KFLua/KFLuaInterface.h"
#include "KFTimer/KFTimerInterface.h"
#include "KFKernel/KFKernelInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFZConfig/KFItemConfig.hpp"

namespace KFrame
{
    class KFItemModule : public KFItemInterface
    {
    public:
        KFItemModule() = default;
        ~KFItemModule() = default;

        // 逻辑
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////

    protected:
        virtual void BindInitItemFunction( uint32 itemtype, KFItemFunction& function );
        virtual void UnRegisteInitItemFunction( uint32 itemtype );

    protected:
        // 删除道具
        __KF_MESSAGE_FUNCTION__( HandleRemoveItemReq );

    protected:
        // 获得道具数量
        __KF_GET_CONFIG_VALUE_FUNCTION__( GetItemTotalCount );

        // 判断是否能添加物品
        __KF_CHECK_ADD_ELEMENT_FUNCTION__( CheckAddItemElement );

        // 添加物品
        __KF_ADD_ELEMENT_FUNCTION__( AddItemElement );

        // 判断物品
        __KF_CHECK_REMOVE_ELEMENT_FUNCTION__( CheckRemoveItemElement );

        // 删除物品
        __KF_REMOVE_ELEMENT_FUNCTION__( RemoveItemElement );

        // 添加物品回调
        __KF_ADD_DATA_FUNCTION__( OnAddItemCallBack );

        // 物品数量更新回调
        __KF_UPDATE_DATA_FUNCTION__( OnItemCountUpdateCallBack );

        // 物品时间更新回调
        __KF_UPDATE_DATA_FUNCTION__( OnItemTimeUpdateCallBack );

        // 删除物品回调
        __KF_REMOVE_DATA_FUNCTION__( OnRemoveItemCallBack );

        // 删除时间道具
        __KF_TIMER_FUNCTION__( OnTimerRemoveTimeItem );

        // 进入游戏
        __KF_ENTER_PLAYER_FUNCTION__( OnEnterItemModule );

        // 离开游戏
        __KF_LEAVE_PLAYER_FUNCTION__( OnLeaveItemModule );

    protected:
        //背包是否满了
        bool CheckItemRecordFull( KFData* kfitemrecord, const KFItemSetting* kfsetting, uint32 itemcount );

        // 添加时间叠加数量
        void AddOverlayTimeItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count, uint32 time );

        // 添加数量叠加道具
        void AddOverlayCountItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count );

        // 不能叠加的道具
        void AddNotOverlayItem( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const KFItemSetting* kfsetting, uint32 count );

        // 添加新物品
        KFData* AddNewItemData( KFEntity* player, KFData* kfparent, const KFItemSetting* kfsetting, uint32& count, uint32 time );
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 调用函数lua函数
        bool CallItemLuaFunction( KFEntity* player, uint32 functiontype, const KFItemSetting* kfsetting, uint32 itemcount );

        // 启动检查时间道具
        void StartItemCheckTimer( KFEntity* player, KFData* kfitem );

        // 计算道具添加数量
        uint32 CalcItemAddCount( uint32 sourcecount, uint32 targetcount, uint32 maxcount );

    protected:
        // 玩家组件上下文
        KFComponent* _kf_component = nullptr;


        // 初始化
        KFBind<uint32, uint32, KFItemFunction > _init_item_function;
    };
}

#endif