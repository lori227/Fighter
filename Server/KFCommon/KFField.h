﻿#ifndef __KF_FIELD_H__
#define __KF_FIELD_H__

namespace KFrame
{
#define __STRING__( name )  KFField::_##name
#define __STRING_DEFINE__( name )  static std::string _##name = #name;

    namespace KFField
    {
        __STRING_DEFINE__( retcode );
        __STRING_DEFINE__( sign );
        __STRING_DEFINE__( app );
        __STRING_DEFINE__( id );
        __STRING_DEFINE__( uuid );
        __STRING_DEFINE__( master );
        __STRING_DEFINE__( proxy );
        __STRING_DEFINE__( shard );
        __STRING_DEFINE__( route );
        __STRING_DEFINE__( ip );
        __STRING_DEFINE__( port );
        __STRING_DEFINE__( daemon );
        __STRING_DEFINE__( appname );
        __STRING_DEFINE__( apptype );
        __STRING_DEFINE__( apppath );
        __STRING_DEFINE__( appfile );
        __STRING_DEFINE__( appconfig );
        __STRING_DEFINE__( appid );
        __STRING_DEFINE__( net );
        __STRING_DEFINE__( service );
        __STRING_DEFINE__( log );
        __STRING_DEFINE__( address );
        __STRING_DEFINE__( deploy );
        __STRING_DEFINE__( deploypath );
        __STRING_DEFINE__( localip );
        __STRING_DEFINE__( interanetip );
        __STRING_DEFINE__( machine );
        __STRING_DEFINE__( status );
        __STRING_DEFINE__( agentid );
        __STRING_DEFINE__( deployid );
        __STRING_DEFINE__( command );
        __STRING_DEFINE__( value );
        __STRING_DEFINE__( zone );
        __STRING_DEFINE__( zoneid );
        __STRING_DEFINE__( loginzoneid );
        __STRING_DEFINE__( datazoneid );
        __STRING_DEFINE__( zonebalance );
        __STRING_DEFINE__( zonestatus );
        __STRING_DEFINE__( row );
        __STRING_DEFINE__( node );
        __STRING_DEFINE__( root );
        __STRING_DEFINE__( config );
        __STRING_DEFINE__( projecttime );
        __STRING_DEFINE__( arrayindex );
        __STRING_DEFINE__( logurl );
        __STRING_DEFINE__( scheduletime );
        __STRING_DEFINE__( msg );
        __STRING_DEFINE__( startup );
        __STRING_DEFINE__( debug );
        __STRING_DEFINE__( logtype );
        __STRING_DEFINE__( shutdown );
        __STRING_DEFINE__( strappid );
        __STRING_DEFINE__( agent );
        __STRING_DEFINE__( server );
        __STRING_DEFINE__( launch );
        __STRING_DEFINE__( process );
        __STRING_DEFINE__( version );
        __STRING_DEFINE__( wget );
        __STRING_DEFINE__( kill );
        __STRING_DEFINE__( downfile );
        __STRING_DEFINE__( reloadconfig );
        __STRING_DEFINE__( loadconfig );
        __STRING_DEFINE__( loadscript );
        __STRING_DEFINE__( reloadplugin );
        __STRING_DEFINE__( loadplugin );
        __STRING_DEFINE__( resource );
        __STRING_DEFINE__( downplugin );
        __STRING_DEFINE__( downresource );
        __STRING_DEFINE__( time );
        __STRING_DEFINE__( restart );
        __STRING_DEFINE__( reloadscript );
        __STRING_DEFINE__( cleantask );
        __STRING_DEFINE__( loglevel );
        __STRING_DEFINE__( logmemory );
        __STRING_DEFINE__( player );
        __STRING_DEFINE__( gateid );
        __STRING_DEFINE__( channel );
        __STRING_DEFINE__( account );
        __STRING_DEFINE__( accountid );
        __STRING_DEFINE__( basic );
        __STRING_DEFINE__( serverid );
        __STRING_DEFINE__( name );
        __STRING_DEFINE__( online );
        __STRING_DEFINE__( logintime );
        __STRING_DEFINE__( totaltime );
        __STRING_DEFINE__( birthday );
        __STRING_DEFINE__( clusterkey );
        __STRING_DEFINE__( clustername );
        __STRING_DEFINE__( robot );
        __STRING_DEFINE__( param );
        __STRING_DEFINE__( match );
        __STRING_DEFINE__( room );
        __STRING_DEFINE__( disconnettime );
        __STRING_DEFINE__( tool );
        __STRING_DEFINE__( serverip );
        __STRING_DEFINE__( serverport );
        __STRING_DEFINE__( file );
        __STRING_DEFINE__( unschedule );
        __STRING_DEFINE__( plugin );
        __STRING_DEFINE__( developreload );
        __STRING_DEFINE__( developupdate );
        __STRING_DEFINE__( dir );
        __STRING_DEFINE__( icon );
        __STRING_DEFINE__( updatemasterip );
        __STRING_DEFINE__( querymasterip );
        __STRING_DEFINE__( querymasterlist );
        __STRING_DEFINE__( masterlist );
        __STRING_DEFINE__( ipblacklist );
        __STRING_DEFINE__( ipwhitelist );
        __STRING_DEFINE__( accountblacklist );
        __STRING_DEFINE__( accountwhitelist );
        __STRING_DEFINE__( starttime );
        __STRING_DEFINE__( endtime );
        __STRING_DEFINE__( comment );
        __STRING_DEFINE__( retlist );
        __STRING_DEFINE__( addipblacklist );
        __STRING_DEFINE__( removeipblacklist );
        __STRING_DEFINE__( queryipblacklist );
        __STRING_DEFINE__( addipwhitelist );
        __STRING_DEFINE__( removeipwhitelist );
        __STRING_DEFINE__( queryipwhitelist );
        __STRING_DEFINE__( addaccountblacklist );
        __STRING_DEFINE__( removeaccountblacklist );
        __STRING_DEFINE__( queryaccountblacklist );
        __STRING_DEFINE__( addaccountwhitelist );
        __STRING_DEFINE__( removeaccountwhitelist );
        __STRING_DEFINE__( queryaccountwhitelist );


