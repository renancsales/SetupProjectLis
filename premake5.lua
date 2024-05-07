projectName = "Lis_App"
workspace "Setup"
	architecture "x64"
	startproject  "Lis_App"
	
	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories relative to root folder (sol. directory)
IncludeDir = {}
IncludeDir["Lis"] = projectName .. "/vendor/lis_premake/include"
include "Lis_App/vendor/lis_premake"


project "Lis_App"
	location "Lis_App"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	-- Additional library directories
	--libdirs { "%{prj.name}/vendor/lis_premake/lib" }
	
	-- OpenMP support
	buildoptions { "/openmp" }
	
	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.Lis}",
	}
	
	links 
	{
		"Lis",
	}
	
	-- Filter: Configurations only applied to specific platforms
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		runtime "Release"
		optimize "on"	
	



