#pragma once
#include "Jade.h"

namespace Jade
{
	enum class EWindowState : uint8;
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

		SharedPtr<Window> CreateNewWindow(const WindowDescriptor& Descriptor, EWindowState WindowState) const;
		SharedPtr<Window> CreateAndSetActiveWindow(const WindowDescriptor& Descriptor, EWindowState WindowState);

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
