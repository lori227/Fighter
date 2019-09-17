@echo off

SETLOCAL ENABLEDELAYEDEXPANSION

rem ===========================================================================
set framepath=..\..\KFrame
set localpath=.

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
if not exist %localpath%\CMakeLists.txt ( 
    copy /y %framepath%\CMakeLists.txt %localpath%\ 
)

if not exist %localpath%\Fighter.sln ( 
    copy /y %framepath%\Frame.sln %localpath%\Fighter.sln 
)

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update _bin path begin"
set binpath=_bin
if not exist %localpath%\%binpath% ( mkdir %localpath%\%binpath% )

rem _gcm=================================
set gcmpath=%binpath%\_gcm
if not exist %localpath%\%gcmpath% ( mkdir %localpath%\%gcmpath% )
if not exist %localpath%\%gcmpath%\build_gcm_conf.bat (
    copy /y %framepath%\%gcmpath%\build_gcm_conf.bat %localpath%\%gcmpath%\
)

set gcmpathbuilder=%binpath%\_gcm\builder
if not exist %localpath%\%gcmpathbuilder% ( mkdir %localpath%\%gcmpathbuilder% )
copy /y %framepath%\%gcmpathbuilder%\gcm_build.exe %localpath%\%gcmpathbuilder%\
copy /y %framepath%\%gcmpathbuilder%\gcm_build %localpath%\%gcmpathbuilder%\

set gcmconfinput=%binpath%\_gcm\conf_input
if not exist %localpath%\%gcmconfinput% (
    mkdir %localpath%\%gcmconfinput%
    xcopy /y %framepath%\%gcmconfinput%\* %localpath%\%gcmconfinput%
)

rem bin=================================
if not exist %localpath%\%binpath%\bin\win64 ( mkdir  %localpath%\%binpath%\bin\win64 )
if not exist %localpath%\%binpath%\bin\win64\debug ( mkdir  %localpath%\%binpath%\bin\win64\debug )
if not exist %localpath%\%binpath%\bin\win64\release ( mkdir  %localpath%\%binpath%\bin\win64\release )
copy /y %framepath%\%binpath%\bin\win64\debug\KFStartupd.exe %localpath%\%binpath%\bin\win64\debug
copy /y %framepath%\%binpath%\bin\win64\debug\libmysql.dll %localpath%\%binpath%\bin\win64\debug
copy /y %framepath%\%binpath%\bin\win64\debug\libtcmalloc_minimald.dll %localpath%\%binpath%\bin\win64\debug

copy /y %framepath%\%binpath%\bin\win64\release\KFStartup.exe %localpath%\%binpath%\bin\win64\release
copy /y %framepath%\%binpath%\bin\win64\release\libmysql.dll %localpath%\%binpath%\bin\win64\release
copy /y %framepath%\%binpath%\bin\win64\release\libtcmalloc_minimal.dll %localpath%\%binpath%\bin\win64\release

rem setting=================================
if not exist  %localpath%\%binpath%\setting (
    mkdir %localpath%\%binpath%\setting
    xcopy /y %framepath%\%binpath%\setting\* %localpath%\%binpath%\setting
)

rem startup=================================
if not exist  %localpath%\%binpath%\startup (
    mkdir %localpath%\%binpath%\startup
    xcopy /y /S %framepath%\%binpath%\startup\* %localpath%\%binpath%\startup
)

rem config=================================
if not exist  %localpath%\%binpath%\config (
    mkdir %localpath%\%binpath%\config
    xcopy /y /S %framepath%\%binpath%\config\* %localpath%\%binpath%\config
)

rem script=================================
if not exist  %localpath%\%binpath%\script ( 
    mkdir %localpath%\%binpath%\script
)
xcopy /y /S %framepath%\%binpath%\script\* %localpath%\%binpath%\script

echo "update _bin path end"

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update _lib path begin"
set libpath=_lib
rd /s /q %localpath%\%libpath%
if not exist %localpath%\%libpath% ( mkdir %localpath%\%libpath% )
if not exist %localpath%\%libpath%\win64 ( mkdir %localpath%\%libpath%\win64 )
xcopy /y /S %framepath%\%libpath%\win64\* %localpath%\%libpath%\win64 
del /F /S /Q %localpath%\%libpath%\win64\debug\KFZConfigd.lib
del /F /S /Q %localpath%\%libpath%\win64\release\KFZConfig.lib
echo "update _lib path end"
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update common path begin"
set commonpath=KFCommon
if not exist %localpath%\%commonpath% ( mkdir %localpath%\%commonpath% )
xcopy /y /S %framepath%\%commonpath%\* %localpath%\%commonpath% 
echo "update common path end"
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update KFContrib path begin"
set contribpath=KFContrib
if not exist %localpath%\%contribpath% ( mkdir %localpath%\%contribpath% )
if not exist %localpath%\%contribpath%\CMakeLists.txt ( 
    copy /y %framepath%\%contribpath%\CMakeLists.txt %localpath%\%contribpath% 
)

