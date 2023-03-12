#include "Application.h"

namespace Jade
{
	static LRESULT CALLBACK Win32MessagePump(HWND Handle, uint32 Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			break;

			default:
			{
				return DefWindowProcA(Handle, Message, WParam, LParam);
			}
			break;
		}

		return DefWindowProcA(Handle, Message, WParam, LParam);
	}

	Application::Application()
	{
	}

	Application::~Application()
	{
		Shutdown();
	}
	
	bool Application::Init()
	{
		return true;
		/*Win32AppInfo.Instance = GetModuleHandleA(nullptr);

		if (!RegisterWindowClass())
		{
			return false;
		}
		
		if (ApplicationCreateWindow(Descriptor))
		{
			ShowWindow(Win32AppInfo.Handle, SW_SHOW);
			bIsRunning = true;
			return true;
		}
		
		return false;*/
	}
	
	Jade::SharedPtr<Jade::Window> Application::MakeWindow(const WindowDescriptor& Descriptor)
	{
		Jade::SharedPtr<Jade::Window> ResultWindow;

		Vector2<uint32> WindowPosition, WindowSize;
		GetWindowPositionAndSize(Descriptor.Position, Descriptor.Size, WindowPosition, WindowSize);

		Win32AppInfo.Handle = CreateWindowExA(
			Win32AppInfo.WindowExStyle, Win32AppInfo.WindowClass.lpszClassName,
			Descriptor.Title.CString(), Win32AppInfo.WindowStyle,
			WindowPosition.X(), WindowPosition.Y(), WindowSize.X(), WindowSize.Y(), 
			nullptr, nullptr, Win32AppInfo.Instance, nullptr
		);
		
		return Win32AppInfo.Handle != nullptr;
	}

	void Application::Shutdown()
	{
		if (Win32AppInfo.Handle)
		{
			DestroyWindow(Win32AppInfo.Handle);
			UnregisterClassA(Win32AppInfo.WindowClass.lpszClassName, Win32AppInfo.Instance);
		}
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

	bool Application::MakeWindow(const WindowDescriptor& Descriptor)
	{
		
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

	bool Application::RegisterWindowClass()
	{
		Win32AppInfo.WindowClass =
		{
			.style = CS_VREDRAW | CS_HREDRAW,
			.lpfnWndProc = Win32MessagePump,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = Win32AppInfo.Instance,
			.hIcon = LoadIcon(Win32AppInfo.Instance, IDI_APPLICATION),
			.hCursor = LoadCursor(nullptr, IDC_ARROW),
			.hbrBackground = nullptr,
			.lpszClassName = "JadeWindowClass"
		};

		return RegisterClassA(&Win32AppInfo.WindowClass);
	}

	void Application::GetWindowPositionAndSize(Vector2<uint32> InPosition, Vector2<uint32> InSize, Vector2<uint32>& OutPosition, Vector2<uint32>& OutSize)
	{
		OutPosition = InPosition;
		OutSize = InSize;

		RECT BorderRect = { 0 };
		AdjustWindowRectEx(&BorderRect, Win32AppInfo.WindowStyle, 0, Win32AppInfo.WindowExStyle);

		OutPosition.X() += BorderRect.left;
		OutPosition.Y() += BorderRect.top;
		OutSize.X() += (BorderRect.right - BorderRect.left);
		OutSize.Y() += (BorderRect.bottom - BorderRect.top);
	}
}

