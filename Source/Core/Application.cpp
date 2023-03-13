#include "Core/Application.h"
#include "Core/Window.h"
#include "Jade.h"

namespace Jade
{
	bool Application::Init(HINSTANCE InInstance)
	{
		Instance = InInstance;
		bIsRunning = true;
		return bIsRunning;
	}

	Application::~Application()
	{
		Shutdown();
	}

	void Application::Shutdown()
	{
		bIsRunning = false;
	}
	
	SharedPtr<Window> Application::CreateNewWindow(const WindowDescriptor& Descriptor, const EWindowState WindowState) const
	{
		const SharedPtr<Window> ResultWindow(new Window(Instance));
		if(ResultWindow)
		{
			if(ResultWindow->Initialize(Descriptor))
			{
				ResultWindow->SetWindowState(WindowState);
				return ResultWindow;
			}
		}
		
		return SharedPtr<Window>();
	}
	
	SharedPtr<Window> Application::CreateAndSetActiveWindow(const WindowDescriptor& Descriptor, const EWindowState WindowState)
	{
		SharedPtr<Window> ResultWindow = CreateNewWindow(Descriptor, WindowState);
		if(ResultWindow)
		{
			ActiveWindow = ResultWindow;
		}
		
		return ResultWindow;
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
		// Input Polling
	}

	void Application::Render()
	{
		// Render Start (Clear)

		// Push to Renderer

		// Render End (Present)
	}
}

