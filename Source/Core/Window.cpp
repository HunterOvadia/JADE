#include "Jade.h"
#include "Core/Window.h"
#include "Math/Vector.h"

namespace Jade
{
	static LRESULT CALLBACK Win32MessagePump(HWND Handle, uint32 Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{
			case WM_DESTROY:
			{
				// TODO(HO): For any window closed, this will close the application.
				PostQuitMessage(0);
			}
			break;

			default:
			{
				return DefWindowProcA(Handle, Message, WParam, LParam);
			}
		}

		return DefWindowProcA(Handle, Message, WParam, LParam);
	}

	
	Window::Window(HINSTANCE Instance)
		: Win32Info()
	{
		Win32Info.Instance = Instance;
		SetWindowState(EWindowState::EWS_Hidden);
	}

	Window::~Window()
	{
		Destroy();
	}
	
	bool Window::Initialize(const WindowDescriptor& Descriptor)
	{
		RegisterWindowClass();
		
		Vector2<uint32> WindowPosition, WindowSize;
		GetPositionAndSize(Descriptor.Position, Descriptor.Size, WindowPosition, WindowSize);
		Win32Info.Handle = CreateWindowExA(
			Win32Info.WindowExStyle, Win32Info.WindowClass.lpszClassName,
			Descriptor.Title.CString(), Win32Info.WindowStyle,
			WindowPosition.X(), WindowPosition.Y(), WindowSize.X(), WindowSize.Y(), 
			nullptr, nullptr, Win32Info.Instance, nullptr
		);

		return Win32Info.Handle != nullptr;
	}

	void Window::Destroy() const
	{
		if (Win32Info.Handle)
		{
			DestroyWindow(Win32Info.Handle);
			UnregisterClassA(Win32Info.WindowClass.lpszClassName, Win32Info.Instance);
		}
	}
	
	void Window::SetWindowState(const EWindowState WindowState)
	{
		CurrentState = WindowState;
		if(Win32Info.Handle)
		{
			ShowWindow(Win32Info.Handle, WindowState == EWindowState::EWS_Shown ? SW_SHOW : SW_HIDE);
		}
	}

	void Window::GetPositionAndSize(const Vector2<uint32> InPosition, const Vector2<uint32> InSize, Vector2<uint32>& OutPosition, Vector2<uint32>& OutSize) const
	{
		OutPosition = InPosition;
		OutSize = InSize;

		RECT BorderRect = { 0 };
		AdjustWindowRectEx(&BorderRect, Win32Info.WindowStyle, 0, Win32Info.WindowExStyle);
		
		OutPosition.X() += BorderRect.left;
		OutPosition.Y() += BorderRect.top;
		OutSize.X() += (BorderRect.right - BorderRect.left);
		OutSize.Y() += (BorderRect.bottom - BorderRect.top);
	}

	void Window::RegisterWindowClass()
	{
		// NOTE(HO): We will just pump every window the same for now...
		Win32Info.WindowClass =
		{
			.style = CS_VREDRAW | CS_HREDRAW,
			.lpfnWndProc = Win32MessagePump,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = Win32Info.Instance,
			.hIcon = LoadIcon(Win32Info.Instance, IDI_APPLICATION),
			.hCursor = LoadCursor(nullptr, IDC_ARROW),
			.hbrBackground = nullptr,
			.lpszClassName = "JadeWindowClass"
		};

		RegisterClassA(&Win32Info.WindowClass);
	}
}