set subcontribpath=KFCore
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFGlobal
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFHttp
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFLogger
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFMath3D
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFMemory
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFNetwork
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFPlugin
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFProto
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFUtility
rd /s /q %localpath%\%contribpath%\%subcontribpath%
if not exist %localpath%\%contribpath%\%subcontribpath% (mkdir %localpath%\%contribpath%\%subcontribpath% )
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.inl %localpath%\%contribpath%\%subcontribpath%\

set subcontribpath=KFProtocol
if not exist %localpath%\%contribpath%\%subcontribpath% (
    mkdir %localpath%\%contribpath%\%subcontribpath%
    xcopy /y %framepath%\%contribpath%\%subcontribpath%\* %localpath%\%contribpath%\%subcontribpath%\
)

set subcontribpath=KFZConfig
if not exist %localpath%\%contribpath%\%subcontribpath% (
    mkdir %localpath%\%contribpath%\%subcontribpath%
    xcopy /y %framepath%\%contribpath%\%subcontribpath%\* %localpath%\%contribpath%\%subcontribpath%\
)
xcopy /y %framepath%\%contribpath%\%subcontribpath%\*.h %localpath%\%contribpath%\%subcontribpath%\

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
set currpath=%cd%
cd %localpath%\%contribpath%\%subcontribpath%\
"%VS150COMNTOOLS%..\IDE\Devenv" KFZConfig.vcxproj /rebuild "Debug|X64"  /project KFZConfig
"%VS150COMNTOOLS%..\IDE\Devenv" KFZConfig.vcxproj /rebuild "Release|X64" /project KFZConfig
cd %currpath%

echo "update KFContrib path end"

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "release KFLibrary path begin"
set librarypath=KFLibrary
rd /s /q %localpath%\%librarypath%
if not exist %localpath%\%librarypath% ( mkdir %localpath%\%librarypath% )

set sublibrarypath=rapidjson
if not exist %localpath%\%librarypath%\%sublibrarypath% ( mkdir %localpath%\%librarypath%\%sublibrarypath% )
xcopy /y /S %framepath%\%librarypath%\%sublibrarypath%\* %localpath%\%librarypath%\%sublibrarypath%\

set sublibrarypath=fmt
if not exist %localpath%\%librarypath%\%sublibrarypath% ( mkdir %localpath%\%librarypath%\%sublibrarypath% )
xcopy /y /S %framepath%\%librarypath%\%sublibrarypath%\* %localpath%\%librarypath%\%sublibrarypath%\

set sublibrarypath=google
if not exist %localpath%\%librarypath%\%sublibrarypath% ( mkdir %localpath%\%librarypath%\%sublibrarypath% )
xcopy /y /S %framepath%\%librarypath%\%sublibrarypath%\protobuf\src\google\*.h %localpath%\%librarypath%\%sublibrarypath%\

set sublibrarypath=luaplus
if not exist %localpath%\%librarypath%\%sublibrarypath% ( mkdir %localpath%\%librarypath%\%sublibrarypath% )
if not exist %localpath%\%librarypath%\%sublibrarypath%\tilde ( mkdir %localpath%\%librarypath%\%sublibrarypath%\tilde )
xcopy /y /S %framepath%\%librarypath%\%sublibrarypath%\*.h %localpath%\%librarypath%\%sublibrarypath%\
xcopy /y /S %framepath%\%librarypath%\%sublibrarypath%\*.inl %localpath%\%librarypath%\%sublibrarypath%\

echo "update KFLibrary path end"

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update KFPlugin path begin"
if not exist %localpath%\KFPlugin (mkdir %localpath%\KFPlugin )
if not exist %localpath%\KFPlugin\CMakeLists.txt ( 
    copy /y %framepath%\KFPlugin\CMakeLists.txt %localpath%\KFPlugin\
)

set pluginpath=KFInterface
if not exist %localpath%\%pluginpath% (mkdir %localpath%\%pluginpath% )
echo "update KFPlugin path end"
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
echo "update _resource path begin"
set resourcepath=..\Resource
if not exist %localpath%\%resourcepath% ( mkdir %resourcepath% )

rem config=================================
if not exist %resourcepath%\config ( mkdir %resourcepath%\config )
if not exist %resourcepath%\config\rank.xml ( 
    copy /y %framepath%\_resource\config\rank.xml %resourcepath%\config\
)

rem tool=================================
rem if not exist %resourcepath%\tool ( mkdir %resourcepath%\tool )
rem xcopy /y %framepath%\_resource\tool\* %resourcepath%\tool 

rem excel=================================
if not exist %resourcepath%\excel ( mkdir %resourcepath%\excel )
copy /y %framepath%\_resource\excel\_zparse.exe %resourcepath%\excel\
if not exist %resourcepath%\excel\_build.bat ( 
    copy /y %framepath%\_resource\excel\_build.bat %resourcepath%\excel\
)

