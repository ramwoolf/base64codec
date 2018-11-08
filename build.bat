@echo off
set ENV_BAT=env.bat

if exist %ENV_BAT% ( call %ENV_BAT% 
) else (@echo WARNING: .%ENV_BAT% is not found! Global environment is used.)

set BUILD_DIR_PREF=build

set TEST_ENABLE=OFF
if "%3" == "test" set TEST_ENABLE=ON

set BUILD_TYPE=release
if "%2" == "debug" set BUILD_TYPE=debug

if "%1" == "" goto mingw 
if "%1" == "mingw" goto mingw 
if "%1" == "msvc" goto msvc

:mingw

set "PATH=%CMAKE_DIR%;%MINGW_DIR%;%PATH%"
set "BUILD_DIR=%BUILD_DIR_PREF%_mingw_%BUILD_TYPE%"

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
cd %BUILD_DIR%
@echo Clean solution: %BUILD_DIR%
del /q /s * > NUL

cmake ../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DTEST_ENABLE=%TEST_ENABLE%
mingw32-make VERBOSE=1

cd ../
goto end

:msvc

set "PATH=%CMAKE_DIR%;%PATH%"
set "BUILD_DIR=%BUILD_DIR_PREF%_msvc_%BUILD_TYPE%"

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
cd %BUILD_DIR%
@echo Clean solution: %BUILD_DIR%
del /q /s * > NUL

cmake ../ -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DTEST_ENABLE=%TEST_ENABLE%

cd ../
goto end

:end

