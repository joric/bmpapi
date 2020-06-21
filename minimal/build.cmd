@echo off

cd %~dp0

rd /S /Q .\_build

set file=_build/nrf52840_xxaa.hex

bash -c "export NRFSDK15_ROOT=/mnt/c/SDK/nRF5_SDK_15.0.0_a53641a && make" || exit

::uf2conv.py %file% -c -b 0xFDE00 -f 0xADA52840 -o bmpapi.uf2 || exit

uf2conv.py %file% -c -f 0xADA52840 -o bmpapi.uf2 || exit

echo dfu| plink.exe -serial com9

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist e:\ goto :loop

timeout 1

copy bmpapi.uf2 e:\


