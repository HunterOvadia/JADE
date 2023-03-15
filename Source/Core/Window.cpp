#include "Jade.h"
#include "Core/Window.h"
#include "Graphics/GraphicsDX11.h"
#include "Math/Vector.h"

namespace Jade
{
	static LRESULT CALLBACK Win32MessagePump(HWND Handle, uint32 Message, WPARAM WParam, LPARAM LParam)
	{
		auto GetWindowParam = [Handle]() -> Window*
		{
			return reinterpret_cast<Window*>(GetWindowLongPtr(Handle, GWLP_USERDATA));
		};
		
		switch (Message)
		{
			case WM_CREATE:
			{
				const CREATESTRUCT* CreateStruct = reinterpret_cast<CREATESTRUCT*>(LParam);
				Window* WindowParam = static_cast<Window*>(CreateStruct->lpCreateParams);
				SetWindowLongPtr(Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(WindowParam));
			}
			break;
			case WM_SIZE:
			{
				Window* WindowParam = GetWindowParam();
				WindowParam->Resize(Vector2<int32>(LOWORD(LParam), HIWORD(LParam)));
			}
			break;

			case WM_DESTROY:
			{
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
		
		GetPositionAndSize(Descriptor.Position, Descriptor.Size, Position, Size);
		Win32Info.Handle = CreateWindowExA(
			Win32WindowInfo::WindowExStyle, Win32Info.WindowClass.lpszClassName,
			Descriptor.Title.CString(), Win32WindowInfo::WindowStyle,
			Position.X(), Position.Y(), Size.X(), Size.Y(), 
			nullptr, nullptr, Win32Info.Instance, this
		);

		if(!Win32Info.Handle)
		{
			return false;
		}
		
		GraphicsRenderer = UniquePtr<GraphicsDX11>(new GraphicsDX11(this));
		if(!GraphicsRenderer)
		{
			return false;
		}

		if(!GraphicsRenderer->Initialize())
		{
			return false;
		}

		return true;
	}

	void Window::Destroy() const
	{
		if(GraphicsRenderer)
		{
			GraphicsRenderer->Shutdown();
		}
		
		if (Win32Info.Handle)
		{
			DestroyWindow(Win32Info.Handle);
			UnregisterClassA(Win32Info.WindowClass.lpszClassName, Win32Info.Instance);
		}
	}

	void Window::Resize(Vector2<int32> InSize)
	{
		Size = InSize;
		GraphicsRenderer->Resize(InSize);
	}

	void Window::Update()
	{
	}

	void Window::Render()
	{
		GraphicsRenderer->PreRender();
		GraphicsRenderer->Render();
		GraphicsRenderer->PostRender();
	}

	void Window::UpdateAndRender(Application& App)
	{
		MSG Message;
		while (PeekMessageA(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
			if (Message.message == WM_QUIT)
			{
				App.Shutdown();
				break;
			}
		}

		if(App.IsRunning())
		{
			Update();
			Render();
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

	void Window::GetPositionAndSize(const Vector2<int32> InPosition, const Vector2<int32> InSize, Vector2<int32>& OutPosition, Vector2<int32>& OutSize) const
	{
		OutPosition = InPosition;
		OutSize = InSize;

		RECT BorderRect = {0, 0, 0, 0 };
		AdjustWindowRectEx(&BorderRect, Win32WindowInfo::WindowStyle, 0, Win32WindowInfo::WindowExStyle);
		
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
