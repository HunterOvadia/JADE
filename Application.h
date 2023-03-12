#pragma once
#include "Jade.h"
#include "SharedPtr.h"

namespace Jade
{
	class Window;
	struct WindowDescriptor;
	class Application
	{
	public:
		Application();
		~Application();
		bool Init();
		void Shutdown();
		void Poll();

		Jade::SharedPtr<Jade::Window> MakeWindow(const WindowDescriptor& Descriptor);

	private:
		void PumpMessages();
		void Update();
		void Render();

		bool RegisterWindowClass();
		void GetWindowPositionAndSize(
			Vector2<uint32> InPosition,
			Vector2<uint32> InSize,
			Vector2<uint32>& OutPosition,
			Vector2<uint32>& OutSize
		);

	private:
		bool bIsRunning = false;
		Jade::SharedPtr<Jade::Window> ActiveWindow;
		//UniquePtr<Jade::Window> Window;
		
	};
}