@echo off

for /f "delims=" %%a in ('dir /b/a-d/oN *.proto') do 3.protoc.exe -I=./ --cpp_out=dllexport_decl=LIBPROTOC_EXPORT:./ %%a

set serverprotopath=..\..\Server\KFContrib\KFProtocol
set clientpublicpath=..\..\UE4Client\Source\Fighter\Public\Protocol
set clientprivatepath=..\..\UE4Client\Source\Fighter\Private\Protocol

set currentpath=%cd%

xcopy *.pb.* %serverprotopath%\ /y
rem xcopy *.pb.h %clientpublicpath%\ /y
rem xcopy *.pb.cc %clientprivatepath%\ /y

call 7.luapb.bat
del *.pb*


cd %serverprotopath%
"%VS150COMNTOOLS%..\IDE\Devenv" KFProtocol.vcxproj /build "Debug|X64"  /project KFProtocol
"%VS150COMNTOOLS%..\IDE\Devenv" KFProtocol.vcxproj /build "Release|X64" /project KFProtocol
cd %currentpath%
