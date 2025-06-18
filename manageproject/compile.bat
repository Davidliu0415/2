@echo off
echo ===================================
echo Project Management System Compiler
echo ===================================

echo.
echo [1/6] Compiling pt.cpp...
g++ -c pt.cpp
if errorlevel 1 goto error

echo [2/6] Compiling project.cpp...
g++ -c project.cpp
if errorlevel 1 goto error

echo [3/6] Compiling task.cpp...
g++ -c task.cpp
if errorlevel 1 goto error

echo [4/6] Compiling TeamMenber.cpp...
g++ -c TeamMenber.cpp
if errorlevel 1 goto error

echo [5/6] Compiling ProjectManagementSystem.cpp...
g++ -c ProjectManagementSystem.cpp
if errorlevel 1 goto error

echo [6/6] Compiling main.cpp...
g++ -c main.cpp
if errorlevel 1 goto error

echo.
echo Linking object files...
g++ pt.o project.o task.o TeamMenber.o ProjectManagementSystem.o main.o -o project.exe
if errorlevel 1 goto error

echo.
echo Cleaning up...
del *.o

echo.
echo ===================================
echo Compilation completed successfully!
echo ===================================
echo.
echo You can now run project.exe
echo.
pause
goto end

:error
echo.
echo ===================================
echo Compilation failed!
echo Please check the error messages above.
echo ===================================
echo.
pause
exit /b 1

:end 