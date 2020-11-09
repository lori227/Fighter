﻿#ifndef __KF_PLAYERT_INTERFACE_H__
#define __KF_PLAYERT_INTERFACE_H__

#include "KFrame.h"
#include "KFKernel/KFComponent.h"

namespace KFrame
{
    class KFPlayerInterface : public KFModule
    {
    public:
        template< class T >
        void RegisterInitDataFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddInitDataFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterInitDataFunction( T* object )
        {
            RemoveInitDataFunction( typeid( T ).name() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterUnInitDataFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddUnInitDataFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterUnInitDataFunction( T* object )
        {
            RemoveUnInitDataFunction( typeid( T ).name() );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // 逻辑函数
        template< class T >
        void RegisterRunDataFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddRunDataFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterRunDataFunction( T* object )
        {
            RemoveRunDataFunction( typeid( T ).name() );
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////
        // 逻辑函数
        template< class T >
        void RegisterAfterRunDataFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddAfterRunDataFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterAfterRunDataFunction( T* object )
        {
            RemoveAfterRunDataFunction( typeid( T ).name() );
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////

        // 重置函数
        template< class T >
        void RegisterResetFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddResetFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterResetFunction( T* object )
        {
            RemoveResetFunction( typeid( T ).name() );
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////
        // 登录函数
        template< class T >
        void RegisterBeforeEnterFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddBeforeEnterFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterBeforeEnterFunction( T* object )
        {
            RemoveBeforeEnterFunction( typeid( T ).name() );
        }
        // 登录函数
        template< class T >
        void RegisterEnterFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddEnterFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterEnterFunction( T* object )
        {
            RemoveEnterFunction( typeid( T ).name() );
        }

        // 登录函数
        template< class T >
        void RegisterAfterEnterFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddAfterEnterFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterAfterEnterFunction( T* object )
        {
            RemoveAfterEnterFunction( typeid( T ).name() );
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // 离开函数
        template< class T >
        void RegisterLeaveFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddLeaveFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterLeaveFunction( T* object )
        {
            RemoveLeaveFunction( typeid( T ).name() );
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////
        // 新玩家首次登陆函数
        template< class T >
        void RegisterNewPlayerFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddNewPlayerFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterNewPlayerFunction( T* object )
        {
            RemoveNewPlayerFunction( typeid( T ).name() );
        }

        // 创建角色
        template< class T >
        void RegisterCreateRoleFunction( T* object, void ( T::*handle )( KFEntity* player ) )
        {
            KFEntityFunction function = std::bind( handle, object, std::placeholders::_1 );
            AddCreateRoleFunction( typeid( T ).name(), function );
        }

        template< class T >
        void UnRegisterCreateRoleFunction( T* object )
        {
            RemoveCreateRoleFunction( typeid( T ).name() );
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // 创建玩家
        virtual KFEntity* Login( const KFMsg::PBLoginData* pblogin, const KFMsg::PBObject* pbplayerdata ) = 0;

        // 重新登录
        virtual KFEntity* ReLogin( uint64 playerid, uint64 gateid ) = 0;

        // 查找玩家
        virtual KFEntity* FindPlayer( uint64 playerid ) = 0;
        virtual KFEntity* FindPlayer( uint64 playerid, const char* function, uint32 line ) = 0;

        // 删除玩家
        virtual void RemovePlayer() = 0;
        virtual void RemovePlayer( uint64 playerid ) = 0;
        virtual void RemovePlayer( KFEntity* player ) = 0;

        // 发送消息
        virtual bool SendToClient( KFEntity* player, uint32 msgid, ::google::protobuf::Message* message, uint32 deplay = 0u ) = 0;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
    protected:
        virtual void AddInitDataFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveInitDataFunction( const std::string& moudle ) = 0;

        virtual void AddUnInitDataFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveUnInitDataFunction( const std::string& moudle ) = 0;

        virtual void AddRunDataFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveRunDataFunction( const std::string& moudle ) = 0;

        virtual void AddAfterRunDataFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveAfterRunDataFunction( const std::string& moudle ) = 0;

        virtual void AddResetFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveResetFunction( const std::string& moudle ) = 0;

        virtual void AddBeforeEnterFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveBeforeEnterFunction( const std::string& moudle ) = 0;

        virtual void AddEnterFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveEnterFunction( const std::string& moudle ) = 0;

        virtual void AddAfterEnterFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveAfterEnterFunction( const std::string& moudle ) = 0;

        virtual void AddLeaveFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveLeaveFunction( const std::string& moudle ) = 0;

        virtual void AddNewPlayerFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveNewPlayerFunction( const std::string& moudle ) = 0;

        virtual void AddCreateRoleFunction( const std::string& moudle, KFEntityFunction& function ) = 0;
        virtual void RemoveCreateRoleFunction( const std::string& moudle ) = 0;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_player, KFPlayerInterface );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __CLIENT_PROTO_PARSE__( msgtype ) \
    __PROTO_PARSE__( msgtype ); \
    auto playerid = __ROUTE_RECV_ID__; \
    auto player = _kf_player->FindPlayer( playerid, __FUNC_LINE__ );\
    if ( player == nullptr )\
    {\
        return;\
    }\

#define __SERVER_PROTO_PARSE__( msgtype ) \
    __PROTO_PARSE__( msgtype ); \
    auto player = _kf_player->FindPlayer( kfmsg.playerid() );\
    if ( player == nullptr )\
    {\
        return;\
    }\

#define __ROUTE_PROTO_PARSE__( msgtype ) \
    __PROTO_PARSE__( msgtype ); \
    auto playerid = __ROUTE_RECV_ID__; \
    auto player = _kf_player->FindPlayer( playerid );\
    if ( player == nullptr )\
    {\
        return;\
    }\
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_PLAYER_ENTER_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_ENTER__( function ) _kf_player->RegisterEnterFunction( this, function )
#define __UN_PLAYER_ENTER__() _kf_player->UnRegisterEnterFunction( this )

#define __REGISTER_PLAYER_BEFORE_ENTER__( function ) _kf_player->RegisterBeforeEnterFunction( this, function )
#define __UN_PLAYER_BEFORE_ENTER__() _kf_player->UnRegisterBeforeEnterFunction( this )

#define __REGISTER_PLAYER_AFTER_ENTER__( function ) _kf_player->RegisterAfterEnterFunction( this, function )
#define __UN_PLAYER_AFTER_ENTER__() _kf_player->UnRegisterAfterEnterFunction( this )

#define __KF_PLAYER_LEAVE_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_LEAVE__( function ) _kf_player->RegisterLeaveFunction( this, function )
#define __UN_PLAYER_LEAVE__() _kf_player->UnRegisterLeaveFunction( this )

#define __KF_PLAYER_RESET_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_RESET__( function ) _kf_player->RegisterResetFunction( this, function )
#define __UN_PLAYER_RESET__() _kf_player->UnRegisterResetFunction( this )

#define __KF_PLAYER_RUN_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_RUN__( function ) _kf_player->RegisterRunDataFunction( this, function )
#define __UN_PLAYER_RUN__() _kf_player->UnRegisterRunDataFunction( this )

#define __KF_PLAYER_AFTER_RUN_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_AFTER_RUN__( function ) _kf_player->RegisterAfterRunDataFunction( this, function )
#define __UN_PLAYER_AFTER_RUN__() _kf_player->UnRegisterAfterRunDataFunction( this )

#define __KF_PLAYER_INIT_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_INIT__( function ) _kf_player->RegisterInitDataFunction( this, function )
#define __UN_PLAYER_INIT__() _kf_player->UnRegisterInitDataFunction( this )

#define __KF_PLAYER_UNINIT_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_PLAYER_UNINIT__( function ) _kf_player->RegisterUnInitDataFunction( this, function )
#define __UN_PLAYER_UNINIT__() _kf_player->UnRegisterUnInitDataFunction( this )

#define __KF_NEW_PLAYER_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_NEW_PLAYER__( function ) _kf_player->RegisterNewPlayerFunction( this, function )
#define __UN_NEW_PLAYER__() _kf_player->UnRegisterNewPlayerFunction( this )

#define __KF_CREATE_ROLE_FUNCTION__( function ) void function( KFEntity* player )
#define __REGISTER_CREATE_ROLE__( function ) _kf_player->RegisterCreateRoleFunction( this, function )
#define __UN_CREATE_ROLE__() _kf_player->UnRegisterCreateRoleFunction( this )

}

#endif