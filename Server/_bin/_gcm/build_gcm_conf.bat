echo "generate version..."

cd builder
gcm_build.exe -m debug -b develop -c 1 -z 2 -o
cd ..