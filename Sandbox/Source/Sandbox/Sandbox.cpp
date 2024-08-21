#include <Wraith/Core/Launch/Launch.h>

class SandboxApp : public Wraith::Application
{
public:
	
};

Wraith::Application* CreateApplication()
{
	return new SandboxApp();
}
