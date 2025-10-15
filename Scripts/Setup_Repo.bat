@echo off
REM ============================================
REM Setup_Repo.bat - Sets up repository branch
REM ============================================

set BRANCH=%1
if "%BRANCH%"=="" (
    echo [ERROR] No branch name provided. Usage: Setup_Repo.bat <branch-name>
    exit /b 1
)

echo [INFO] Setting up repository for branch: %BRANCH%

git fetch origin %BRANCH%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

git clean -dfx
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

git reset --hard origin/%BRANCH%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

git checkout %BRANCH%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

git pull origin %BRANCH%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

echo [INFO] Repository setup completed successfully.
exit /b 0
