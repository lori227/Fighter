@echo off

set DIR=%~dp0

cd /d "%DIR%"

setlocal enabledelayedexpansion

for /r %%i in (*.proto) do (
    set pbname=%%i
    set pbname=!pbname:~0,-5!pb
    3.protoc -I %DIR% --descriptor_set_out !pbname! %%i
)

set luaprotopath=..\..\UE4Client\Content\Lua\protocol

move ClientMessage.pb %luaprotopath%
move CodeMessage.pb %luaprotopath%
move DefineMessage.pb %luaprotopath%
move EnumMessage.pb %luaprotopath%
move FrameClientMessage.pb %luaprotopath%
move FrameCodeMessage.pb %luaprotopath%
move FrameDefineMessage.pb %luaprotopath%
move FrameEnumMessage.pb %luaprotopath%
