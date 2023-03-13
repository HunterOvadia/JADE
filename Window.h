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
		explicit Window(HINSTANCE Instance, const WindowDescriptor& Descriptor);
		~Window();
		void Show() const;
		
	private:
		void GetPositionAndSize(
			Vector2<uint32> InPosition,
			Vector2<uint32> InSize,
			Vector2<uint32>& OutPosition,
			Vector2<uint32>& OutSize
		) const;
		bool RegisterWindowClass();

	private:
		struct Win32WindowInfo
		{
			HWND Handle;
			HINSTANCE Instance;
			WNDCLASSA WindowClass;
			static constexpr uint32 WindowStyle = (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZE | WS_MINIMIZEBOX | WS_THICKFRAME);
			static constexpr uint32 WindowExStyle = (WS_EX_APPWINDOW);
		} Win32Info;
	};
}