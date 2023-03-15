#pragma once
#include "Jade.h"
#include "Graphics/GraphicsDX11.h"

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

		bool IsRunning() const { return bIsRunning; }
		bool Initialize(HINSTANCE InInstance);
		void Shutdown();
		void TickFrame();
		
		SharedPtr<Window> CreateAndSetActiveWindow(const WindowDescriptor& Descriptor, EWindowState WindowState);

	private:
		SharedPtr<Window> CreateNewWindow(const WindowDescriptor& Descriptor, EWindowState WindowState) const;
	
	private:
		bool bIsRunning = false;
		HINSTANCE Instance;
		SharedPtr<Window> ActiveWindow;
	};
}
