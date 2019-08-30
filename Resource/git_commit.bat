@echo off
setlocal enabledelayedexpansion

set curpath=%cd% 

cd %cd%\%1
git commit -m "update resource by parse tool"


cd %curpath%




