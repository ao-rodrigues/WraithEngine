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

		_window.Create(initParams.windowWidth, initParams.windowHeight, initParams.windowTitle);

		Renderer::Instance().Init(_window.GetGLFWWindow());
	}

	void Engine::Shutdown()
	{
		Renderer::Instance().Shutdown();
		Debug::Logger::Shutdown();
	}

	void Engine::Run()
	{
		while (!_window.ShouldClose())
		{
			_window.PollEvents();
			Renderer::Instance().DrawFrame();
		}

		Shutdown();
	}
}
