@echo off

setlocal enabledelayedexpansion

if not exist "Build" mkdir Build

set CommonFlags=/nologo /INCREMENTAL:NO /I External /I Source /std:c++20 /EHsc

if "%1"=="debug" (
	set DebugFlags=/Zi
)

:: Build graphics engine
echo.
echo Building graphics engine:
call :GenerateUnity %cd%\Source\GraphicsEngine %cd%\Source\Generated\GraphicsEngineUnity.cpp
cl Source\Generated\GraphicsEngineUnity.cpp /Fe:Build\GraphicsEngine /Fd:Build\GraphicsEngine /c %CommonFlags% %DebugFlags%
lib GraphicsEngineUnity.obj /OUT:Build\GraphicsEngine.lib /nologo

:: Build model viewer application
echo.
echo Building model viewer application:
call :GenerateUnity %cd%\Source\ModelViewer %cd%\Source\Generated\ModelViewerUnity.cpp
cl Source\Generated\ModelViewerUnity.cpp /Fe:Build\ModelViewer /Fd:Build\ModelViewer /LD %CommonFlags% %DebugFlags% /link Build\GraphicsEngine.lib

:: Build model viewer platform
echo.
echo Building model viewer platform:
call :GenerateUnity %cd%\Source\Win32ModelViewer %cd%\Source\Generated\Win32ModelViewerUnity.cpp
cl Source\Generated\Win32ModelViewerUnity.cpp /Fe:Build\Win32ModelViewer /Fd:Build\Win32ModelViewer %CommonFlags% %DebugFlags% /link user32.lib Build\GraphicsEngine.lib

:: Clean
del *.obj

goto :eof


:: Subroutines

:: Generate unity
:: Arg 1: Absolute source directory
:: Arg 2: Absolute target file
:GenerateUnity

set CurrentUnityTarget=%~2

if exist %CurrentUnityTarget% del %CurrentUnityTarget%

pushd %~1
call :GenerateUnityImpl
popd

exit /b

:: Not to be called manually
:GenerateUnityImpl

for %%f in (*.cpp) do (
	echo #include "%cd%\%%f">> %CurrentUnityTarget%
)

for /D %%d in (*) do (
	cd %%d
	call :GenerateUnityImpl
	cd ..
)
exit /b
