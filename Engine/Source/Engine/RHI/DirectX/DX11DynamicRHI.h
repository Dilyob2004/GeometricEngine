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
		virtual RHITexture2D*			RHIGetViewportBackBuffer(const RHIViewport*) OVERRIDE;

		virtual bool					RHICreateGUI(void*)OVERRIDE;
		virtual void					RHIBeginFrameGUI() OVERRIDE;
		virtual void					RHIEndFrameGUI() OVERRIDE;

		virtual RHIPixelShader*			RHICreatePixelShader(const TVector<U32>& )OVERRIDE;
		virtual RHIVertexShader*		RHICreateVertexShader(const TVector<U32>&) OVERRIDE;		

		virtual RHIVertexBuffer*		RHICreateVertexBuffer(const void*, U32, U32, U32) OVERRIDE;
		virtual RHIIndexBuffer*			RHICreateIndexBuffer(const U32*, U32) OVERRIDE;
		virtual RHIUniformBuffer*		RHICreateUniformBuffer(void*, U32) OVERRIDE;

		virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinition&)OVERRIDE;
		virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition&) OVERRIDE;


		virtual void					RHISetSamplerState(const RHIPixelShader*, const RHISamplerState*)OVERRIDE;
		virtual void					RHISetTexture(const RHIPixelShader*, const RHITexture2D*) OVERRIDE;

		virtual void					RHISetUniformBuffer(const RHIVertexShader*, const RHIUniformBuffer*) OVERRIDE;
		virtual void					RHISetUniformBuffer(const RHIPixelShader*, const RHIUniformBuffer*) OVERRIDE;
		virtual void					RHISetPixelShader(const RHIPixelShader*) OVERRIDE;
		virtual void					RHISetVertexShader(const RHIVertexShader*) OVERRIDE;


		virtual void					RHISetVertexBuffer(const RHIVertexBuffer*) OVERRIDE;		
		virtual void					RHIUpdateUniformBuffer(const RHIUniformBuffer*, void*, U32) OVERRIDE;

		virtual void					RHIDrawPrimitiveIndexed(RHIIndexBuffer*,U32, U32, DrawType type = DrawType::Triangles) OVERRIDE;
		virtual void					RHIDrawPrimitive(U32, U32, DrawType type = DrawType::Triangles) OVERRIDE;



		virtual void					RHISetScissorRect(U32, U32, U32, U32) OVERRIDE;

		virtual void					RHISetViewport(F32, F32, F32, F32) OVERRIDE;
		virtual void					RHIResizeViewport(const RHIViewport*, U32, U32, bool) OVERRIDE;

		virtual void					RHIBeginFrameViewport(const RHIViewport*) OVERRIDE;
		virtual void					RHIBeginFrameViewportDepth(const RHIViewport*, RHITexture2D*)OVERRIDE;
		virtual void					RHIEndFrameViewport(const RHIViewport*) OVERRIDE;



		virtual void					RHISetRenderTarget(RHITexture2D*) OVERRIDE;
		virtual void					RHISetRenderTarget(RHITexture2D*, RHITexture2D*) OVERRIDE;
		virtual void					RHICopyRenderTarget(RHITexture2D*, RHITexture2D*) OVERRIDE;

		virtual void					RHIClearRenderTarget(RHITexture2D*, F32, F32, F32, F32) OVERRIDE;
		virtual void					RHIClearDepthTarget(RHITexture2D*, bool UseDepth, bool UseStencil, F32 Depth) OVERRIDE;


		bool InitDevice();


		virtual RHIPipelineState*		RHICreatePipelineState(const RHIPipelineStateDefinition&) override;
		virtual void					RHISetPipelineState(RHIPipelineState*) override;

		IDXGIFactory1*			GetDXGIFactory() const { return DXGIFactory; }
		ID3D11Device*			GetDXDevice() const { return DXDevice; }
		ID3D11DeviceContext*	GetDXDeviceContext() const { return DXDeviceContext; }
	private:

		I32						DXAdapterIndex = -1;
		ID3D11Device*			DXDevice;
		ID3D11DeviceContext*	DXDeviceContext;
		IDXGIFactory1*			DXGIFactory;


		U32 DepthFlag { 0 };
		F32 ClearColor[4] { 0, 0, 0, 1 };
		F32 BlendFactor[4] { 0, 0, 0, 0 };
	};
}

#endif // !DX11DynamicRHI_H
