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

	class Engine : public Singleton<Engine>
	{
	public:
		void Init(const EngineInitParams& initParams);
		void Shutdown();

	private:
		friend class Application;
		void Run();

		Window _window;
	};
	
}
