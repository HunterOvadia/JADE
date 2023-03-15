#pragma once
#include <d3d11_1.h>
#include "Math/Vector.h"

namespace Jade
{
    class Window;
    struct DXInterface
    {
        ID3D11Device1* Device;
        ID3D11DeviceContext1* DeviceContext;
        ID3D11SamplerState* SamplerState;
        ID3D11BlendState* BlendState;
        IDXGISwapChain1* SwapChain;
        ID3D11RenderTargetView* FramebufferRTV;
    };
    
    class GraphicsDX11
    {
    public:
        explicit GraphicsDX11(Window* InWindow);
        ~GraphicsDX11();

        bool Initialize();
        void Shutdown();
        void CreateSwapChain();
        void Resize(Vector2<int32> NewSize) const;

        void PreRender();
        void Render();
        void PostRender();
        
    private:
        void CreateDevice();
        void CreateRenderTargetView();
        void CreateSamplerState();
        void CreateBlendState();
        
    private:
        DXInterface Interface;
        Window* OwningWindow;
    };
}
