#ifndef DX11DYNAMICRHI_H
#define DX11DYNAMICRHI_H
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <d3d11.h>
namespace GeometricEngine
{
	struct DX11Adapter
	{
		I32 Index = -1;
		D3D_FEATURE_LEVEL MaxSupportFeatureLevel = (D3D_FEATURE_LEVEL)0;
		DXGI_ADAPTER_DESC Description;
	};
	class GEOMETRIC_API DX11DynamicRHI: public DynamicRHI
	{
	public:
		friend class DX11Viewport;
		DX11DynamicRHI();
		DX11DynamicRHI(IDXGIFactory1 *, DX11Adapter);
		~DX11DynamicRHI();
		virtual bool Initialize() override;

		virtual RHIViewport*		RHICreateViewport(void*, U32, U32, bool) override;
		virtual RHIPixelShader*		RHICreatePixelShader(const TVector<U32>& )override;
		virtual RHIVertexShader*	RHICreateVertexShader(const TVector<U32>&) override;		
		virtual RHIVertexLayout*	RHICreateVertexLayout(const RHIVertexShader*, const TVector<BufferElement>&) override;
		virtual RHIVertexBuffer*	RHICreateVertexBuffer(void*, U32) override;
		virtual RHIIndexBuffer*		RHICreateIndexBuffer(U32*, U32) override;
		virtual RHIConstantBuffer*  RHICreateConstantBuffer(void*, U32) override;

		virtual void				RHIBindVSConstantBuffer(const RHIConstantBuffer*) override;
		virtual void				RHIBindPSConstantBuffer(const RHIConstantBuffer*) override;
		virtual void				RHIUpdateConstantBuffer(const RHIConstantBuffer*, void*, U32) override;

		virtual void				RHIBindPixelShader(const RHIPixelShader*) override;
		virtual void				RHIBindVertexShader(const RHIVertexShader*) override;
		virtual void				RHIBindVertexLayout(const RHIVertexLayout*) override;

		virtual void				RHIDraw(U32, U32, DrawType) override;
		virtual void				RHIBindVertexBuffer(const RHIVertexBuffer*, const RHIVertexLayout*, U32) override;
		virtual void				RHIBindIndexBuffer(const RHIIndexBuffer*) override;


		virtual void				RHIClearViewport(const RHIViewport*, F32, F32, F32, F32);

		virtual void				RHISetViewport(F32, F32, F32, F32, F32, F32) override;
		virtual void				RHIResizeViewport(const RHIViewport*, U32, U32, bool)override;
		virtual void				RHIBegin(const RHIViewport*)override;
		virtual void				RHIEnd(const RHIViewport*)override;


		bool InitDevice();



		IDXGIFactory1*			GetDXGIFactory() const { return DXGIFactory; }
		ID3D11Device*			GetDXDevice() const { return DXDevice; }
		ID3D11DeviceContext*	GetDXDeviceContext() const { return DXDeviceContext; }
	private:

		TVector<DX11Viewport*> Viewport;


		I32						DXAdapterIndex = -1;
		ID3D11Device*			DXDevice;
		ID3D11DeviceContext*	DXDeviceContext;
		IDXGIFactory1*			DXGIFactory;
	};
}

#endif // !DX11DynamicRHI_H
