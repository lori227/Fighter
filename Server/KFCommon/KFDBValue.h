﻿#ifndef __KF_DB_VALUE_H__
#define __KF_DB_VALUE_H__

#include "KFMap.h"
#include "KFMacros.h"

namespace KFrame
{
    class KFDBValue
    {
    public:
        inline void AddValue( const std::string& key, uint64 value )
        {
            _int_list[ key ] = value;
        }

        inline void AddValue( const std::string& key, const std::string& value, bool isbinary = false )
        {
            if ( isbinary )
            {
                _str_list[ key ] = value;
            }
            else
            {
                _bin_list[ key ] = value;
            }
        }

        inline uint64 FindValue( const std::string& key ) const
        {
            auto iter = _int_list.find( key );
            if ( iter == _int_list.end() )
            {
                return 0u;
            }

            return iter->second;
        }

        inline const std::string& FindStrValue( const std::string& key ) const
        {
            auto iter = _str_list.find( key );
            if ( iter == _str_list.end() )
            {
                iter = _bin_list.find( key );
                if ( iter == _bin_list.end() )
                {
                    return _invalid_string;
                }
            }

            return iter->second;
        }

        bool IsEmpty() const
        {
            return _int_list.empty() && _str_list.empty() && _bin_list.empty();
        }

    public:
        // int 属性列表
        StringUInt64 _int_list;

        // string 属性列表
        StringMap _str_list;

        // binary 属性列表
        StringMap _bin_list;
    };

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
#define __DBVALUE_TO_PROTO__( dbvalue, pbvalue )\
    {\
        auto& pbintlist = *pbvalue->mutable_pbuint64();\
        __MAP_TO_PROTO__( dbvalue._int_list, pbintlist);\
        auto& pbstrlist = *pbvalue->mutable_pbstring(); \
        __MAP_TO_PROTO__( dbvalue._str_list, pbstrlist ); \
        __MAP_TO_PROTO__( dbvalue._bin_list, pbstrlist ); \
    }

#define __PROTO_TO_DBVALUE__( pbvalue, dbvalue  )\
    {\
        auto pbintlist = &pbvalue->pbuint64();\
        __PROTO_TO_MAP__( pbintlist, dbvalue._int_list);\
        auto pbstrlist = &pbvalue->pbstring(); \
        __PROTO_TO_MAP__( pbstrlist, dbvalue._str_list  ); \
    }

#define __DBVALUE_TO_MAP__( dbvalue, values )\
    {\
        __MAP_TO_PROTO__( dbvalue._str_list, values ); \
        __MAP_TO_PROTO__( dbvalue._bin_list, values ); \
        for ( auto iter = dbvalue._int_list.begin(); iter != dbvalue._int_list.end(); ++iter )\
        {\
            values[ iter->first ] = __TO_STRING__(iter->second);\
        }\
    }

#define __JSON_TO_DBVALUE__( kfjson, dbvalue )\
    for ( auto iter = kfjson.MemberBegin(); iter != kfjson.MemberEnd(); ++iter )\
    {\
        if ( iter->value.IsString() )\
        {\
            dbvalue.AddValue(iter->name.GetString(), iter->value.GetString());\
        }\
        else if ( iter->value.IsNumber() )\
        {\
            dbvalue.AddValue(iter->name.GetString(), iter->value.GetUint64());\
        }\
    }
}
#endif

