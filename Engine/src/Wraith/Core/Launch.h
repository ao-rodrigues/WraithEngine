#pragma once

#include "Wraith/Core/Application.h"

extern Wraith::Application* Wraith::CreateApplication();

inline int main()
{
	Wraith::Application* app = Wraith::CreateApplication();

	app->Run();

	delete app;
}