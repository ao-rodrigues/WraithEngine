project "Sandbox"
    kind "WindowedApp"
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
        ["Source/*"] = { "Source/Sandbox/**.h", "Source/Sandbox/**.cpp" }
    }

	includedirs
	{
		"Source",
        "%{wks.location}/Engine/Source"
	}

    links
    {
        "WraithEngine" 
    }