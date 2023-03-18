#ifndef DX11SWAPCHAIN_H
#define DX11SWAPCHAIN_H

#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <Engine/RHI/DynamicRHI.h>
#include <dxgi.h>
#include <d3d11.h>
namespace GeometricEngine
{
	class DX11DynamicRHI;
	class DX11Viewport : public RHIViewport
	{
	public:
		DX11Viewport();
		DX11Viewport(const DX11DynamicRHI*, HWND, U32, U32, bool);
		~DX11Viewport();

		void Resize(const DX11DynamicRHI*, U32, U32, bool);
		void Present();

		U32 GetWidth() const { return Width; }
		U32 GetHeight() const { return Height; }
		RHITextureView* GetBackBufferView() const;
		IDXGISwapChain* GetDXGISwapChain() const { return DXGISwapChain; }




		ID3D11RenderTargetView* GetDXRenderTargetView() const { return DXRenderTargetView; }
		ID3D11RenderTargetView** GetInitDXRenderTargetView() { return &DXRenderTargetView; }
		ID3D11ShaderResourceView* GetDXShaderResourceView() const { return DXShaderResourceView; }
		ID3D11DepthStencilView* GetDXDepthStencilView() const { return DXDepthStencilView; }


		void CreateBackBuffer(const DX11DynamicRHI* RHI, U32 Width, U32 Height);
	private:
		IDXGISwapChain* DXGISwapChain;
		ID3D11RenderTargetView* DXRenderTargetView;
		ID3D11ShaderResourceView* DXShaderResourceView;
		ID3D11DepthStencilView* DXDepthStencilView;

		HWND HandleWindow;
		U32 Width = 0, Height = 0;

		bool EnabledVSync, EnabledFullScreen;
	};
}
#endif // !DXSWAPCHAIN_H
