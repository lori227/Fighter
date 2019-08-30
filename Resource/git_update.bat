@echo on
setlocal enabledelayedexpansion

set curpath=%cd% 

cd %cd%\%1
::https://www.cnblogs.com/ayseeing/p/5000380.html
::git config --global credential.helper winstore

git pull
git log -1 --pretty=format:%%h > version.txt

cd %curpath%
