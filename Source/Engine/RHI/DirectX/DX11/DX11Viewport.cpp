
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	ID3D11Texture2D* D3DCreateTexture2D(ID3D11Device* DXDevice,
										U32 BindFlag, 
										U32 MipLevels,
										U32 Width, 
										U32 Height, 
										DXGI_FORMAT Format)
	{
		D3D11_TEXTURE2D_DESC Descriptor;
		SMemory::Zero(&Descriptor, sizeof(Descriptor));
		Descriptor.ArraySize = 1;
		Descriptor.Usage = D3D11_USAGE_DEFAULT;
		Descriptor.BindFlags = BindFlag;
		Descriptor.Format = Format;
		Descriptor.Width = Width;
		Descriptor.Height = Height;
		Descriptor.MipLevels = MipLevels;
		Descriptor.MiscFlags = 0;
		Descriptor.SampleDesc.Count = 1;
		Descriptor.SampleDesc.Quality = 0;
		Descriptor.CPUAccessFlags = 0;
		ID3D11Texture2D* Result = NULL;
		if (FAILED(DXDevice->CreateTexture2D(&Descriptor, NULL, &Result)))
		{
			LOG("Error: [DX11RHI] Failed to create 2D texture!");
			return NULL;
		}
		return Result;
	}

	static ID3D11Texture2D* GetSwapChainBackBuffer(IDXGISwapChain* DXSwapChain)
	{

	}
	DX11Viewport::DX11Viewport()
		: DXGISwapChain(NULL)
		, DXRenderTargetView(NULL)
		, DXShaderResourceView(NULL)
		, DXDepthStencilView(NULL)
		, Width(0)
		, Height(0)
		, EnabledFullScreen(false)
		, EnabledVSync(false)
		, HandleWindow(NULL)
	{
	}
	DX11Viewport::DX11Viewport(const DX11DynamicRHI* RHI, HWND Window, U32 SizeWidth, U32 SizeHeight, bool IsFullScreen)
		: DXGISwapChain(NULL)
		, DXRenderTargetView(NULL)
		, DXShaderResourceView(NULL)
		, DXDepthStencilView(NULL)
		, Width(SizeWidth)
		, Height(SizeHeight)
		, EnabledFullScreen(IsFullScreen)
		, EnabledVSync(true)
		, HandleWindow(Window)
	{

		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		SMemory::Zero(&SwapChainDescriptor, sizeof(SwapChainDescriptor));
		SwapChainDescriptor.BufferDesc.Width = Width;
		SwapChainDescriptor.BufferDesc.Height = Height;
		SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
		SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		SwapChainDescriptor.BufferCount = 2;
		SwapChainDescriptor.SampleDesc.Count = 2;
		SwapChainDescriptor.SampleDesc.Quality = 0;
		SwapChainDescriptor.OutputWindow = HandleWindow;
		SwapChainDescriptor.Windowed = !EnabledFullScreen;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		if (FAILED(RHI->GetDXGIFactory()->CreateSwapChain(RHI->GetDXDevice(), &SwapChainDescriptor, &DXGISwapChain)))
		{
			LOG("Error: [DX11RHI] Failed to create a swapchain!");
			exit(-1);
		}

		RHI->GetDXGIFactory()->MakeWindowAssociation(HandleWindow, DXGI_MWA_NO_WINDOW_CHANGES);


		CreateBackBuffer(RHI, Width, Height);

		PostMessage(HandleWindow, WM_PAINT, 0, 0);

	}

	void DX11Viewport::CreateBackBuffer(const DX11DynamicRHI* RHI, U32 Width, U32 Height)
	{

		ID3D11Texture2D* BackBuffer = NULL;

		DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		if (BackBuffer)
		{
			if (FAILED(RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, NULL, &DXRenderTargetView)))
			{
				LOG("Error: [DX11RHI] Failed to Create a RenderTargetView!");
				exit(-1);
			}

			/*8if (FAILED(RHI->GetDXDevice()->CreateShaderResourceView(BackBuffer, NULL, &DXShaderResourceView)))
			{
				LOG("Error: [DX11RHI] Failed to Create a ShaderResourceView!");
				exit(-1);
			}*/


			/**ID3D11Texture2D* DepthTexture = D3DCreateTexture2D(RHI->GetDXDevice(), D3D11_BIND_DEPTH_STENCIL,
				1, Width, Height, DXGI_FORMAT_D24_UNORM_S8_UINT);


			D3D11_DEPTH_STENCIL_VIEW_DESC ViewDesc;
			SMemory::Zero(&ViewDesc, sizeof(ViewDesc));
			ViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			ViewDesc.Texture2D.MipSlice = 0;
			ViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			if (FAILED(RHI->GetDXDevice()->CreateDepthStencilView(DepthTexture, &ViewDesc, &DXDepthStencilView)))
			{
				LOG("Error: [DX11RHI] Failed to Create a DepthStencilView!");
				exit(-1);
			}*/
		}
		else
		{
			LOG("Error: [DX11RHI] Failed to get a back buffer !");
			exit(-1);
		}
		BackBuffer->Release();
	}
	DX11Viewport::~DX11Viewport()
	{
		DXGISwapChain->Release();
		DXRenderTargetView->Release();
		DXShaderResourceView->Release();
		DXDepthStencilView->Release();
	}

	void DX11Viewport::Resize(const DX11DynamicRHI* RHI, U32 SizeWidth, U32 SizeHeight, bool)
	{
		DXRenderTargetView->Release();
		DXShaderResourceView->Release();
		DXDepthStencilView->Release();

		DXGISwapChain->ResizeBuffers(1, SizeWidth, SizeHeight, DXGI_FORMAT_UNKNOWN, 0);
		CreateBackBuffer(RHI, SizeWidth, SizeHeight);
	}
	void DX11Viewport::Present()
	{
		if (FAILED(DXGISwapChain->Present(EnabledVSync, 0)))
		{
			LOG("Error: [DX11RHI] Present failed!");
				exit(-1);
		}
	}
	RHIViewport* DX11DynamicRHI::RHICreateViewport(void* Window, U32 Width, U32 Height, bool EnableFullScreen)
	{
		return new DX11Viewport(this, (HWND)Window, Width, Height, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIClearViewport(const RHIViewport* Viewport, F32 r, F32 g, F32 b, F32 a)
	{
		F32 Colos[] = { r, g, b, a };
		DXDeviceContext->ClearRenderTargetView(((DX11Viewport*)Viewport)->GetDXRenderTargetView(), Colos);
	}
	void DX11DynamicRHI::RHIResizeViewport(const RHIViewport* InViewport, U32 SizeWidth, U32 SizeHeight, bool EnableFullScreen)
	{
		((DX11Viewport*)InViewport)->Resize(this, SizeWidth, SizeHeight, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIBegin(const RHIViewport* Viewport)
	{
		RHIClearViewport(Viewport, 0, 0, 0, 1);
		RHISetViewport(0, 0, 0, 800, 600, 1);
		DXDeviceContext->OMSetRenderTargets(1, ((DX11Viewport*)Viewport)->GetInitDXRenderTargetView(), NULL);
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
	void DX11DynamicRHI::RHIEnd(const RHIViewport* Viewport)
	{
		((DX11Viewport*)Viewport)->Present();
	}
}