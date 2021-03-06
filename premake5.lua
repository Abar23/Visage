workspace "Visage"
    architecture "x86_64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    vendorIncludes = {}
    vendorIncludes["Glad"] = "Visage/vendor/Glad/include"
    vendorIncludes["GLFW"] = "Visage/vendor/GLFW/include"
    vendorIncludes["stb_image"] = "Visage/vendor/stb_image"
    
    group "Dependencies"
        include "Visage/vendor/Glad"
        include "Visage/vendor/GLFW"
    group ""

    project "Visage"
        location "Visage"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("obj/" .. outputDir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.inl",
            "%{prj.name}/vendor/stb_image/**.h",
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "_USE_MATH_DEFINES",
            "GLFW_INCLUDE_NONE"
        }

        includedirs
        {
            "%{prj.name}/src",
            "%{vendorIncludes.Glad}",
            "%{vendorIncludes.GLFW}",
            "%{vendorIncludes.stb_image}"
        }

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            runtime "Release"
            optimize "On"

    project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        
        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("obj/" .. outputDir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h"
        }

        defines
        {
            "_USE_MATH_DEFINES"
        }

        includedirs
        {
            "%{wks.name}/src",
            "%{vendorIncludes.Glad}",
            "%{vendorIncludes.GLFW}",
            "%{vendorIncludes.stb_image}"
        }

        links
        {
            "Visage"
        }

        filter "system:linux"
            systemversion "latest"

            links
            {
                "Glad",
                "GLFW",
                "dl",
                "pthread",
                "X11"
            }

        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            runtime "Release"
            optimize "On"