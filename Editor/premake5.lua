project "WraithEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{prj.location}/out/bin/" .. OutputDir)
    objdir ("%{prj.location}/out/int/" .. OutputDir)

    vpaths
    {
        ["Source/*"] = { "src/WraithEditor/**.h", "src/WraithEditor/**.cpp" }
    }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{wks.location}/Engine/src"
    }

    links
    {
        "WraithEngine" 
    }