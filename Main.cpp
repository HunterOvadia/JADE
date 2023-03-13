#include "Jade.h"
#include "Application.h"
#include "UniquePtr.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, int CmdShow)
{
	const Jade::UniquePtr<Jade::Application> Application(new Jade::Application());
	if (Application->Init(Instance))
	{
		const Jade::WindowDescriptor Descriptor =
		{
			.Title = "Window Title",
			.Position = Jade::Vector2<uint32>(100 ,100),
			.Size = Jade::Vector2<uint32>(1280, 720)
		};

		const Jade::SharedPtr<Jade::Window> MainWindow = Application->CreateAndSetActiveWindow(Descriptor);
		if(MainWindow)
		{
			MainWindow->Show();
		}

		Application->Poll();
	}

	Application->Shutdown();
	return 0;
}
