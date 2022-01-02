#pragma once

#include <string>

#include "Core/Singleton.h"
#include "Platform/Window.h"

namespace Wraith
{
	struct EngineInitParams
	{
		int windowWidth;
		int windowHeight;
		std::string windowTitle;
	};

	class Engine final : public Singleton<Engine>
	{
	public:
		void Init(const EngineInitParams& initParams);
		void Run();
		void Shutdown();

	private:
		friend class Renderer;

		Window& GetWindow() const
		{
			return *_window;
		}

		std::unique_ptr<Window> _window;
	};

#define WRAITH_ENGINE Engine::Instance()
}
