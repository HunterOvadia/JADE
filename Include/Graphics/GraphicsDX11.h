#pragma once
#include "Jade.h"

namespace Jade
{
    class Window;
    struct DXInterface
    {
        ID3D11Device* Device;
        ID3D11DeviceContext* DeviceContext;
        IDXGISwapChain1* SwapChain;
        ID3D11RenderTargetView* FramebufferRTV;

    };

    template<typename T>
    struct ScopedComPtr
    {
    public:
        ScopedComPtr() : Pointer(nullptr) {}
        ScopedComPtr(T* Input) : Pointer(Input) {}
        ~ScopedComPtr()
        {
            SAFE_RELEASE(Pointer);
        }

        operator T*() const { return Pointer; }
        T** operator&() { return &Pointer; }
        T* operator->() const { return Pointer; }

    private:
        T* Pointer;
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
        
    private:
        DXInterface Interface;
        Window* OwningWindow;
    };
}
