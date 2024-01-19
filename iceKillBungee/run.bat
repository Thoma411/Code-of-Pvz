@echo off
g++ ialgo.cpp interlayer.cpp newExemple.cpp -o ikb_eg.exe
if "%1" == "" (
    ikb_eg.exe 1000000
) else (
    ikb_eg.exe %1
)