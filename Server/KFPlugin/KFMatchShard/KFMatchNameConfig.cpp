﻿#include "KFMatchNameConfig.hpp"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    void KFMatchNameConfig::ReadSetting( KFNode& xmlnode, KFMatchNameSetting* kfsetting )
    {
        auto name = xmlnode.GetString( "Name" );
        kfsetting->_name_list.push_back( name );
    }

    /////////////////////////////////////////////////////////////////////////////////
    const std::string& KFMatchNameConfig::RandName() const
    {
        static std::string _name = "";
        _name.clear();

        for ( auto iter : _settings._objects )
        {
            auto kfsetting = iter.second;
            if ( kfsetting->_name_list.empty() )
            {
                continue;
            }

            auto index = KFGlobal::Instance()->RandRatio( kfsetting->_name_list.size() );
            _name += kfsetting->_name_list[ index ];
        }

        return _name;
    }
}