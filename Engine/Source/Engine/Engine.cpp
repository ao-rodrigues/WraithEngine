#include "Engine.h"

#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Platform/Window.h"

namespace Wraith
{
	void Engine::Init(const EngineInitParams& initParams)
	{
		Debug::Logger::Init();
		LOG_DEBUG("Staring Wraith Engine...");

		_window = std::make_unique<Window>(initParams.windowWidth, initParams.windowHeight, initParams.windowTitle);

		Renderer::Instance().Init();
	}

	void Engine::Shutdown()
	{
		Renderer::Instance().Shutdown();
		Debug::Logger::Shutdown();
	}

	void Engine::Run()
	{
		while (!_window->ShouldClose())
		{
			_window->PollEvents();
			Renderer::Instance().DrawFrame();
		}

		Shutdown();
	}
}
