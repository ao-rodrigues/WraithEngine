project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{prj.location}/out/bin/" .. OutputDir)
    objdir ("%{prj.location}/out/int/" .. OutputDir)

    vpaths
    {
        ["Source/*"] = { "src/Sandbox/**.h", "src/Sandbox/**.cpp" }
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