        __STRING_DEFINE__( zoneregister );
        __STRING_DEFINE__( zoneupdate );
        __STRING_DEFINE__( zoneremove );
        __STRING_DEFINE__( zonelist );
        __STRING_DEFINE__( zoneip );
        __STRING_DEFINE__( zonelogicid );
        __STRING_DEFINE__( zoneloginid );
        __STRING_DEFINE__( worldregister );
        __STRING_DEFINE__( worldurl );
        __STRING_DEFINE__( auth );
        __STRING_DEFINE__( verify );
        __STRING_DEFINE__( activation );
        __STRING_DEFINE__( onlinedata );
        __STRING_DEFINE__( ban );
        __STRING_DEFINE__( banip );
        __STRING_DEFINE__( banplayerid );
        __STRING_DEFINE__( banaccountid );
        __STRING_DEFINE__( bantime );
        __STRING_DEFINE__( unban );
        __STRING_DEFINE__( queryban );
        __STRING_DEFINE__( queryaccount );
        __STRING_DEFINE__( extend );
        __STRING_DEFINE__( user );
        __STRING_DEFINE__( playeridcreate );
        __STRING_DEFINE__( url );
        __STRING_DEFINE__( tokenexpiretime );
        __STRING_DEFINE__( token );
        __STRING_DEFINE__( openid );
        __STRING_DEFINE__( channeldata );
        __STRING_DEFINE__( count );
        __STRING_DEFINE__( code );
        __STRING_DEFINE__( verifyactivationcode );
        __STRING_DEFINE__( public );
        __STRING_DEFINE__( logic );
        __STRING_DEFINE__( openactivation );
        __STRING_DEFINE__( activationcode );
        __STRING_DEFINE__( kickonline );
        __STRING_DEFINE__( onlinelist );
        __STRING_DEFINE__( accountlist );
        __STRING_DEFINE__( accountmake );
        __STRING_DEFINE__( access_token );
        __STRING_DEFINE__( expires_in );
        __STRING_DEFINE__( scope );
        __STRING_DEFINE__( errcode );
        __STRING_DEFINE__( refresh_token );
        __STRING_DEFINE__( response );
        __STRING_DEFINE__( error );
        __STRING_DEFINE__( params );
        __STRING_DEFINE__( steamid );
        __STRING_DEFINE__( gate );
        __STRING_DEFINE__( world );
        __STRING_DEFINE__( game );
        __STRING_DEFINE__( login );
        __STRING_DEFINE__( data );
        __STRING_DEFINE__( sessionid );
        __STRING_DEFINE__( playerid );
        __STRING_DEFINE__( adddata );
        __STRING_DEFINE__( setdata );
        __STRING_DEFINE__( deldata );
        __STRING_DEFINE__( playernamelength );
        __STRING_DEFINE__( sex );
        __STRING_DEFINE__( achieve );
        __STRING_DEFINE__( level );
        __STRING_DEFINE__( task );
        __STRING_DEFINE__( activity );
        __STRING_DEFINE__( received );
        __STRING_DEFINE__( hero );
        __STRING_DEFINE__( skin );
        __STRING_DEFINE__( sevenday );
        __STRING_DEFINE__( sevenreward );
        __STRING_DEFINE__( note );
        __STRING_DEFINE__( luafile );
        __STRING_DEFINE__( luafunction );
        __STRING_DEFINE__( mail );
        __STRING_DEFINE__( reward );
        __STRING_DEFINE__( validtime );
        __STRING_DEFINE__( configid );
        __STRING_DEFINE__( content );
        __STRING_DEFINE__( title );
        __STRING_DEFINE__( type );
        __STRING_DEFINE__( flag );
        __STRING_DEFINE__( sendid );
        __STRING_DEFINE__( sendname );
        __STRING_DEFINE__( sendtime );
        __STRING_DEFINE__( globalmail );
        __STRING_DEFINE__( mailinfo );
        __STRING_DEFINE__( gmmailid );
        __STRING_DEFINE__( mailzonelist );
        __STRING_DEFINE__( maillist );
        __STRING_DEFINE__( idcreater );
        __STRING_DEFINE__( mailid );
        __STRING_DEFINE__( addmail );
        __STRING_DEFINE__( delmail );
        __STRING_DEFINE__( rank );
        __STRING_DEFINE__( friend );
        __STRING_DEFINE__( rankdata );
        __STRING_DEFINE__( ranksort );
        __STRING_DEFINE__( ranksortlist );
        __STRING_DEFINE__( minrankscore );
        __STRING_DEFINE__( statustime );
        __STRING_DEFINE__( relation );
        __STRING_DEFINE__( relationmaxcount );
        __STRING_DEFINE__( friendinvite );
        __STRING_DEFINE__( friendliness );
        __STRING_DEFINE__( refusefriend );
        __STRING_DEFINE__( freindlinessmax );
        __STRING_DEFINE__( invite );
        __STRING_DEFINE__( friendlist );
        __STRING_DEFINE__( friendlinesslimit );
        __STRING_DEFINE__( invitelist );
        __STRING_DEFINE__( message );
        __STRING_DEFINE__( variable );
        __STRING_DEFINE__( freindinvitecount );
        __STRING_DEFINE__( newadd );
        __STRING_DEFINE__( freindinvitekeeptime );
        __STRING_DEFINE__( freindlinessresettime );
        __STRING_DEFINE__( freindlinessdailymax );
        __STRING_DEFINE__( playersavetime );
        __STRING_DEFINE__( payorder );
        __STRING_DEFINE__( pay );
        __STRING_DEFINE__( firstpay );
        __STRING_DEFINE__( payid );
        __STRING_DEFINE__( paydata );
        __STRING_DEFINE__( price );
        __STRING_DEFINE__( applyorder );
        __STRING_DEFINE__( removeorder );
        __STRING_DEFINE__( querypay );
        __STRING_DEFINE__( finishpay );
        __STRING_DEFINE__( internalpay );
        __STRING_DEFINE__( item );
        __STRING_DEFINE__( storage );
        __STRING_DEFINE__( usecount );
        __STRING_DEFINE__( var );
        __STRING_DEFINE__( index );
        __STRING_DEFINE__( resettime );
        __STRING_DEFINE__( expire );
        __STRING_DEFINE__( drop );
        __STRING_DEFINE__( order );
        __STRING_DEFINE__( unlock );
        __STRING_DEFINE__( condition );
        __STRING_DEFINE__( conditions );
        __STRING_DEFINE__( execute );
        __STRING_DEFINE__( compound );
        __STRING_DEFINE__( lasttime );
        __STRING_DEFINE__( heartbeat );
        __STRING_DEFINE__( wait );
        __STRING_DEFINE__( copy );
        __STRING_DEFINE__( remote );
        __STRING_DEFINE__( project );
        __STRING_DEFINE__( element );
        __STRING_DEFINE__( recommend );
        __STRING_DEFINE__( zonerecommend );
        __STRING_DEFINE__( zonerecommendlist );
        __STRING_DEFINE__( newplayer );
        __STRING_DEFINE__( newrole );
        __STRING_DEFINE__( build );
        __STRING_DEFINE__( normal );
        __STRING_DEFINE__( disconnecttime );
        __STRING_DEFINE__( authdatabase );
        __STRING_DEFINE__( dirdatabase );
        __STRING_DEFINE__( paydatabase );
        __STRING_DEFINE__( basicdatabase );
        __STRING_DEFINE__( relationdatabase );
        __STRING_DEFINE__( maildatabase );
        __STRING_DEFINE__( zonetoken );
        __STRING_DEFINE__( store );
        __STRING_DEFINE__( storeid );
        __STRING_DEFINE__( storeunlock );
        __STRING_DEFINE__( storeindex );
        __STRING_DEFINE__( sort );
        __STRING_DEFINE__( goods );
        __STRING_DEFINE__( refresh );
        __STRING_DEFINE__( playername );
        __STRING_DEFINE__( refuse );
        __STRING_DEFINE__( rewardtype );
        __STRING_DEFINE__( sell );
        __STRING_DEFINE__( taskchain );
        __STRING_DEFINE__( taskrefresh );
        __STRING_DEFINE__( chain );
        __STRING_DEFINE__( taskreceive );
        __STRING_DEFINE__( taskcondition );
        __STRING_DEFINE__( messageopen );
        __STRING_DEFINE__( messageclose );
        __STRING_DEFINE__( moduleopen );
        __STRING_DEFINE__( moduleclose );
        __STRING_DEFINE__( dropopen );
        __STRING_DEFINE__( dropclose );
        __STRING_DEFINE__( executeopen );
        __STRING_DEFINE__( executeclose );

        __STRING_DEFINE__( team );
        __STRING_DEFINE__( info );
        __STRING_DEFINE__( maxcount );
        __STRING_DEFINE__( member );
        __STRING_DEFINE__( captainid );
        __STRING_DEFINE__( captainname );
        __STRING_DEFINE__( nowcount );
        __STRING_DEFINE__( signtime );
        __STRING_DEFINE__( continuoussign );



    }
}

#endif
