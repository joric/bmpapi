@echo off

:: WSL version
:: get project folder
cd %1 && for %%I in (.) do set PROJ_NAME=%%~nxI

::set SDK_ROOT=/c/mnt/SDK/nRF5_SDK_15.0.0_a53641a
::set PROJ_DIR=%~dp0/../
set SDK_ROOT=~/nRF5_SDK_15.0.0_a53641a
set PROJ_ROOT=~/bmpapi

set PROJ_DIR=%PROJ_ROOT%/%PROJ_NAME%
set BUILD_DIR=.build
set UF2=%BUILD_DIR%/%PROJ_NAME%.uf2

bash -c "cd %PROJ_DIR% && export SDK_ROOT=%SDK_ROOT% && make" || exit

python %~dp0/uf2conv.py %BUILD_DIR%/nrf52840_xxaa.hex -c -f 0xADA52840 -o %UF2% || exit

echo dfu| plink.exe -serial com9 >nul

echo .
echo Waiting for the UF2 drive. Press Reset twice...
:loop
if not exist e:\ goto :loop
timeout 1
copy %UF2% e:\

