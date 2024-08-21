include "Dependencies.lua"

workspace "WraithEngine"
    configurations
    { 
        "Debug",
        "Development",
        "Shipping"
    }
    platforms {
        "Win64"
    }
    startproject "Sandbox"

    flags { "MultiProcessorCompile"}

OutputDir = "%{cfg.buildcfg}/%{cfg.platform}"

group "Engine"
    include "Engine"
group ""

group "Games"
    include "Sandbox"
group ""

filter "platforms:Win64"
    system "Windows"
    architecture "x64"
    defines
    {
        "WR_PLATFORM_WINDOWS"
    }

filter "configurations:Debug"
    runtime "Debug"
    symbols "On"
    optimize "Off"
    targetsuffix "-Debug"
    defines
    {
        "WR_CONFIG_DEBUG"
    }

filter "configurations:Development"
    runtime "Release"
    symbols "On"
    optimize "Debug"
    targetsuffix "-Development"
    defines
    {
        "WR_CONFIG_DEVELOPMENT"
    }

filter "configurations:Shipping"
    runtime "Release"
    symbols "Off"
    optimize "Full"
    targetsuffix "-Shipping"
    defines
    {
        "WR_CONFIG_SHIPPING"
    }