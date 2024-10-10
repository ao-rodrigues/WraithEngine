include "Dependencies.lua"

workspace "WraithEngine"
    configurations
    {
        "DebugEditor",
        "DevelopmentEditor",
        "ShippingEditor",
        "DebugGame",
        "DevelopmentGame",
        "ShippingGame"
    }
    platforms {
        "Win64"
    }

    flags { "MultiProcessorCompile"}

    startproject "Sandbox"


OutputDir = "%{cfg.buildcfg}/%{cfg.platform}"

group "Engine"
    include "Editor"
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

filter "configurations:Debug*"
    runtime "Debug"
    symbols "On"
    optimize "Off"
    defines
    {
        "WR_CONFIG_DEBUG"
    }

filter "configurations:Development*"
    runtime "Release"
    symbols "On"
    optimize "Debug"
    defines
    {
        "WR_CONFIG_DEVELOPMENT"
    }

filter "configurations:Shipping*"
    runtime "Release"
    symbols "Off"
    optimize "Full"
    defines
    {
        "WR_CONFIG_SHIPPING"
    }

filter { "platforms:Win64", "configurations:Debug*" }
    targetsuffix "-Win64-Debug"

filter { "platforms:Win64", "configurations:Development*" }
    targetsuffix "-Win64-Development"

filter { "platforms:Win64", "configurations:Shipping*" }
    targetsuffix "-Win64-Shipping"