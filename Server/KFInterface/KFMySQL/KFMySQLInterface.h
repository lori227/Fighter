#ifndef __KF_MYSQL_INTERFACE_H__
#define __KF_MYSQL_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    class KFMySQLDriver
    {
    public:
        // �����¼
        virtual bool Insert( const std::string& table, const MapString& invalue ) = 0;

        // ɾ������
        virtual bool Delete( const std::string& table ) = 0;
        virtual bool Delete( const std::string& table, const std::string& key ) = 0;
        virtual bool Delete( const std::string& table, const MapString& keyvalues ) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////
        // �����ֶ�
        template< class T >
        bool Update( const std::string& table, const std::string& field, T invalue )
        {
            MapString updatevalue;
            updatevalue[ field ] = KFUtility::ToString< T >( invalue );
            return Update( table, updatevalue );
        }

        // Ĭ���ֶ�
        template< class T >
        bool Update( const std::string& table, const std::string& key, const std::string& field, T invalue )
        {
            MapString updatevalue;
            updatevalue[ field ] = KFUtility::ToString< T >( invalue );

            MapString keyvalue;
            keyvalue[ __KF_STRING__( id ) ] = key;

            return Update( table, keyvalue, updatevalue );
        }

        // ���¶���ֶ�
        virtual bool Update( const std::string& table, const MapString& invalue ) = 0;
        virtual bool Update( const std::string& table, const std::string& key, const MapString& invalue ) = 0;
        virtual bool Update( const std::string& table, const MapString& keyvalue, const MapString& invalue ) = 0;
        ///////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////
        template< typename... P >
        KFResult< voidptr >::UniqueType Execute( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return VoidExecute( strsql );
        }

        template< typename... P >
        KFResult< uint32 >::UniqueType QueryUInt32( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return UInt32Execute( strsql );
        }

        template< typename... P >
        KFResult< uint64 >::UniqueType QueryUint64( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return UInt64Execute( strsql );
        }

        template< typename... P >
        KFResult< std::string >::UniqueType QueryString( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return StringExecute( strsql );
        }

        template< typename... P >
        KFResult< ListString >::UniqueType QueryList( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return ListExecute( strsql );
        }

        template< typename... P >
        KFResult< MapString >::UniqueType QueryMap( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return MapExecute( strsql );
        }

        template< typename... P >
        KFResult< std::list< MapString > >::UniqueType QueryListMap( const char* myfmt, P&& ... args )
        {
            auto strsql = __FORMAT__( myfmt, std::forward<P>( args )... );
            return ListMapExecute( strsql );
        }

        // ��ѯ����
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table, const ListString& fields ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table, const std::string& key ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table, const std::string& key, const ListString& fields ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table, const MapString& key ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType Select( const std::string& table, const MapString& key, const ListString& fields ) = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        // ����( Ŀǰֻ����ִ��, û�м���mysql������ )
        virtual void Pipeline( const ListString& commands ) = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:
        virtual KFResult< voidptr >::UniqueType VoidExecute( const std::string& strsql ) = 0;
        virtual KFResult< uint32 >::UniqueType UInt32Execute( const std::string& strsql ) = 0;
        virtual KFResult< uint64 >::UniqueType UInt64Execute( const std::string& strsql ) = 0;
        virtual KFResult< std::string >::UniqueType StringExecute( const std::string& strsql ) = 0;
        virtual KFResult< MapString >::UniqueType MapExecute( const std::string& strsql ) = 0;
        virtual KFResult< ListString >::UniqueType ListExecute( const std::string& strsql ) = 0;
        virtual KFResult< std::list< MapString > >::UniqueType ListMapExecute( const std::string& strsql ) = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class KFMySQLInterface : public KFModule
    {
    public:
        // ����Execute
        virtual KFMySQLDriver* CreateExecute( const std::string& module, uint32 logicid = 0 ) = 0;

    };

    ///////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_mysql, KFMySQLInterface );
    ///////////////////////////////////////////////////////////////////////////////////////////////
}

#endif