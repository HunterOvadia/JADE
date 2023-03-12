#include "Jade.h"
#include "Application.h"
#include "UniquePtr.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	Jade::UniquePtr<Jade::Application> Application(new Jade::Application());
	if (Application->Init())
	{
		Jade::WindowDescriptor Descriptor =
		{
			.Title = "Window Title",
			.Position = Jade::Vector2<uint32>(100 ,100),
			.Size = Jade::Vector2<uint32>(1280, 720)
		};

		if (Application->MakeWindow(Descriptor))
		{
			Application->Poll();
		}
	}

	Application->Shutdown();
	return 0;
}