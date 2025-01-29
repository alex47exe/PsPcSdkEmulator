REM This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
REM If a copy of the MPL was not distributed with this file, you can obtain one at
REM https://mozilla.org/MPL/2.0/.
REM
REM Copyright (c) 2025 Lander Gallastegi (LNDF)

@echo off

for /f "tokens=*" %%i in ('powershell.exe -NoProfile -Command "Get-ExecutionPolicy -Scope Process"') do set CurrentPolicy=%%i
powershell.exe -NoProfile -Command "Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass -Force"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0MakeCert.ps1"
powershell.exe -NoProfile -Command "Set-ExecutionPolicy -Scope Process -ExecutionPolicy %CurrentPolicy% -Force"
