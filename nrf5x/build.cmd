@echo off

cd %~dp0

set file=bmpapi.hex

bash -c "export NRFSDK15_ROOT=/mnt/c/SDK/nRF5_SDK_15.0.0_a53641a && make" || exit

cd .build

python ../uf2conv.py %file% -c -f 0xADA52840 || exit

echo dfu| plink.exe -serial com9

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist e:\ goto :loop

timeout 1

copy flash.uf2 e:\

