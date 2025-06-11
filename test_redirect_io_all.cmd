@echo off
setlocal enabledelayedexpansion
:: Add JetBrains CLion toolchains to PATH for this session
set "CLION_PATH=D:\Jetbrains\CLion"
@REM set "CLION_PATH=C:\Users\pysga\AppData\Local\Programs\CLion"
set "PATH=%CLION_PATH%\bin\cmake\win\x64\bin;%CLION_PATH%\bin\mingw\bin;%CLION_PATH%\bin\ninja\win\x64;%PATH%"
@REM echo Path: %PATH%
REM Check for required arguments
if "%~1"=="" (
    echo Usage: %~nx0 START END
    exit /b 1
)
if "%~2"=="" (
    echo Usage: %~nx0 START END
    exit /b 1
)

set START=%1
set END=%2

for /l %%i in (%START%,1,%END%) do (
    set num=%%i
    if %%i lss 10 set num=0%%i

    echo.
    echo Building b_!num!...
    cmake --build "cmake-build-debug" --target b_!num! -j 6

    echo Command: call test_redirect_io.cmd b_!num!
    call test_redirect_io.cmd b_!num!
    if %ERRORLEVEL% EQU 0 (echo b_!num! run successfully) else (echo b_!num! run failed)
    popd
)

endlocal