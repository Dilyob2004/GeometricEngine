
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	static RHITexture2D* GetSwapChainBackBuffer(const DX11DynamicRHI* RHI, IDXGISwapChain* DXSwapChain)
	{
		ID3D11Texture2D* BackBuffer;
		ID3D11RenderTargetView* DXRenderTargetView;
		ID3D11ShaderResourceView* DXShaderResourceView;
		DXSwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
		D3D11_TEXTURE2D_DESC Descriptor;
		BackBuffer->GetDesc(&Descriptor);
		if (BackBuffer)
		{
			D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
			if (Descriptor.SampleDesc.Count > 1)
				RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			else
			{
				RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				RTVDesc.Texture2D.MipSlice = 0;
			}
			RTVDesc.Format = Descriptor.Format;
			if (FAILED(RHI->GetDXDevice()->CreateRenderTargetView(BackBuffer, &RTVDesc, &DXRenderTargetView)))
			{
				LOG("Error: [DX11RHI] Failed to Create a RenderTargetView!");
				
				exit(-1);
			}
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
			if (Descriptor.SampleDesc.Count > 1)
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
			else
			{
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				SRVDesc.Texture2D.MostDetailedMip = 0;
				SRVDesc.Texture2D.MipLevels = Descriptor.MipLevels;
			}
			SRVDesc.Format = Descriptor.Format;
			if (FAILED(RHI->GetDXDevice()->CreateShaderResourceView(BackBuffer, &SRVDesc, &DXShaderResourceView)))
			{
				LOG("Error: [DX11RHI] Failed to Create a ShaderResourceView!");
				exit(-1);
			}
		}
		else
		{
			LOG("Error: [DX11RHI] Failed to get a back buffer !");
			exit(-1);
		}
		RHITextureDefinition Definitions;
		Definitions.Format = RHIFormatToDX11Format(Descriptor.Format);
		Definitions.Width = Descriptor.Width;
		Definitions.Height = Descriptor.Height;
		Definitions.Flags = TF_RenderTarget | TF_ShaderResource;

		return new DX11Texture2D( BackBuffer, 
									DXRenderTargetView, 
									DXShaderResourceView,
									NULL, Definitions);
	}
	DX11Viewport::DX11Viewport()
		: DXGISwapChain(NULL)
		, BackBuffer(NULL)
		, Definition()
	{
	}
	DX11Viewport::DX11Viewport(const DX11DynamicRHI* RHI, const RHIViewportDefinition& Def)
		: Definition(Def)
	{
		HWND Window = (HWND)Definition.HandleWindow;
		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		SMemory::Zero(&SwapChainDescriptor, sizeof(SwapChainDescriptor));
		SwapChainDescriptor.BufferDesc.Width = Definition.Width;
		SwapChainDescriptor.BufferDesc.Height = Definition.Height;
		SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = Definition.RefreshRateNum;
		SwapChainDescriptor.BufferDesc.Format = RHIFormatToDX11Format(Def.Format);
		SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;


		SwapChainDescriptor.OutputWindow = Window;
		SwapChainDescriptor.Windowed = !Definition.FullScreen;


		SwapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		SwapChainDescriptor.BufferCount = 2;
		SwapChainDescriptor.SampleDesc.Count = 1;
		SwapChainDescriptor.SampleDesc.Quality = 0;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		if (FAILED(RHI->GetDXGIFactory()->CreateSwapChain(RHI->GetDXDevice(), &SwapChainDescriptor, &DXGISwapChain)))
		{
			LOG("Error: [DX11RHI] Failed to create a swapchain!\n");
			exit(-1);
		}

		RHI->GetDXGIFactory()->MakeWindowAssociation(Window, DXGI_MWA_NO_WINDOW_CHANGES);

		BackBuffer = GetSwapChainBackBuffer(RHI, DXGISwapChain);
		PostMessage(Window, WM_PAINT, 0, 0);

		DXDevice5 = (ID3D11Device5*)RHI->GetDXDevice();
		DXDeviceContext4 = (ID3D11DeviceContext4*)RHI->GetDXDeviceContext();
		if (FAILED(DXDevice5->CreateFence(0, D3D11_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence))))
		{
			LOG("Error: [DX11RHI] Failed to Create a Fence!\n");
			exit(-1);
		}
		FenceValue = 1;
		FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (!FenceEvent)
		{
			LOG("Error: [DX11RHI] Failed to Create a Event!\n");
			exit(-1);
		}

	}
	DX11Viewport::~DX11Viewport()
	{
		CloseHandle(FenceEvent);
		DXGISwapChain->Release();
		WaitForNextFrame();
	}

	void DX11Viewport::WaitForNextFrame()
	{

		const UINT64 OldFence = FenceValue;
		DXDeviceContext4->Signal(Fence, OldFence);
		FenceValue++;

		// Wait until the previous frame is finished.
		if (Fence->GetCompletedValue() < OldFence)
		{
			if (Fence->SetEventOnCompletion(OldFence, FenceEvent) != S_OK)
			{
				LOG("SetEventOnCompletion\n");
				exit(-1);
			}
			WaitForSingleObject(FenceEvent, INFINITE);
		}
	}
	void DX11Viewport::Resize(const DX11DynamicRHI* RHI, U32 SizeWidth, U32 SizeHeight, bool Fullscreen)
	{

		DYNAMIC_CAST(DX11Texture2D, OldBackBuffer, BackBuffer);
		OldBackBuffer->SafeRelease();
		Definition.FullScreen = Fullscreen;
		Definition.Width = SizeWidth;
		Definition.Height = SizeHeight;
		if (Fullscreen)
		{
			DXGI_MODE_DESC BufferDesc;
			SMemory::Zero(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.Width = SizeWidth;
			BufferDesc.Height = SizeHeight;
			BufferDesc.RefreshRate.Numerator = Definition.RefreshRateNum;
			BufferDesc.RefreshRate.Denominator = 1;
			BufferDesc.Format = RHIFormatToDX11Format(Definition.Format);
			BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			DXGISwapChain->ResizeTarget(&BufferDesc);
		}
		else
			DXGISwapChain->ResizeBuffers(2, SizeWidth, SizeHeight, RHIFormatToDX11Format(Definition.Format), DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

		BackBuffer = GetSwapChainBackBuffer(RHI, DXGISwapChain);
	}
	void DX11Viewport::Present()
	{
		if (FAILED(DXGISwapChain->Present(Definition.VSync, 0)))
		{
			LOG("Error: [DX11RHI] Present failed!");
				exit(-1);
		}
		WaitForNextFrame();
	}
	RHIViewport* DX11DynamicRHI::RHICreateViewport(const RHIViewportDefinition& Def)
	{
		return new DX11Viewport(this, Def);
	}
	void DX11DynamicRHI::RHIResizeViewport(const RHIViewport* ViewportRHI, U32 SizeWidth, U32 SizeHeight, bool EnableFullScreen)
	{
		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		Viewport->Resize(this, SizeWidth, SizeHeight, EnableFullScreen);
	}
	void DX11DynamicRHI::RHIBeginFrameViewport(const RHIViewport* ViewportRHI)
	{
		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		RHIClearRenderTarget(Viewport->GetBackBufferView(), 30, 30, 30, 30);
		RHISetRenderTarget(Viewport->GetBackBufferView());
	}	
	void DX11DynamicRHI::RHIBeginFrameViewportDepth(const RHIViewport* ViewportRHI, RHITexture2D* DepthTHI)
	{
		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		RHIClearRenderTarget(Viewport->GetBackBufferView(), 30, 30, 30, 30);
		RHIClearDepthTarget(DepthTHI, true, true, 1.0f);
		RHISetRenderTarget(Viewport->GetBackBufferView(), DepthTHI);
	}
	void DX11DynamicRHI::RHIEndFrameViewport(const RHIViewport* ViewportRHI)
	{
		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		Viewport->Present();
	}
	RHITexture2D* DX11DynamicRHI::RHIGetViewportBackBuffer(const RHIViewport* ViewportRHI)
	{
		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		return Viewport->GetBackBufferView();
	}
}