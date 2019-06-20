@echo off
setlocal enabledelayedexpansion
if not exist ..\..\Server\_bin\config\ ( mkdir ..\..\Server\_bin\config\ )

for /f "delims=\" %%x in ('dir /b /a-d /o-d "*.xlsx"') do (
echo %%x
_parse.exe %%~nx.xlsx --xml=..\..\Server\_bin\config\
)
