#ifndef DX11DYNAMICRHI_H
#define DX11DYNAMICRHI_H
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
namespace GeometricEngine
{
	struct DX11Adapter
	{
		DX11Adapter()
			: Index(-1)
			, MaxSupportFeatureLevel((D3D_FEATURE_LEVEL)0)
			, Description()
		{
		}
		I32 Index;
		D3D_FEATURE_LEVEL MaxSupportFeatureLevel;
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

		virtual RHIViewport*			RHICreateViewport(const RHIViewportDefinition&) override;
		virtual RHITexture2D*			RHIGetViewportBackBuffer(const RHIViewport*)override;

		virtual RHIPixelShader*			RHICreatePixelShader(const TVector<U32>& )override;
		virtual RHIVertexShader*		RHICreateVertexShader(const TVector<U32>&) override;		
		virtual RHIVertexLayout*		RHICreateVertexLayout(const RHIVertexShader*, const TVector<BufferElement>&) override;
		virtual RHIVertexBuffer*		RHICreateVertexBuffer(void*, U32) override;
		virtual RHIIndexBuffer*			RHICreateIndexBuffer(U32*, U32) override;
		virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinitions&)override;
		virtual RHIConstantBuffer*		RHICreateConstantBuffer(void*, U32) override;
		

		virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition&) override;
		virtual RHIRasterizerState*		RHICreateRasterizerState(const RHIRasterizerStateDefinition&) override;
		virtual RHIBlendState*			RHICreateBlendState(const RHIBlendStateDefinition&) override;
		virtual RHIDepthStencilState*	RHICreateDepthStencilState(const RHIDepthStencilStateDefinition&) override;

		virtual void					RHISetDepthStencilState(const RHIDepthStencilState*)override;
		virtual void					RHISetBlendState(const RHIBlendState*) override;
		virtual void					RHISetRasterizerState(const RHIRasterizerState*) override;

		virtual void					RHISetSamplerState(const RHIPixelShader*, const RHISamplerState*)override;
		virtual void					RHISetTexture(const RHIPixelShader*, const RHITexture2D*) override;

		virtual void					RHISetConstantBuffer(const RHIVertexShader*, const RHIConstantBuffer*) override;
		virtual void					RHISetConstantBuffer(const RHIPixelShader*, const RHIConstantBuffer*) override;
		virtual void					RHISetPixelShader(const RHIPixelShader*) override;
		virtual void					RHISetVertexShader(const RHIVertexShader*) override;
		virtual void					RHISetVertexLayout(const RHIVertexLayout*) override;
		virtual void					RHISetVertexBuffer(const RHIVertexBuffer*, const RHIVertexLayout*, U32) override;
		virtual void					RHISetIndexBuffer(const RHIIndexBuffer*) override;

		virtual void					RHIUpdateConstantBuffer(const RHIConstantBuffer*, void*, U32) override;

		virtual void					RHIDrawPrimitiveIndexed(U32, U32, DrawType type = DrawType::Triangles) override;
		virtual void					RHIDrawPrimitive(U32, U32, DrawType type = DrawType::Triangles)override;

		virtual void					RHIClearViewport(const RHIViewport*, F32, F32, F32, F32);
		virtual void					RHISetViewport(F32, F32, F32, F32) override;
		virtual void					RHISetRenderTarget(const RHITexture *)override;
		virtual void					RHISetRenderTarget(const RHITexture*, const RHITexture*) override;
		virtual void					RHISetScissorRect(U32, U32, U32, U32)override;

		virtual void					RHIResizeViewport(const RHIViewport*, U32, U32, RHIPixelFormat, bool)override;
		virtual void					RHIBegin(const RHIViewport*)override;
		virtual void					RHIEnd(const RHIViewport*)override;


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
