#pragma once
#include "Application.h"
#include "Jade.h"

namespace Jade
{
	class GraphicsDX11;

	struct WindowDescriptor
	{
		String Title;
		Vector2<int32> Position;
		Vector2<int32> Size;
	};

	enum class EWindowState : uint8
	{
		EWS_Shown,
		EWS_Hidden
	};

	struct Win32WindowInfo
	{
		HWND Handle;
		HINSTANCE Instance;
		WNDCLASSA WindowClass;
		static constexpr uint32 WindowStyle = (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME);
		static constexpr uint32 WindowExStyle = (WS_EX_APPWINDOW);
	};

	class Window
	{
	public:
		explicit Window(HINSTANCE Instance);
		~Window();

		GraphicsDX11* GetGraphicsRenderer() const { return GraphicsRenderer.Get(); }
		const Vector2<int32>& GetSize() const { return Size; }
		Win32WindowInfo& GetWindowInfo() { return Win32Info; }
		bool Initialize(const WindowDescriptor& Descriptor);
		void SetWindowState(EWindowState WindowState);
		void Destroy() const;

		void Resize(Vector2<int32> InSize);
		void UpdateAndRender(Application& App);

	private:
		void GetPositionAndSize(
			Vector2<int32> InPosition,
			Vector2<int32> InSize,
			Vector2<int32>& OutPosition,
			Vector2<int32>& OutSize
		) const;
		void RegisterWindowClass();
		void Update();
		void Render();
		
	private:
		UniquePtr<GraphicsDX11> GraphicsRenderer;
		EWindowState CurrentState;
		Win32WindowInfo Win32Info;
		Vector2<int32> Size;
		Vector2<int32> Position;
	};
}
