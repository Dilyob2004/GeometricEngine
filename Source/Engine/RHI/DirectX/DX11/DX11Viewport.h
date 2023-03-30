#ifndef DX11SWAPCHAIN_H
#define DX11SWAPCHAIN_H

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
		DX11Viewport(const DX11DynamicRHI*, const RHIViewportDefinition&);
		~DX11Viewport();

		void Resize(const DX11DynamicRHI*, U32, U32, RHIPixelFormat, bool);
		void Present();

		U32 GetWidth() const { return Definition.Width; }
		U32 GetHeight() const { return Definition.Height; }

		RHITexture2D* GetBackBufferView() const { return BackBuffer; }
		IDXGISwapChain* GetDXGISwapChain() const { return DXGISwapChain; }


		RHIViewportDefinition GetDefinition() const { return Definition; }
	private:
		IDXGISwapChain* DXGISwapChain;
		RHIViewportDefinition Definition;
		RHITexture2D* BackBuffer;
	};
}
#endif // !DXSWAPCHAIN_H
