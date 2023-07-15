#ifndef DYNAMICRHI_H
#define DYNAMICRHI_H
#include <Engine/RHI/RHIResources.h>
#include <Engine/Math/Vector4.h>

#define GPU_VENDOR_ID_AMD 0x1002
#define GPU_VENDOR_ID_INTEL 0x8086
#define GPU_VENDOR_ID_NVIDIA 0x10DE
#define GPU_VENDOR_ID_MICROSOFT 0x1414

class GEOMETRIC_API DynamicRHI
{
public:
		
	static DynamicRHI*				CreateDynamicRHI();
		
	virtual ~DynamicRHI() {}

	virtual bool Initialize() = 0;


	virtual RHIViewport*			RHICreateViewport(const RHIViewportDefinition& ) = 0;
	virtual RHIRenderTarget*		RHIGetViewportBackBuffer(const RHIViewport*) = 0;
	virtual void					RHISetViewport(F32, F32, F32, F32) = 0;
	virtual void					RHIBeginFrameViewport(RHIViewport* ) = 0;
	virtual void					RHIBeginFrameViewportDepth(RHIViewport*, RHIDepthTarget*) = 0;

	virtual void					RHIEndFrameViewport(RHIViewport* ) = 0;
	virtual void					RHIResizeViewport(RHIViewport*, U32, U32, bool) = 0;
	virtual void					RHISetScissorRect(U32, U32, U32, U32) = 0;

	virtual void					RHISetRenderTarget(RHIRenderTarget*) = 0;
	virtual void					RHISetRenderTarget(RHIRenderTarget*, RHIDepthTarget*) = 0;
	virtual void					RHICopyRenderTarget(RHIRenderTarget*, RHIRenderTarget*) = 0;
	virtual void					RHIResizeRenderTarget(RHIRenderTarget**, U32, U32) = 0;

	virtual void					RHIClearRenderTarget(RHIRenderTarget*, F32, F32, F32, F32) = 0;
	virtual void					RHIClearDepthTarget(RHIDepthTarget*, bool, bool, F32) = 0;



	virtual bool					RHICreateGUI(void*) = 0;
	virtual void					RHIBeginFrameGUI() = 0;
	virtual void					RHIEndFrameGUI() = 0;

	virtual RHIPixelShader*			RHICreatePixelShader(const TArray<U32>&) = 0;
	virtual RHIVertexShader*		RHICreateVertexShader(const TArray<U32>&) = 0;

	virtual RHIVertexBuffer*		RHICreateVertexBuffer(const void*, U32 , U32, U32 = 0, RHIUsage = RHIUsage::Default) = 0;
	virtual RHIIndexBuffer*			RHICreateIndexBuffer(const U32*, U32, RHIUsage = RHIUsage::Default) = 0;
	virtual RHIUniformBuffer*		RHICreateUniformBuffer(const void*, U32, RHIUsage = RHIUsage::Default) = 0;


	virtual void					RHIUpdateUniformBuffer(RHIUniformBuffer*, const void*, U32) = 0;
	virtual void					RHIUpdateVertexBuffer(RHIVertexBuffer*, const void*, U32) = 0;
	virtual void					RHIUpdateIndexBuffer(RHIIndexBuffer*, const void*, U32) = 0;

	virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinition&, U8* Data) = 0;


	virtual RHIRenderTarget*		RHICreateRenderTarget(const RHITextureDefinition& ) = 0;
	virtual RHIDepthTarget*			RHICreateDepthTarget(const RHITextureDefinition& ) = 0;

	virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition& ) = 0;




	virtual RHIPipelineState*		RHICreatePipelineState(const RHIPipelineStateDefinition&) = 0;
	virtual void					RHISetPipelineState(RHIPipelineState* ) = 0;

	virtual void					RHISetPixelShaderSampler(RHISamplerState*) = 0;
	virtual void					RHISetVertexShaderSampler(RHISamplerState*) = 0;

	virtual void					RHISetPixelShaderTexture(RHITexture2D*) = 0;
	virtual void					RHISetVertexShaderTexture(RHITexture2D*) = 0;


	virtual void					RHISetPixelShaderUniformBuffer(RHIUniformBuffer*) = 0;
	virtual void					RHISetVertexShaderUniformBuffer(RHIUniformBuffer*) = 0;
			

	virtual void					RHIDrawPrimitiveIndexed(RHIVertexBuffer*, RHIIndexBuffer*, U32, U32, DrawType type = DrawType::Triangles) = 0;
	virtual void					RHIDrawPrimitive(RHIVertexBuffer*, U32, U32, DrawType type = DrawType::Triangles) = 0;

};
extern GEOMETRIC_API DynamicRHI* GDynamicRHI;
extern GEOMETRIC_API bool InitializeDynamicRHI();

#endif // !DYNAMICRHI_H
