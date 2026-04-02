workspace "AGP"
	configurations { "Debug", "Release" }

project "AGP"
	kind "Makefile"
	language "C++"
	targetdir "Build"
	objdir ".vs"
	files { "**.c", "**.h", "**.cpp", "**.hpp" }
	debugcommand "Build/Win32ModelViewer"

filter "configurations:Release"
	vsprops { NMakeBuildCommandLine = "call build.bat release" }
filter "configurations:Debug"
	vsprops { NMakeBuildCommandLine = "call build.bat debug" }
