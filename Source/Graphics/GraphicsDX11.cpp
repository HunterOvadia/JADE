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
        CreateSamplerState();
        CreateBlendState();
        Resize(OwningWindow->GetSize());
        return true;
    }

    void GraphicsDX11::Shutdown()
    {
        SAFE_RELEASE(Interface.BlendState);
        SAFE_RELEASE(Interface.SamplerState);
        SAFE_RELEASE(Interface.FramebufferRTV);
        SAFE_RELEASE(Interface.SwapChain);
        SAFE_RELEASE(Interface.DeviceContext);
        SAFE_RELEASE(Interface.Device);
    }

    void GraphicsDX11::CreateDevice()
    {
        D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

        ID3D11Device* TempDevice;
        ID3D11DeviceContext* TempDeviceContext;

        HR_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &TempDevice, nullptr, &TempDeviceContext));
        HR_CHECK(TempDevice->QueryInterface(UUIDOF(ID3D11Device1, Interface.Device)));
        HR_CHECK(TempDeviceContext->QueryInterface(UUIDOF(ID3D11DeviceContext1, Interface.DeviceContext)));

        SAFE_RELEASE(TempDeviceContext);
        SAFE_RELEASE(TempDevice);
    }

    void GraphicsDX11::CreateRenderTargetView()
    {
        ID3D11Texture2D* FramebufferTexture;
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
        SAFE_RELEASE(FramebufferTexture);
    }

    void GraphicsDX11::CreateSamplerState()
    {
        const D3D11_SAMPLER_DESC SamplerDesc =
        {
            .Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
            .AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
            .ComparisonFunc = D3D11_COMPARISON_NEVER,
            .MaxLOD = D3D11_FLOAT32_MAX
        };
        
        HR_CHECK(Interface.Device->CreateSamplerState(&SamplerDesc, &Interface.SamplerState));
    }

    void GraphicsDX11::CreateBlendState()
    {
        D3D11_BLEND_DESC BlendStateDesc =
        {
            .AlphaToCoverageEnable = FALSE,
            .IndependentBlendEnable = FALSE
        };
        BlendStateDesc.RenderTarget[0].BlendEnable = TRUE;
        BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
        BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
        BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        
        HR_CHECK(Interface.Device->CreateBlendState(&BlendStateDesc, &Interface.BlendState));
    }

    void GraphicsDX11::CreateSwapChain()
    {
        IDXGIDevice1* DXGIDevice;
        HR_CHECK(Interface.Device->QueryInterface(UUIDOF(IDXGIDevice1, DXGIDevice)));

        IDXGIAdapter* DXGIAdapter;
        HR_CHECK(DXGIDevice->GetAdapter(&DXGIAdapter));
        SAFE_RELEASE(DXGIDevice);
        
        IDXGIFactory2* DXGIFactory;
        HR_CHECK(DXGIAdapter->GetParent(UUIDOF(IDXGIFactory2, DXGIFactory)));
        SAFE_RELEASE(DXGIAdapter);

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
        SAFE_RELEASE(DXGIFactory);
        HR_CHECK(Interface.SwapChain->GetDesc1(&SwapChainDesc));

        CreateRenderTargetView();
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
