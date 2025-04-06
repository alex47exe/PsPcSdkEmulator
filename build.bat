@echo off
setlocal enabledelayedexpansion

echo PsPcSdkEmu Build Script
echo ====================

:: Build both Release and Debug for x64
set PLATFORM=x64

echo Building for Release and Debug x64

:: Run the certificate generation script first
echo Running certificate generation...
if exist "PsPcSdkEmulator\RunMakeCert.bat" (
    pushd PsPcSdkEmulator
    call RunMakeCert.bat
    popd
    echo Certificate generation completed.
) else (
    echo WARNING: Certificate script not found at PsPcSdkEmulator\RunMakeCert.bat
    echo Build may fail if certificate is missing.
)

:: Find MSBuild
set FOUND_MSBUILD=0
set MSBUILD_PATH=

:: Try Visual Studio 2022
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
    set FOUND_MSBUILD=1
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
    set FOUND_MSBUILD=1
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    set FOUND_MSBUILD=1
)

:: Try Visual Studio 2019
if %FOUND_MSBUILD%==0 (
    if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    )
)

:: Try Visual Studio 2017
if %FOUND_MSBUILD%==0 (
    if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" (
        set MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe"
        set FOUND_MSBUILD=1
    )
)

:: Try to find MSBuild in PATH
if %FOUND_MSBUILD%==0 (
    where msbuild.exe >nul 2>&1
    if %ERRORLEVEL%==0 (
        set MSBUILD_PATH=msbuild.exe
        set FOUND_MSBUILD=1
    )
)

if %FOUND_MSBUILD%==0 (
    echo ERROR: MSBuild not found. Please install Visual Studio or set it in your PATH.
    exit /b 1
)

echo Using MSBuild: %MSBUILD_PATH%

:: Build both configurations for x64
echo Building Release configuration...
%MSBUILD_PATH% PsPcSdkEmulator.sln /p:Configuration=Release /p:Platform=%PLATFORM% /t:Rebuild /m /v:minimal

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Release build failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

echo Building Debug configuration...
%MSBUILD_PATH% PsPcSdkEmulator.sln /p:Configuration=Debug /p:Platform=%PLATFORM% /t:Rebuild /m /v:minimal

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Debug build failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

:: Process Release output
set RELEASE_DIR=x64\Release
set RELEASE_DLL=%RELEASE_DIR%\PsPcSdkEmu.dll
set RELEASE_INI=%RELEASE_DIR%\PsPcSdkEmu.ini

echo Checking Release output files...
if not exist "%RELEASE_DLL%" (
    echo ERROR: Release DLL not found at %RELEASE_DLL%
    exit /b 1
)

echo Release Output DLL: %RELEASE_DLL%

:: Process Debug output
set DEBUG_DIR=x64\Debug
set DEBUG_DLL=%DEBUG_DIR%\PsPcSdkEmu.dll
set DEBUG_INI=%DEBUG_DIR%\PsPcSdkEmu.ini

echo Checking Debug output files...
if not exist "%DEBUG_DLL%" (
    echo ERROR: Debug DLL not found at %DEBUG_DLL%
    exit /b 1
)

echo Debug Output DLL: %DEBUG_DLL%

:: Check for INI file and copy to both output directories
echo Looking for INI file...
set INI_FOUND=0

:: Check in the PsPcSdkEmulator subfolder
if exist "PsPcSdkEmulator\PsPcSdkEmulator.ini" (
    echo INI found in PsPcSdkEmulator folder
    copy "PsPcSdkEmulator\PsPcSdkEmulator.ini" "%RELEASE_INI%" >nul
    copy "PsPcSdkEmulator\PsPcSdkEmulator.ini" "%DEBUG_INI%" >nul
    set INI_FOUND=1
)

echo.
echo Build completed successfully!
echo.
echo Release Output: %RELEASE_DLL%
echo Release Output: %RELEASE_INI%
echo.
echo Debug Output: %DEBUG_DLL%
echo Debug Output: %DEBUG_INI%

endlocal