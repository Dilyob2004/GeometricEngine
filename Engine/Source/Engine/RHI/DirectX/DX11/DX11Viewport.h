#ifndef DX11SWAPCHAIN_H
#define DX11SWAPCHAIN_H

#include <Engine/RHI/RHIResources.h>
#include <Engine/RHI/DynamicRHI.h>
#include <dxgi.h>
#include <d3d11_4.h>
namespace GeometricEngine
{
	class DX11DynamicRHI;
	class DX11Viewport : public RHIViewport
	{
	public:
		DX11Viewport();
		DX11Viewport(const DX11DynamicRHI*, const RHIViewportDefinition&);
		~DX11Viewport();

		void Resize(const DX11DynamicRHI*, U32, U32, bool);
		void Present();

		void WaitForNextFrame();

		RHITexture2D* GetBackBufferView() const { return BackBuffer; }
		IDXGISwapChain* GetDXGISwapChain() const { return DXGISwapChain; }


		RHIViewportDefinition GetDefinition() const { return Definition; }
	private:
		ID3D11Device5* DXDevice5;
		ID3D11DeviceContext4* DXDeviceContext4;

		IDXGISwapChain* DXGISwapChain;
		RHIViewportDefinition Definition;
		RHITexture2D* BackBuffer;

		ID3D11Fence* Fence ;
		U64 FenceValue;
		HANDLE FenceEvent;
	};
}
#endif // !DXSWAPCHAIN_H
