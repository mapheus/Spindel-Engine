workspace "Spindel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Spindel/vendor/GLFW/include"
IncludeDir["Glad"] = "Spindel/vendor/Glad/include"
IncludeDir["ImGui"] = "Spindel/vendor/imgui"
IncludeDir["glm"] = "Spindel/vendor/glm"
IncludeDir["stb_image"] = "Spindel/vendor/stb_image"
IncludeDir["entt"] = "Spindel/vendor/entt/include"
IncludeDir["assimp"] = "Spindel/vendor/assimp/include"
IncludeDir["ImGuizmo"] = "Spindel/vendor/ImGuizmo"

group "Dependencies"
	include "Spindel/vendor/GLFW"
	include "Spindel/vendor/Glad"
	include "Spindel/vendor/imgui"
group ""

project "Spindel"
	location "Spindel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sppch.h"
	pchsource "Spindel/src/sppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.hpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGuizmo}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	libdirs
	{
		"%{prj.name}/vendor/assimp/lib"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"assimp-vc142-mtd.lib"
	}

	filter "files:Spindel/vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WINDOWS", 
			"SP_BUILD_DLL",
			"SP_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MT"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Spindel/vendor/spdlog/include",
		"Spindel/src",
		"Spindel/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Spindel"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MT"
		optimize "on"


		
project "SpindelWeb"
	location "SpindelWeb"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Spindel/vendor/spdlog/include",
		"Spindel/src",
		"Spindel/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"Spindel"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MT"
		optimize "on"