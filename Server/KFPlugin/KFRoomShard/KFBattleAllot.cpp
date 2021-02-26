#include "KFBattleAllot.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////
    void KFBattleAllot::Initialize( std::shared_ptr<KFRedisDriver> redis_driver )
    {
        _redis_driver = redis_driver;
    }

    bool KFBattleAllot::AddBattle( uint64 server_id, const std::string& ip, uint32 port, const std::string& version )
    {
        // 为了避免单点问题, 保存到redis缓存中
        StringMap values;
        values[ __STRING__( ip ) ] = ip;
        values[ __STRING__( version ) ] = version;
        values[ __STRING__( port ) ] = __TO_STRING__( port );

        _redis_driver->WriteMulti();
        _redis_driver->SAdd( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), server_id );
        _redis_driver->HMSet( __DATABASE_KEY_2__( __STRING__( battle ), server_id ), values );
        _redis_driver->Expire( __DATABASE_KEY_2__( __STRING__( battle ), server_id ), 300 );
        auto result = _redis_driver->WriteExec();
        return result->IsOk();
    }

    void KFBattleAllot::RemoveBattle( uint64 server_id, const std::string& version )
    {
        _redis_driver->WriteMulti();
        _redis_driver->Del( __DATABASE_KEY_2__( __STRING__( battle ), server_id ) );
        _redis_driver->SRem( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), server_id );
        _redis_driver->WriteExec();
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotBattle( uint64 server_id, const std::string& version )
    {
        if ( server_id != _invalid_int )
        {
            return AllotSpecificBattle( server_id );
        }

        return AllotVersionBattle( version );
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotSpecificBattle( uint64 server_id )
    {
        std::string ip = "";
        uint32 port = _invalid_int;
        uint64 allot_id = _invalid_int;
        bool isempty = false;

        auto result = _redis_driver->HGetAll( __DATABASE_KEY_2__( __STRING__( battle ), server_id ) );
        if ( result->IsOk() )
        {
            if ( !result->_value.empty() )
            {
                allot_id = server_id;
                ip = result->_value[ __STRING__( ip ) ];
                port = KFUtility::ToValue< uint32 >( result->_value[ __STRING__( port ) ] );
                if ( ip.empty() || port == _invalid_int )
                {
                    isempty = true;
                    __LOG_ERROR__( "battle[{}] data error!", KFAppId::ToString( server_id ) );
                }

                // 删除列表
                auto version = result->_value[ __STRING__( version ) ];
                _redis_driver->SRem( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), allot_id );
            }
            else
            {
                isempty = true;
                __LOG_ERROR__( "battle[{}] no data!", KFAppId::ToString( server_id ) );
            }
        }

        return std::make_tuple( allot_id, ip, port, isempty );
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotVersionBattle( const std::string& version )
    {
        std::string ip = "";
        uint32 port = _invalid_int;
        uint64 allot_id = _invalid_int;
        bool isempty = false;

        do
        {
            // 弹出一个可用的服务器
            auto result = _redis_driver->SPopUInt64( __DATABASE_KEY_2__( __STRING__( battlelist ), version ) );
            if ( result->_value != _invalid_int )
            {
                std::tie( allot_id, ip, port, isempty ) = AllotSpecificBattle( result->_value );
            }
            else
            {
                if ( result->IsOk() )
                {
                    __LOG_ERROR__( "version[{}] battle list empty!", version );
                }
                break;
            }
        } while ( isempty );

        return std::make_tuple( allot_id, ip, port, isempty );
    }

    void KFBattleAllot::UpdateBattle( uint64 server_id )
    {
        // 保存10分钟
        _redis_driver->Expire( __DATABASE_KEY_2__( __STRING__( battle ), server_id ), 300 );
    }
}