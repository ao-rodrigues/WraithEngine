#include "wrpch.h"
#include "Wraith/Application.h"

#include "Engine.h"

namespace Wraith {
    Application::Application(int windowWidth, int windowHeight, const std::string& name) {
        Engine::GetInstance().Init({windowWidth, windowHeight, name});
    }

    void Application::Run() {
        Engine::GetInstance().Run();
    }

    void Application::Shutdown() {
        Engine::GetInstance().Shutdown();
    }
}
