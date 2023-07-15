#ifndef DX11DYNAMICRHI_H
#define DX11DYNAMICRHI_H
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>

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
	virtual bool Initialize() FINAL OVERRIDE;

	virtual RHIViewport*			RHICreateViewport(const RHIViewportDefinition&) FINAL OVERRIDE;
	virtual RHIRenderTarget*		RHIGetViewportBackBuffer(const RHIViewport*) FINAL OVERRIDE;

	virtual bool					RHICreateGUI(void*) FINAL OVERRIDE;
	virtual void					RHIBeginFrameGUI() FINAL OVERRIDE;
	virtual void					RHIEndFrameGUI() FINAL OVERRIDE;

	virtual RHIPixelShader*			RHICreatePixelShader(const TArray<U32>& ) FINAL OVERRIDE;
	virtual RHIVertexShader*		RHICreateVertexShader(const TArray<U32>&) FINAL OVERRIDE;		


	virtual RHIVertexBuffer*		RHICreateVertexBuffer(const void*, U32, U32, U32 = 0, RHIUsage = RHIUsage::Default) FINAL OVERRIDE;
	virtual RHIIndexBuffer*			RHICreateIndexBuffer(const U32*, U32, RHIUsage = RHIUsage::Default) FINAL OVERRIDE;
	virtual RHIUniformBuffer*		RHICreateUniformBuffer(const void*, U32, RHIUsage = RHIUsage::Default) FINAL OVERRIDE;

	virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinition&, U8* Data)FINAL OVERRIDE;
	virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition&) FINAL OVERRIDE;

	virtual RHIRenderTarget*		RHICreateRenderTarget(const RHITextureDefinition&)FINAL OVERRIDE;
	virtual RHIDepthTarget*			RHICreateDepthTarget(const RHITextureDefinition&)FINAL OVERRIDE;

	virtual void					RHISetPixelShaderSampler(RHISamplerState*) FINAL OVERRIDE;
	virtual void					RHISetVertexShaderSampler(RHISamplerState*) FINAL OVERRIDE;
	virtual void					RHISetPixelShaderTexture(RHITexture2D*) FINAL OVERRIDE;
	virtual void					RHISetVertexShaderTexture(RHITexture2D*) FINAL OVERRIDE;

	virtual void					RHISetPixelShaderUniformBuffer(RHIUniformBuffer*) FINAL OVERRIDE;
	virtual void					RHISetVertexShaderUniformBuffer(RHIUniformBuffer*) FINAL OVERRIDE;


	virtual void					RHIUpdateUniformBuffer(RHIUniformBuffer*, const void*, U32) FINAL OVERRIDE;
	virtual void					RHIUpdateVertexBuffer(RHIVertexBuffer*, const void*, U32) FINAL OVERRIDE;
	virtual void					RHIUpdateIndexBuffer(RHIIndexBuffer*, const void*, U32) FINAL OVERRIDE;

	virtual void					RHIDrawPrimitiveIndexed(RHIVertexBuffer*, RHIIndexBuffer*,U32, U32, DrawType type = DrawType::Triangles) FINAL OVERRIDE;
	virtual void					RHIDrawPrimitive(RHIVertexBuffer*, U32, U32, DrawType type = DrawType::Triangles) FINAL OVERRIDE;



	virtual void					RHISetScissorRect(U32, U32, U32, U32) FINAL OVERRIDE;

	virtual void					RHISetViewport(F32, F32, F32, F32) FINAL OVERRIDE;
	virtual void					RHIResizeViewport(RHIViewport*, U32, U32, bool) FINAL OVERRIDE;

	virtual void					RHIBeginFrameViewport(RHIViewport*) FINAL OVERRIDE;
	virtual void					RHIBeginFrameViewportDepth(RHIViewport*, RHIDepthTarget*)OVERRIDE;
	virtual void					RHIEndFrameViewport(RHIViewport*) FINAL OVERRIDE;



	virtual void					RHISetRenderTarget(RHIRenderTarget*) FINAL OVERRIDE;
	virtual void					RHISetRenderTarget(RHIRenderTarget*, RHIDepthTarget*) FINAL OVERRIDE;
	virtual void					RHICopyRenderTarget(RHIRenderTarget*, RHIRenderTarget*) FINAL OVERRIDE;
	virtual void					RHIResizeRenderTarget(RHIRenderTarget**, U32, U32)  FINAL OVERRIDE;

	virtual void					RHIClearRenderTarget(RHIRenderTarget*, F32, F32, F32, F32) FINAL OVERRIDE;
	virtual void					RHIClearDepthTarget(RHIDepthTarget*, bool UseDepth, bool UseStencil, F32 Depth) FINAL OVERRIDE;


	bool InitDevice();


	virtual RHIPipelineState*		RHICreatePipelineState(const RHIPipelineStateDefinition&) FINAL OVERRIDE;
	virtual void					RHISetPipelineState(RHIPipelineState*) FINAL OVERRIDE;

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

#endif // !DX11DynamicRHI_H
