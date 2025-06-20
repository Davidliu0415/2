@echo off

echo Compiling all source files...

g++ -std=c++11 -o project.exe main.cpp project.cpp ProjectManagementSystem.cpp pt.cpp task.cpp TeamMenber.cpp

if %errorlevel%==0 (
    echo Compilation successful. project.exe generated.
) else (
    echo Compilation failed. Please check the error messages.
)

pause 