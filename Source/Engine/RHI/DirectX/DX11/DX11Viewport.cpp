
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/Platform/Platform.h>
#include <dwmapi.h>
#include <Engine/Core/Application.h>
namespace MeteorEngine
{
	ID3D11RenderTargetView* DXRenderTargetView;
	IDXGISwapChain* DXGISwapChain = NULL;

	DX11Viewport::DX11Viewport()
		:// DXGISwapChain(NULL) , 
		Width(0)
		, Height(0)
		, EnabledFullScreen(false)
		, EnabledVSync(false)
		, HandleWindow(NULL)
	{
	}
	DX11Viewport::DX11Viewport(const DX11DynamicRHI* RHI, HWND HWindow, u32 SizeWidth, u32 SizeHeight, bool IsFullScreen)
		: //DXRHIRHI ,
		  Width(SizeWidth)
		, Height(SizeHeight)
		, EnabledFullScreen(IsFullScreen)
		, EnabledVSync(true)
		, HandleWindow(HWindow)
	{
		IDXGIDevice* DXGIDevice = NULL;
		if (FAILED(RHI->GetDXDevice()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice))))
		{
			LOG("Error: DX11Viewport-?QueryInterface");
			return;
		}
		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		Platform::Memzero(&SwapChainDescriptor, sizeof(SwapChainDescriptor));
		/////////////////////////////////////////////////////////////////////////////////////////
		SwapChainDescriptor.BufferDesc.Width = Width;
		SwapChainDescriptor.BufferDesc.Height = Height;
		SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
		SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
		/////////////////////////////////////////////////////////////////////////////////////////
		SwapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDescriptor.BufferCount = 2;
		SwapChainDescriptor.SampleDesc.Count = 16;
		SwapChainDescriptor.SampleDesc.Quality = 0;
		SwapChainDescriptor.OutputWindow = HandleWindow;
		SwapChainDescriptor.Windowed = !EnabledFullScreen;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		/////////////////////////////////////////////////////////////////////////////////////////
		if (FAILED(RHI->GetDXGIFactory()->CreateSwapChain(DXGIDevice, &SwapChainDescriptor, &DXGISwapChain)))
		{
			LOG("Error: CreateSwapChain!");
			return;
		}
		RHI->GetDXGIFactory()->MakeWindowAssociation(HandleWindow, DXGI_MWA_NO_WINDOW_CHANGES);

		/////////////////////////////////////////////////////////////////////////////////////////
		ID3D11Texture2D* BackBuffer = NULL;
		DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		if (RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, NULL, &DXRenderTargetView) != S_OK)
		{
			LOG("Error: CreateRenderTargetView!");
			return;
		}
		BackBuffer->Release();

		PostMessage(HandleWindow, WM_PAINT, 0, 0);
	}
	DX11Viewport::~DX11Viewport()
	{
		DXGISwapChain->Release();
	}

	void DX11Viewport::Resize(const DX11DynamicRHI* RHI, u32 Width, u32 Height, bool)
	{
		DXRenderTargetView->Release();
		DXGISwapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);
		ID3D11Texture2D* BackBuffer = NULL;
		DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		if (RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, NULL, &DXRenderTargetView) != S_OK)
		{
			LOG("Error: CreateRenderTargetView!");
			return;
		}
		BackBuffer->Release();
	}
	void DX11Viewport::Present(bool vSync)
	{
		DXGISwapChain->Present(vSync, 0);
	}
	RHIViewport* DX11DynamicRHI::RHICreateViewport(void* Window, u32 Width, u32 Height, bool EnableFullScreen)
	{
		return new DX11Viewport(this, (HWND)Window, Width, Height, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIResizeViewport(u32 SizeWidth, u32 SizeHeight, bool EnableFullScreen)
	{
		DXViewport->Resize(this, SizeWidth, SizeHeight, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIBegin()
	{
		f32 Colos[] = { 0, 0, 0, 1 };
		DXDeviceContext->ClearRenderTargetView(DXRenderTargetView, Colos);

		RECT winRect;
		GetClientRect((HWND)Application::GetInstance().GetWindow().GetWindowPtr(), &winRect);
		D3D11_VIEWPORT viewport = {
		  0.0f,
		  0.0f,
		  (FLOAT)(winRect.right - winRect.left),
		  (FLOAT)(winRect.bottom - winRect.top),
		  0.0f,
		  1.0f };
		DXDeviceContext->RSSetViewports(1, &viewport);

		DXDeviceContext->OMSetRenderTargets(1, &DXRenderTargetView, NULL);
		DXDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}
	void DX11DynamicRHI::RHISetViewport(f32 MinX, f32 MinY, f32 MinZ, f32 MaxX, f32 MaxY, f32 MaxZ)
	{
		D3D11_VIEWPORT Viewport;
		Platform::Memzero(&Viewport, sizeof(D3D11_VIEWPORT));
		Viewport.TopLeftX	= MinX;
		Viewport.TopLeftY	= MinY;
		Viewport.MinDepth	= MinZ;
		Viewport.Width		= MaxX;
		Viewport.Height		= MaxY;
		Viewport.MaxDepth	= MaxZ;
		DXDeviceContext->RSSetViewports(1, &Viewport);
	}
	void DX11DynamicRHI::RHIEnd()
	{
		DXViewport->Present(true);
	}
}