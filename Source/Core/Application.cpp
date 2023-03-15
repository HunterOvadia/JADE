#include "Core/Application.h"
#include "Core/Window.h"
#include "Jade.h"

namespace Jade
{
	bool Application::Initialize(HINSTANCE InInstance)
	{
		Instance = InInstance;
		bIsRunning = true;
		return true;
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
	
	void Application::TickFrame()
	{
		if(ActiveWindow)
		{
			ActiveWindow->UpdateAndRender(*this);
		}
	}
}

