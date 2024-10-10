project "WraithEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{prj.location}/out/bin/" .. OutputDir)
    objdir ("%{prj.location}/out/int/" .. OutputDir)

    vpaths
    {
        ["Source/*"] = { "src/Wraith/**.h", "src/Wraith/**.cpp" }
    }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{IncludeDirs.VulkanSDK}"
    }

    --[[
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
    --]]