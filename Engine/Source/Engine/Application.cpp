#include "Application.h"

#include "Engine/Engine.h"

namespace Wraith
{
	Application::Application(int windowWidth, int windowHeight, const std::string& name)
	{
		Engine::Instance().Init({windowWidth, windowHeight, name});
	}

	void Application::Run()
	{
		Engine::Instance().Run();
	}

	void Application::Shutdown()
	{
		Engine::Instance().Shutdown();
	}
}
