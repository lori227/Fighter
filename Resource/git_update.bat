@echo on
setlocal enabledelayedexpansion

set curpath=%cd% 

cd %cd%\%1
::git config --global credential.helper winstore

git pull
git log -1 --pretty=format:%%h > version.txt

cd %curpath%
