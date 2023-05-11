#ifndef DYNAMICRHI_H
#define DYNAMICRHI_H
#include <Engine/RHI/RHIResources.h>
#include <Engine/Math/Vector4.h>

#define GPU_VENDOR_ID_AMD 0x1002
#define GPU_VENDOR_ID_INTEL 0x8086
#define GPU_VENDOR_ID_NVIDIA 0x10DE
#define GPU_VENDOR_ID_MICROSOFT 0x1414

namespace GeometricEngine
{
	class GEOMETRIC_API DynamicRHI
	{
	public:
		
		static DynamicRHI*				CreateDynamicRHI();
		
		virtual ~DynamicRHI() {}

		virtual bool Initialize() = 0;


		virtual RHIViewport*			RHICreateViewport(const RHIViewportDefinition& ) = 0;
		virtual RHITexture2D*			RHIGetViewportBackBuffer(const RHIViewport*) = 0;
		virtual void					RHISetViewport(F32, F32, F32, F32) = 0;
		virtual void					RHIBeginFrameViewport(const RHIViewport*) = 0;
		virtual void					RHIBeginFrameViewportDepth(const RHIViewport*, RHITexture2D*) = 0;
		virtual void					RHIEndFrameViewport(const RHIViewport*) = 0;
		virtual void					RHIResizeViewport(const RHIViewport*, U32, U32, bool) = 0;
		virtual void					RHISetScissorRect(U32, U32, U32, U32) = 0;

		virtual void					RHISetRenderTarget(RHITexture2D*) = 0;
		virtual void					RHISetRenderTarget(RHITexture2D*, RHITexture2D*) = 0;
		virtual void					RHICopyRenderTarget(RHITexture2D*, RHITexture2D*) = 0;
		virtual void					RHIClearRenderTarget(RHITexture2D*, F32, F32, F32, F32) = 0;
		virtual void					RHIClearDepthTarget(RHITexture2D*, bool, bool, F32) = 0;



		virtual bool					RHICreateGUI(void*) = 0;
		virtual void					RHIBeginFrameGUI() = 0;
		virtual void					RHIEndFrameGUI() = 0;

		virtual RHIPixelShader*			RHICreatePixelShader(const TVector<U32>&) = 0;
		virtual RHIVertexShader*		RHICreateVertexShader(const TVector<U32>&) = 0;

		virtual RHIVertexBuffer*		RHICreateVertexBuffer(const void*, U32 , U32, U32 = 0) = 0;
		virtual RHIIndexBuffer*			RHICreateIndexBuffer(const U32*, U32) = 0;
		virtual RHIUniformBuffer*		RHICreateUniformBuffer(void*, U32) = 0;

		virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinition& ) = 0;
		virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition& ) = 0;



		virtual RHIPipelineState*		RHICreatePipelineState(const RHIPipelineStateDefinition&) = 0;
		virtual void					RHISetPipelineState(RHIPipelineState* ) = 0;

		virtual void					RHISetSamplerState(const RHIPixelShader*, const RHISamplerState*) = 0;
		virtual void					RHISetTexture(const RHIPixelShader*, const RHITexture2D*) = 0;

		virtual void					RHISetPixelShader(const RHIPixelShader*) = 0;
		virtual void					RHISetVertexShader(const RHIVertexShader*) = 0;

		virtual void					RHISetVertexBuffer(const RHIVertexBuffer*) = 0;

		virtual void					RHIUpdateUniformBuffer(const RHIUniformBuffer*, void*, U32) = 0;

		virtual void					RHISetUniformBuffer(const RHIVertexShader*, const RHIUniformBuffer*) = 0;
		virtual void					RHISetUniformBuffer(const RHIPixelShader*, const RHIUniformBuffer*) = 0;


		virtual void					RHIDrawPrimitiveIndexed(RHIIndexBuffer*, U32, U32, DrawType type = DrawType::Triangles) = 0;
		virtual void					RHIDrawPrimitive(U32, U32, DrawType type = DrawType::Triangles) = 0;





	};
	extern GEOMETRIC_API DynamicRHI* GDynamicRHI;
	extern GEOMETRIC_API bool InitializeDynamicRHI();
}
#endif // !DYNAMICRHI_H
