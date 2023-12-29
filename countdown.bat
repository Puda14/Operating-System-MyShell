@echo off
for /L %%i in (10,-1,1) do (
    echo %%i
    timeout /nobreak /t 1 >nul
)
echo Done!