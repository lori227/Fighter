@echo on
setlocal enabledelayedexpansion

set curpath=%cd% 

cd %cd%\%1

git pull
git log -1 --pretty=format:%%h > version.txt

cd %curpath%


:: 下载 git
:: https://github.com/git-for-windows/git/releases/download/v2.23.0.windows.1/Git-2.23.0-64-bit.exe


::https://www.cnblogs.com/ayseeing/p/5000380.html
:: 设置保存密码
::git config --global credential.helper winstore

:: 安装密码工具 git-credential-winstore.exe
