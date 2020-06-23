@echo off

cd %~dp0

rd /S /Q _build

bash -c "export NRFSDK15_ROOT=/mnt/c/SDK/nRF5_SDK_15.0.0_a53641a && make" || exit

uf2conv.py _build/nrf52840_xxaa.hex -c -f 0xADA52840 -o launcher.uf2 || exit

echo Resetting via microshell...
echo dfu| plink.exe -serial com9

echo Waiting for the UF2 drive. Press Reset twice...
:loop
if not exist e:\ goto :loop
timeout 1
copy launcher.uf2 e:\


