#ifndef DX12DYNAMICRHI_H
#define DX12DYNAMICRHI_H
#include <Engine/RHI/DynamicRHI.h>
#include <d3d12.h>
#include <dxgi1_5.h>
namespace GeometricEngine
{
	/**class GEOMETRIC_API DX12DynamicRHI : public DynamicRHI
	{
	public:
		DX12DynamicRHI();
		DX12DynamicRHI(IDXGIFactory4*, IDXGIAdapter*);
		~DX12DynamicRHI();
		virtual bool Initialize() override;

		virtual RHIViewport* RHICreateViewport(void*, U32, U32, bool) override;
		virtual void				RHIBegin() override;
		virtual void				RHIEnd() override;
		IDXGIFactory4* GetDXGIFactory() const { return DXGIFactory; }
		IDXGISwapChain3* GetDXGISwapChain() const { return DXGISwapChain; }
		ID3D12Device* GetDXDevice() const	{ return DXDevice; }
		IDXGIAdapter* GetDXGIAdapter() const	{ return DXGIAdapter; }
		bool InitDevice();
	private:
		ID3D12Device* DXDevice;
		IDXGIFactory4* DXGIFactory;
		IDXGIAdapter* DXGIAdapter;
		IDXGISwapChain3* DXGISwapChain;
	};*/
}

#endif // !DX11DynamicRHI_H
