#include "Jade.h"
#include "Core/Application.h"
#include "Core/Window.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, int CmdShow)
{
	const Jade::UniquePtr<Jade::Application> Application(new Jade::Application());
	if (Application->Initialize(Instance))
	{
		const Jade::WindowDescriptor Descriptor =
		{
			.Title = "JADE Engine",
			.Position = Jade::Vector2<int32>(100,100),
			.Size = Jade::Vector2<int32>(1280, 720)
		};

		const Jade::SharedPtr<Jade::Window> MainWindow = Application->CreateAndSetActiveWindow(Descriptor, Jade::EWindowState::EWS_Shown);
		if(MainWindow)
		{
			while(Application->IsRunning())
			{
				Application->TickFrame();
			}
		}
	}

	Application->Shutdown();
	return 0;
}
