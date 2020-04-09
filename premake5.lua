workspace "Visage"
    architecture "x86_64"
    startproject "Visage"

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
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("obj/" .. outputDir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
            "%{prj.name}/vendor/stb_image/**.h",
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
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
            "Glad",
            "GLFW",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "GLFW_INCLUDE_NONE"
            }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            runtime "Release"
            optimize "On"
