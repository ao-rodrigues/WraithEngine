project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{prj.location}/Binaries/" .. OutputDir)
    objdir ("%{prj.location}/Intermediate/" .. OutputDir)

    vpaths
    {
        ["Source/*"] = { "Source/Sandbox/**.h", "Source/Sandbox/**.cpp" }
    }

    files
    {
        "Source/**.h",
        "Source/**.cpp"
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