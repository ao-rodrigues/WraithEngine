//
// Application.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"

#include "Core/Application.h"

#include "Core/Engine.h"

namespace Wraith
{
    Application::Application(int windowWidth, int windowHeight, const std::string& name)
    {
        Engine::GetInstance().Init({windowWidth, windowHeight, name});
    }

    void Application::Run()
    {
        Engine::GetInstance().Run();
    }

    void Application::Shutdown()
    {
        Engine::GetInstance().Shutdown();
    }
}
