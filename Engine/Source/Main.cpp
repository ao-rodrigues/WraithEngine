#include "wrpch.h"
#include "Engine/Application.h"

int main()
{
	Wraith::Application app(800, 600, "Wraith Engine Demo");

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
