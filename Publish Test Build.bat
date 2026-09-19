@echo off
setlocal
powershell.exe -NoLogo -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\friends\Publish-TestBuild.ps1" -RepoPath "%~dp0."
set "result=%ERRORLEVEL%"
echo.
if not "%result%"=="0" echo Publish stopped. Read the error above; an incomplete release stays a draft.
pause
exit /b %result%
