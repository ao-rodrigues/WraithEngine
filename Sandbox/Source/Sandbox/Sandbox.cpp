#include <Wraith/Core/Launch.h>
#include "SandboxApp.h"

Wraith::Application* Wraith::CreateApplication()
{
	return new SandboxApp();
}
