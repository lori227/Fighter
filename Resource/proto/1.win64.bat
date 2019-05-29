@echo off

for /f "delims=" %%a in ('dir /b/a-d/oN *.proto') do 3.protoc.exe -I=./ --cpp_out=dllexport_decl=LIBPROTOC_EXPORT:./ %%a

set serverprotopath=..\..\Server\KFContrib\KFProtocol
set clientpublicpath=..\..\UE4Client\Source\Fighter\Public\Protocol
set clientprivatepath=..\..\UE4Client\Source\Fighter\Private\Protocol
set luaprotopath=..\..\UE4Client\Content\Lua\protocol

set currentpath=%cd%

xcopy *.pb.* %serverprotopath%\ /y
xcopy *.pb.h %clientpublicpath%\ /y
xcopy *.pb.cc %clientprivatepath%\ /y
del *.pb.*

copy /y CodeMessage.proto %luaprotopath%\
copy /y EnumMessage.proto %luaprotopath%\
copy /y DefineMessage.proto %luaprotopath%\
copy /y ClientMessage.proto %luaprotopath%\
copy /y FrameCodeMessage.proto %luaprotopath%\
copy /y FrameEnumMessage.proto %luaprotopath%\
copy /y FrameDefineMessage.proto %luaprotopath%\
copy /y FrameClientMessage.proto %luaprotopath%\

cd %serverprotopath%
"%VS150COMNTOOLS%..\IDE\Devenv" KFProtocol.vcxproj /build "Debug|X64"  /project KFProtocol
"%VS150COMNTOOLS%..\IDE\Devenv" KFProtocol.vcxproj /build "Release|X64" /project KFProtocol
cd %currentpath%
