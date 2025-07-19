@echo off
echo Building Bare Metal Web Server...

if not exist "build" mkdir build

gcc -o build/server.exe ^
    src/main.c ^
    src/winsock_utils.c ^
    src/http_parser.c ^
    src/file_handler.c ^
    -lws2_32 -liphlpapi

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Run with: build/server.exe
) else (
    echo Build failed!
    pause
    exit /b 1
)

pause
