#ifndef __KF_DISPLAY_INTERFACE_H__
#define __KF_DISPLAY_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    class KFData;
    class KFEntity;
    class KFDisplayInterface : public KFModule
    {
    public:
        // ���ͽ����ʾ���ͻ���
        // Gate/Proxy ==> Client
        template< class...Args >
        inline void SendToClient( uint64 playerid, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToClient( playerid, result, params );
        }

        // ���ͽ����ʾ���ͻ���
        // Game ==> Client
        template< class...Args >
        inline void SendToClient( KFEntity* player, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToClient( player, result, params );
        }

        // ���ͽ����ʾ���ͻ���
        // Route ==> Player
        template< class...Args >
        inline void SendToPlayer( uint64 serverid, uint64 playerid, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToPlayer( serverid, playerid, result, params );
        }

        // ���ͽ����ʾ���ͻ���
        // Route ==> Player
        template< class...Args >
        inline void SendToPlayer( const Route& route, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToPlayer( route, result, params );
        }

        // ���ͽ����ʾ���ͻ���
        // Game ==> Player
        template< class...Args >
        inline void SendToPlayer( KFData* kfbasic, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToPlayer( kfbasic, result, params );
        }

        // ���ͽ����ʾ���ͻ���
        // Game ==> Client
        template< class...Args >
        inline void SendToGroup( KFEntity* player, uint32 result, Args&& ... args )
        {
            ListString params;
            FormatParam( params, std::forward< Args >( args )... );
            SendToGroup( player, result, params );
        }

    protected:
        // ��ʽ������
        inline void FormatParam( ListString& params ) {}

        template< class T, class...Args >
        inline void FormatParam( ListString& params, T head, Args&& ... args )
        {
            params.push_back( KFUtility::ToString< T >( head ) );
            FormatParam( params, args... );
        }

    private:
        // Gate/Proxy ==> Client
        virtual void SendToClient( uint64 playerid, uint32 result, ListString& params ) = 0;

        // Game ==> Client
        virtual void SendToClient( KFEntity* player, uint32 result, ListString& params ) = 0;

        // Game ==> Client
        virtual void SendToGroup( KFEntity* player, uint32 result, ListString& params ) = 0;

        // Game ==> Route ==> Game
        virtual void SendToPlayer( KFData* kfbasic, uint32 result, ListString& params ) = 0;
        virtual void SendToPlayer( uint64 serverid, uint64 playerid, uint32 result, ListString& params ) = 0;
        virtual void SendToPlayer( const Route& route, uint32 result, ListString& params ) = 0;

    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_display, KFDisplayInterface );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif