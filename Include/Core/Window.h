#pragma once
#include "Jade.h"

namespace Jade
{
	struct WindowDescriptor
	{
		String Title;
		Vector2<uint32> Position;
		Vector2<uint32> Size;
	};

	enum class EWindowState : uint8
	{
		EWS_Shown,
		EWS_Hidden
	};

	class Window
	{
	public:
		explicit Window(HINSTANCE Instance);
		~Window();

		bool Initialize(const WindowDescriptor& Descriptor);
		void SetWindowState(EWindowState WindowState);
		void Destroy() const;

	private:
		void GetPositionAndSize(
			Vector2<uint32> InPosition,
			Vector2<uint32> InSize,
			Vector2<uint32>& OutPosition,
			Vector2<uint32>& OutSize
		) const;
		void RegisterWindowClass();

	private:
		EWindowState CurrentState;
		struct Win32WindowInfo
		{
			HWND Handle;
			HINSTANCE Instance;
			WNDCLASSA WindowClass;
			static constexpr uint32 WindowStyle = (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME);
			static constexpr uint32 WindowExStyle = (WS_EX_APPWINDOW);
		} Win32Info;
	};
}
