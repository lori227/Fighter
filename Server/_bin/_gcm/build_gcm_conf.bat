echo "generate version..."

if not exist ..\config ( mkdir ..\config )
xcopy /S /y ..\..\..\Resource\config\* ..\config\

if not exist ..\script ( mkdir ..\script )
xcopy /S /y ..\..\..\Resource\script\* ..\script\

cd builder
gcm_build.exe -m debug -b develop -c 1 -z 2 -o
cd ..