rem proto=================================
if not exist %resourcepath%\proto ( mkdir %resourcepath%\proto )
if not exist %resourcepath%\proto\1.win64.bat (
    copy /y %framepath%\_resource\proto\1.win64.bat %resourcepath%\proto 
)
if not exist %resourcepath%\proto\2.linux.sh (
    copy /y %framepath%\_resource\proto\2.linux.sh %resourcepath%\proto 
)
if not exist %resourcepath%\proto\3.protoc.exe (
    copy /y %framepath%\_resource\proto\3.protoc.exe %resourcepath%\proto 
)
if not exist %resourcepath%\proto\4.protoc (
    copy /y %framepath%\_resource\proto\4.protoc %resourcepath%\proto 
)
if not exist %resourcepath%\proto\5.md5list (
    copy /y %framepath%\_resource\proto\5.md5list %resourcepath%\proto 
)
if not exist %resourcepath%\proto\6.version.txt (
    copy /y %framepath%\_resource\proto\6.version.txt %resourcepath%\proto 
)

xcopy /y %framepath%\_resource\proto\*.proto %resourcepath%\proto 


echo "update _resource path end"


rem ===========================================================================
rem ===========================================================================
rem ===========================================================================

rem frame
call :CopyInterface KFConfig
call :CopyInterface KFMySQL
call :CopyInterface KFRedis
call :CopyInterface KFMongo
call :CopyInterface KFDeployAgent
call :CopyInterface KFDeployClient
call :CopyInterface KFDeployServer
call :CopyInterface KFClusterClient
call :CopyInterface KFClusterMaster
call :CopyInterface KFClusterProxy
call :CopyInterface KFClusterShard
call :CopyInterface KFLogClient
call :CopyInterface KFLogShard
call :CopyInterface KFKernel 2000-玩家-属性定义.xlsx
call :CopyInterface KFFilter 1000-框架-屏蔽字符.xlsx
call :CopyInterface KFPlayer
call :CopyInterface KFHttpClient
call :CopyInterface KFHttpServer
call :CopyInterface KFMessage
call :CopyInterface KFBus
call :CopyInterface KFTcpServer
call :CopyInterface KFTcpClient
call :CopyInterface KFTcpDiscover
call :CopyInterface KFIpAddress
call :CopyInterface KFOption 1010-常量-全局配置.xlsx
call :CopyInterface KFRouteClient
call :CopyInterface KFRouteProxy
call :CopyInterface KFRouteShard
call :CopyInterface KFSchedule
call :CopyInterface KFTimer

rem auth
call :CopyInterface KFAuth
call :CopyInterface KFChannel 1000-框架-渠道配置.xlsx

rem data
call :CopyInterface KFDataClient
call :CopyInterface KFDataShard

rem display
call :CopyInterface KFDisplay

rem lua
call :CopyInterface KFLua

rem mail
call :CopyInterface KFMailClient
call :CopyInterface KFMailShard

rem rank
rem call :CopyInterface KFRankClient
rem call :CopyInterface KFRankMaster
rem call :CopyInterface KFRankShard
copy /y %framepath%\%binpath%\config\rank.xml ..\Resource\config\

rem public
call :CopyInterface KFPublicClient
call :CopyInterface KFPublicShard

rem relation
rem call :CopyInterface KFRelationClient
rem call :CopyInterface KFRelationShard

rem zone
call :CopyInterface KFGame
call :CopyInterface KFGate
call :CopyInterface KFLogin
call :CopyInterface KFWorld


rem player
call :CopyInterface KFCommand
call :CopyInterface KFReset 2001-玩家-进入游戏.xlsx
call :CopyInterface KFReset 2002-玩家-属性重置.xlsx
call :CopyInterface KFReset 2003-玩家-离开游戏.xlsx
call :CopyInterface KFDrop
call :CopyInterface KFItem


rem Robot
call :CopyInterface KFRobot
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem Attribute
call :CopyPlugin KFAttribute

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
set currpath=%cd%
cd ..\Resource\proto
call 1.win64.bat
cd %currpath%
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
exit /b 0
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
:CopyInterface
echo %1
copy /y %framepath%\%binpath%\bin\win64\debug\%1d.dll %localpath%\%binpath%\bin\win64\debug\
copy /y %framepath%\%binpath%\bin\win64\release\%1.dll %localpath%\%binpath%\bin\win64\release\
if not exist %localpath%\KFInterface\%1 ( mkdir %localpath%\KFInterface\%1 )
copy /y %framepath%\KFPlugin\%1\*.h %localpath%\KFInterface\%1

set excelfile=%2
if "%excelfile%"=="" (
    goto end
) else (
    echo %excelfile%
    if not exist ..\Resource\excel\%excelfile% ( 
        copy /y %framepath%\_resource\excel\%excelfile% ..\Resource\excel\
    )
)
:end
goto:eof

:CopyPlugin
if not exist %localpath%\KFPlugin\%1 (
    mkdir %localpath%\KFPlugin\%1
	xcopy /y %framepath%\KFPlugin\%1\* %localpath%\KFPlugin\%1
)
set excelfile=%2
if "%excelfile%"=="" (
    goto end
) else (
    echo %excelfile%
    if not exist ..\Resource\excel\%excelfile% ( 
        copy /y %framepath%\_resource\excel\%excelfile% ..\Resource\excel\
    )
)
:end
goto:eof

rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
rem ===========================================================================
