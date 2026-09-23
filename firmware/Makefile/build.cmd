:: Copyright (c) 2025 Nations Technologies Inc.
:: SPDX-License-Identifier: Apache-2.0

@echo off
rem ===========================================================================
rem N32H787 demo one-click build entry for Windows.
rem All path changes are local to this process; no system/global PATH edits.
rem
rem Usage:
rem   build.cmd                 Build n32h787_person_detect_demo.elf/.hex/.bin (M7 + M4 image)
rem   build.cmd release=y       Release build without debug info
rem   build.cmd clean           Remove the build directory
rem   build.cmd cm4             Build M4 only
rem   build.cmd flash           Build and flash the single image at 0x15000000
rem                             via CMSIS-DAP (no bootloader, power-on direct run)
rem ===========================================================================

setlocal

rem --- Python 3 (user-scope winget install; needed by tools/embed_tflite.py)
set "PYTHON_DIR=%LOCALAPPDATA%\Programs\Python\Python312"

rem --- Git for Windows provides sh.exe and coreutils (dd/stat/mkdir/...)
rem     Override with "set GIT_DIR=..." if Git is installed elsewhere.
if not defined GIT_DIR if exist "C:\Program Files\Git\bin\sh.exe" set "GIT_DIR=C:\Program Files\Git"
if not defined GIT_DIR set "GIT_DIR=D:\Program\git\Git"

rem --- N32Studio toolchain (absolute GCC_PATH avoids the native-make PATH
rem     truncation that otherwise loses the compiler inside sh recipes)
if not defined GCC_PATH set "GCC_PATH=%USERPROFILE:\=/%/.n32studio/Toolchain/gcc-arm-none-eabi/bin/"
if not defined PYTHON set "PYTHON=python"
if not defined OPENOCD set "OPENOCD=%USERPROFILE:\=/%/.n32studio/Toolchain/openocd/bin/openocd.exe"

set "PATH=%PYTHON_DIR%;%PYTHON_DIR%\Scripts;%GIT_DIR%\bin;%GIT_DIR%\usr\bin;%PATH%"

if "%~1"=="" (
    make
) else (
    make %*
)

endlocal
