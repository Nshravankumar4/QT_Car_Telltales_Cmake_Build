@echo off
REM ============================================
REM Setup_Repo.bat - Sets up repository branch
REM ============================================
setlocal enabledelayedexpansion

set BRANCH=%1

if "!BRANCH!"=="" (
    echo [ERROR] No branch name provided. Usage: Setup_Repo.bat ^<branch-name^>
    exit /b 1
)

echo [INFO] Setting up repository for branch: !BRANCH!

REM Fetch the specified branch
echo [INFO] Fetching branch !BRANCH! from origin...
git fetch origin !BRANCH!
if !ERRORLEVEL! neq 0 (
    echo [ERROR] Failed to fetch branch !BRANCH!
    exit /b !ERRORLEVEL!
)

REM Clean working directory
echo [INFO] Cleaning working directory...
git clean -dfx
if !ERRORLEVEL! neq 0 (
    echo [ERROR] Failed to clean repository
    exit /b !ERRORLEVEL!
)

REM Reset to remote branch
echo [INFO] Resetting to origin/!BRANCH!...
git reset --hard origin/!BRANCH!
if !ERRORLEVEL! neq 0 (
    echo [ERROR] Failed to reset repository
    exit /b !ERRORLEVEL!
)

REM Checkout the branch
echo [INFO] Checking out branch !BRANCH!...
git checkout !BRANCH!
if !ERRORLEVEL! neq 0 (
    echo [ERROR] Failed to checkout branch !BRANCH!
    exit /b !ERRORLEVEL!
)

REM Pull latest changes
echo [INFO] Pulling latest changes from origin/!BRANCH!...
git pull origin !BRANCH!
if !ERRORLEVEL! neq 0 (
    echo [ERROR] Failed to pull from origin/!BRANCH!
    exit /b !ERRORLEVEL!
)

echo [INFO] Repository setup completed successfully.
exit /b 0
