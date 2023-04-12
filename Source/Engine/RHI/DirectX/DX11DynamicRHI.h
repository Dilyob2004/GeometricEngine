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
		DX11DynamicRHI();
		DX11DynamicRHI(IDXGIFactory1 *, DX11Adapter);
		~DX11DynamicRHI();
		virtual bool Initialize() OVERRIDE;

		virtual RHIViewport*			RHICreateViewport(const RHIViewportDefinition&) OVERRIDE;
		virtual RHITexture2D*			RHIGetViewportBackBuffer(const RHIViewport*)OVERRIDE;

		virtual bool					RHICreateGUI(void*)OVERRIDE;
		virtual void					RHIBeginFrameGUI() OVERRIDE;
		virtual void					RHIEndFrameGUI() OVERRIDE;

		virtual RHIPixelShader*			RHICreatePixelShader(const TVector<U32>& )OVERRIDE;
		virtual RHIVertexShader*		RHICreateVertexShader(const TVector<U32>&) OVERRIDE;		
		virtual RHIVertexLayout*		RHICreateVertexLayout(const RHIVertexShader*, const TVector<BufferElement>&) OVERRIDE;
		virtual RHIVertexBuffer*		RHICreateVertexBuffer(void*, U32) OVERRIDE;
		virtual RHIIndexBuffer*			RHICreateIndexBuffer(U32*, U32) OVERRIDE;
		virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinition&)OVERRIDE;
		virtual RHIConstantBuffer*		RHICreateConstantBuffer(void*, U32) OVERRIDE;
		

		virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition&) OVERRIDE;
		virtual RHIRasterizerState*		RHICreateRasterizerState(const RHIRasterizerStateDefinition&) OVERRIDE;
		virtual RHIBlendState*			RHICreateBlendState(const RHIBlendStateDefinition&) OVERRIDE;
		virtual RHIDepthStencilState*	RHICreateDepthStencilState(const RHIDepthStencilStateDefinition&) OVERRIDE;

		virtual void					RHISetDepthStencilState(const RHIDepthStencilState*)OVERRIDE;
		virtual void					RHISetBlendState(const RHIBlendState*) OVERRIDE;
		virtual void					RHISetRasterizerState(const RHIRasterizerState*) OVERRIDE;

		virtual void					RHISetSamplerState(const RHIPixelShader*, const RHISamplerState*)OVERRIDE;
		virtual void					RHISetTexture(const RHIPixelShader*, const RHITexture2D*) OVERRIDE;

		virtual void					RHISetConstantBuffer(const RHIVertexShader*, const RHIConstantBuffer*) OVERRIDE;
		virtual void					RHISetConstantBuffer(const RHIPixelShader*, const RHIConstantBuffer*) OVERRIDE;
		virtual void					RHISetPixelShader(const RHIPixelShader*) OVERRIDE;
		virtual void					RHISetVertexShader(const RHIVertexShader*) OVERRIDE;
		virtual void					RHISetVertexLayout(const RHIVertexLayout*) OVERRIDE;
		virtual void					RHISetVertexBuffer(const RHIVertexBuffer*, const RHIVertexLayout*, U32) OVERRIDE;
		virtual void					RHISetIndexBuffer(const RHIIndexBuffer*) OVERRIDE;

		virtual void					RHIUpdateConstantBuffer(const RHIConstantBuffer*, void*, U32) OVERRIDE;

		virtual void					RHIDrawPrimitiveIndexed(U32, U32, DrawType type = DrawType::Triangles) OVERRIDE;
		virtual void					RHIDrawPrimitive(U32, U32, DrawType type = DrawType::Triangles) OVERRIDE;



		virtual void					RHISetScissorRect(U32, U32, U32, U32) OVERRIDE;

		virtual void					RHISetViewport(F32, F32, F32, F32) OVERRIDE;
		virtual void					RHIResizeViewport(const RHIViewport*, U32, U32, bool) OVERRIDE;

		virtual void					RHIBeginFrameViewport(const RHIViewport*) OVERRIDE;
		virtual void					RHIBeginFrameViewportDepth(const RHIViewport*, const RHITexture2D*)OVERRIDE;
		virtual void					RHIEndFrameViewport(const RHIViewport*) OVERRIDE;



		virtual void					RHISetRenderTarget(const RHITexture2D*) OVERRIDE;
		virtual void					RHISetRenderTarget(const RHITexture2D*, const RHITexture2D*) OVERRIDE;

		virtual void					RHIClearRenderTarget(const RHITexture2D*, F32, F32, F32, F32) OVERRIDE;
		virtual void					RHIClearDepthTarget(const RHITexture2D*, bool UseDepth, bool UseStencil, F32 Depth) OVERRIDE;


		bool InitDevice();



		IDXGIFactory1*			GetDXGIFactory() const { return DXGIFactory; }
		ID3D11Device*			GetDXDevice() const { return DXDevice; }
		ID3D11DeviceContext*	GetDXDeviceContext() const { return DXDeviceContext; }
	private:

		I32						DXAdapterIndex = -1;
		ID3D11Device*			DXDevice;
		ID3D11DeviceContext*	DXDeviceContext;
		IDXGIFactory1*			DXGIFactory;


		U32 DepthFlag;
		F32 ClearColor[4];
	};
}

#endif // !DX11DynamicRHI_H
