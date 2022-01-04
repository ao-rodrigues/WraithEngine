#pragma once

namespace Wraith
{
	class Application
	{
	public:
		Application(int windowWidth, int windowHeight, const std::string& name);

		void Run();

	private:
		void Shutdown();

	};
}
