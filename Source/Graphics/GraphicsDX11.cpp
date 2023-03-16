#include "Graphics/GraphicsDX11.h"
#include "Core/Window.h"
#include "Jade.h"

namespace Jade
{
    GraphicsDX11::GraphicsDX11(Window* InWindow)
        : Interface()
        , OwningWindow(InWindow)
    {
    }

    GraphicsDX11::~GraphicsDX11()
    {
        Shutdown();
    }

    bool GraphicsDX11::Initialize()
    {
        CreateDevice();
        CreateSwapChain();
        CreateRenderTargetView();
        Resize(OwningWindow->GetSize());
        return true;
    }

    void GraphicsDX11::Shutdown()
    {
        SAFE_RELEASE(Interface.FramebufferRTV);
        SAFE_RELEASE(Interface.SwapChain);
        SAFE_RELEASE(Interface.DeviceContext);
        SAFE_RELEASE(Interface.Device);
    }

    void GraphicsDX11::CreateDevice()
    {
        D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

        
        {
            UINT Flags = 0;
#if DEBUG_MODE
            Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
            HR_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flags, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &Interface.Device, nullptr, &Interface.DeviceContext));
        }

#if DEBUG_MODE
        {
            ScopedComPtr<ID3D11InfoQueue> Info;
            Interface.Device->QueryInterface(UUIDOF(ID3D11InfoQueue, Info));
            Info->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, TRUE);
            Info->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, TRUE);
        }
#endif
    }

    void GraphicsDX11::CreateRenderTargetView()
    {
        ScopedComPtr<ID3D11Texture2D> FramebufferTexture;
        HR_CHECK(Interface.SwapChain->GetBuffer(0, UUIDOF(ID3D11Texture2D, FramebufferTexture)));
        
        const D3D11_RENDER_TARGET_VIEW_DESC RTVDesc =
        {
            .Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
            .ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D,
            .Texture2D =
            {
                .MipSlice = 0
            }
        };
        
        HR_CHECK(Interface.Device->CreateRenderTargetView(FramebufferTexture, &RTVDesc, &Interface.FramebufferRTV));
    }
    
    void GraphicsDX11::CreateSwapChain()
    {
        ScopedComPtr<IDXGIDevice2> DXGIDevice;
        HR_CHECK(Interface.Device->QueryInterface(UUIDOF(IDXGIDevice2, DXGIDevice)));

        ScopedComPtr<IDXGIAdapter> DXGIAdapter;
        HR_CHECK(DXGIDevice->GetAdapter(&DXGIAdapter));
        
        ScopedComPtr<IDXGIFactory2> DXGIFactory;
        HR_CHECK(DXGIAdapter->GetParent(UUIDOF(IDXGIFactory2, DXGIFactory)));

        DXGI_SWAP_CHAIN_DESC1 SwapChainDesc =
        {
            .Width = 0,
            .Height = 0,
            .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
            .SampleDesc = {
                .Count = 1
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = 2,
            .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD
        };

        HR_CHECK(DXGIFactory->CreateSwapChainForHwnd(Interface.Device, OwningWindow->GetWindowInfo().Handle, &SwapChainDesc, nullptr, nullptr, &Interface.SwapChain));
        HR_CHECK(Interface.SwapChain->GetDesc1(&SwapChainDesc));
    }

    void GraphicsDX11::Resize(Vector2<int32> NewSize) const
    {
        const D3D11_VIEWPORT Viewport =
        {
            .Width = static_cast<float32>(NewSize.X()),
            .Height = static_cast<float32>(NewSize.Y()),
            .MaxDepth = 1.0f
        };

        if(Viewport.Width > 0 && Viewport.Height > 0)
        {
            Interface.DeviceContext->RSSetViewports(1, &Viewport);
        }
    }

    void GraphicsDX11::PreRender()
    {
        constexpr float Color[4] = { 0.09f, 0.09f, 0.1f, 1.0f };
        Interface.DeviceContext->OMSetRenderTargets(1, &Interface.FramebufferRTV, nullptr);     
        Interface.DeviceContext->ClearRenderTargetView(Interface.FramebufferRTV, Color);    
    }

    void GraphicsDX11::Render()
    {
    }

    void GraphicsDX11::PostRender()
    {
        HR_CHECK(Interface.SwapChain->Present(1, 0));
    }
}
