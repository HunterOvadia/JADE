#include "Application.h"
#include "Window.h"

namespace Jade
{
	Application::~Application()
	{
		Shutdown();
	}
	
	bool Application::Init(HINSTANCE InInstance)
	{
		Instance = InInstance;
		bIsRunning = true;
		return bIsRunning;
	}
	
	SharedPtr<Window> Application::CreateAndSetActiveWindow(const WindowDescriptor& Descriptor)
	{
		SharedPtr<Window> ResultWindow(new Window(Instance, Descriptor));
		if(ResultWindow)
		{
			ActiveWindow = ResultWindow;
		}
		return ResultWindow;
	}

	void Application::Shutdown()
	{
		
	}
	
	void Application::Poll()
	{
		while (bIsRunning)
		{
			PumpMessages();
			Update();
			Render();
		}
	}
	
	void Application::PumpMessages()
	{
		MSG Message;
		while (PeekMessageA(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
			if (Message.message == WM_QUIT)
			{
				bIsRunning = false;
				break;
			}
		}
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
		// Render Start (Clear)

		// Push to Renderer

		// Render End (Present)
	}
}

