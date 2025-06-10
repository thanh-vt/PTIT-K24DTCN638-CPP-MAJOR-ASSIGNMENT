@echo off
setlocal enabledelayedexpansion
:: Add JetBrains CLion toolchains to PATH for this session
set "PATH=D:\Jetbrains\CLion\bin\cmake\win\x64\bin;D:\Jetbrains\CLion\bin\mingw\bin;D:\Jetbrains\CLion\bin\ninja\win\x64;%PATH%"

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

    pushd cmake-build-debug
    echo Command: call test_redirect_io.cmd b_!num!
    call test_redirect_io.cmd b_!num!
    popd
)

endlocal