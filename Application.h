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
		Application() = default;
		~Application();
		bool Init(HINSTANCE InInstance);
		void Shutdown();
		void Poll();
		SharedPtr<Window> CreateAndSetActiveWindow(const WindowDescriptor& Descriptor);

	private:
		void PumpMessages();
		void Update();
		void Render();

	private:
		HINSTANCE Instance;
		bool bIsRunning = false;
		SharedPtr<Window> ActiveWindow;
	};
}