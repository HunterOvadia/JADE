#pragma once
#include "Jade.h"
#include "String.h"
#include "Vector.h"

namespace Jade
{
	struct WindowDescriptor
	{
		String Title;
		Vector2<uint32> Position;
		Vector2<uint32> Size;
	};

	class Window
	{
	public:
		explicit Window(const WindowDescriptor& Descriptor);
		~Window();

	private:
		struct Win32WindowInfo
		{
			HWND Handle;
			HINSTANCE Instance;
			WNDCLASSA WindowClass;
			uint32 WindowStyle = (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZE | WS_MINIMIZEBOX | WS_THICKFRAME);
			uint32 WindowExStyle = (WS_EX_APPWINDOW);
		} 
		Win32Info;
	};
}