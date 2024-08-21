#pragma once

namespace Wraith
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual void Run() = 0;
	};

	Application* CreateApplication();
}
