@echo off
echo Compiling animation program...

g++ -std=c++11 -Wall -Wextra main.cpp Shapes/primitives.cpp Shapes/cube.cpp Shapes/plane.cpp -o animation.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Run with: animation.exe
) else (
    echo Compilation failed!
)

pause
