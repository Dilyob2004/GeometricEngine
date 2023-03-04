
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	ID3D11RenderTargetView* DXRenderTargetView = NULL;
	IDXGISwapChain* DXGISwapChain = NULL;

	DX11Viewport::DX11Viewport()
		: Width(0)
		, Height(0)
		, EnabledFullScreen(false)
		, EnabledVSync(false)
		, HandleWindow(NULL)
	{
	}
	DX11Viewport::DX11Viewport(const DX11DynamicRHI* RHI, HWND HWindow, U32 SizeWidth, U32 SizeHeight, bool IsFullScreen)
		: Width(SizeWidth)
		, Height(SizeHeight)
		, EnabledFullScreen(IsFullScreen)
		, EnabledVSync(true)
		, HandleWindow(HWindow)
	{
		IDXGIDevice* DXGIDevice = NULL;
		if (FAILED(RHI->GetDXDevice()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice))))
		{
			LOG("Error: [DIRECTX11] DX11Viewport -? QueryInterface");
			exit(-1);
		}
		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		SMemory::Zero(&SwapChainDescriptor, sizeof(SwapChainDescriptor));
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
		SwapChainDescriptor.SampleDesc.Count = 2;
		SwapChainDescriptor.SampleDesc.Quality = 0;
		SwapChainDescriptor.OutputWindow = HandleWindow;
		SwapChainDescriptor.Windowed = !EnabledFullScreen;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		/////////////////////////////////////////////////////////////////////////////////////////
		if (FAILED(RHI->GetDXGIFactory()->CreateSwapChain(DXGIDevice, &SwapChainDescriptor, &DXGISwapChain)))
		{
			LOG("Error: [DIRECTX11] Failed to Create a SwapChain!");
			exit(-1);
		}
		RHI->GetDXGIFactory()->MakeWindowAssociation(HandleWindow, DXGI_MWA_NO_WINDOW_CHANGES);

		/////////////////////////////////////////////////////////////////////////////////////////
		ID3D11Texture2D* BackBuffer = NULL;
		DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		if (BackBuffer) {
			if (FAILED(RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, NULL, &DXRenderTargetView)))
			{
				LOG("Error: [DIRECTX11] Failed to Create a RenderTargetView!");
				return;
			}
		}
		BackBuffer->Release();

		PostMessage(HandleWindow, WM_PAINT, 0, 0);
	}
	DX11Viewport::~DX11Viewport()
	{
		DXGISwapChain->Release();
	}

	void DX11Viewport::Resize(const DX11DynamicRHI* RHI, U32 SizeWidth, U32 SizeHeight, bool)
	{
		DXRenderTargetView->Release();
		DXGISwapChain->ResizeBuffers(0, SizeWidth, SizeHeight, DXGI_FORMAT_UNKNOWN, 0);
		ID3D11Texture2D* BackBuffer = NULL;
		DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		if (BackBuffer) 
		{
			if (FAILED(RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, NULL, &DXRenderTargetView)))
			{
				LOG("Error: [DirectX 11] Failed to Create a RenderTargetView!");
				return;
			}
		}
		BackBuffer->Release();
	}
	void DX11Viewport::Present(bool vSync)
	{
		DXGISwapChain->Present(vSync, 0);
	}
	RHIViewport* DX11DynamicRHI::RHICreateViewport(void* Window, U32 Width, U32 Height, bool EnableFullScreen)
	{
		return new DX11Viewport(this, (HWND)Window, Width, Height, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIResizeViewport(U32 SizeWidth, U32 SizeHeight, bool EnableFullScreen)
	{
		DXViewport->Resize(this, SizeWidth, SizeHeight, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIBegin()
	{
		F32 Colos[] = { 0, 0, 0, 1 };
		DXDeviceContext->ClearRenderTargetView(DXRenderTargetView, Colos);
		DXDeviceContext->OMSetRenderTargets(1, &DXRenderTargetView, NULL);

	}
	void DX11DynamicRHI::RHISetViewport(F32 MinX, F32 MinY, F32 MinZ, F32 MaxX, F32 MaxY, F32 MaxZ)
	{
		D3D11_VIEWPORT Viewport;
		SMemory::Zero(&Viewport, sizeof(D3D11_VIEWPORT));
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