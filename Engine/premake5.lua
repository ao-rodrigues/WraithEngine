project "WraithEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{prj.location}/Binaries/" .. OutputDir)
    objdir ("%{prj.location}/Intermediate/" .. OutputDir)

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    vpaths
    {
        ["Source/*"] = { "Source/Wraith/**.h", "Source/Wraith/**.cpp" }
    }

    includedirs
    {
        "Source/Wraith",
        "%{IncludeDirs.VulkanSDK}"
    }

    filter "configurations:Debug"
        links
        {
            "%{Libraries.ShaderC_Debug}",
            "%{Libraries.SPIRV_Cross_Debug}",
            "%{Libraries.SPIRV_Cross_GLSL_Debug}"
        }

    filter "configurations:Development"
        links
        {
            "%{Libraries.ShaderC_Release}",
            "%{Libraries.SPIRV_Cross_Release}",
            "%{Libraries.SPIRV_Cross_GLSL_Release}"
        }

    filter "configurations:Shipping"
        links
        {
            "%{Libraries.ShaderC_Release}",
            "%{Libraries.SPIRV_Cross_Release}",
            "%{Libraries.SPIRV_Cross_GLSL_Release}"
        }