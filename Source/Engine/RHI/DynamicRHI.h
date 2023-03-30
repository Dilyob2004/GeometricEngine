#ifndef DYNAMICRHI_H
#define DYNAMICRHI_H
#include <Engine/RHI/RHIResources.h>
#include <Engine/Core/EngineModule.h>
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

		virtual RHIPixelShader*			RHICreatePixelShader(const TVector<U32>&) = 0;
		virtual RHIVertexShader*		RHICreateVertexShader(const TVector<U32>&) = 0;
		virtual RHIVertexLayout*		RHICreateVertexLayout(const RHIVertexShader*, const TVector<BufferElement>&) = 0;

		virtual RHIVertexBuffer*		RHICreateVertexBuffer(void*, U32) = 0;
		virtual RHIIndexBuffer*			RHICreateIndexBuffer(U32*, U32) = 0;
		virtual RHIConstantBuffer*		RHICreateConstantBuffer(void*, U32) = 0;

		virtual RHITexture2D*			RHICreateTexture2D(const RHITextureDefinitions& ) = 0;
		
		virtual RHISamplerState*		RHICreateSamplerState(const RHISamplerStateDefinition& ) = 0;
		virtual RHIBlendState*			RHICreateBlendState(const RHIBlendStateDefinition& ) = 0;
		virtual RHIRasterizerState*		RHICreateRasterizerState(const RHIRasterizerStateDefinition& ) = 0;
		virtual RHIDepthStencilState*	RHICreateDepthStencilState(const RHIDepthStencilStateDefinition&) = 0;
		
		virtual void					RHISetRasterizerState(const RHIRasterizerState*) = 0;
		virtual void					RHISetBlendState(const RHIBlendState*) = 0;
		virtual void					RHISetDepthStencilState(const RHIDepthStencilState*) = 0;


		virtual void					RHISetSamplerState(const RHIPixelShader*, const RHISamplerState*) = 0;
		virtual void					RHISetTexture(const RHIPixelShader*, const RHITexture2D*) = 0;

		virtual void					RHISetPixelShader(const RHIPixelShader*) = 0;
		virtual void					RHISetVertexShader(const RHIVertexShader*) = 0;
		virtual void					RHISetVertexBuffer(const RHIVertexBuffer*, const RHIVertexLayout* , U32 Offset = 0) = 0;
		virtual void					RHISetIndexBuffer(const RHIIndexBuffer*) = 0;

		virtual void					RHIUpdateConstantBuffer(const RHIConstantBuffer*, void*, U32) = 0;
		virtual void					RHISetConstantBuffer(const RHIVertexShader*, const RHIConstantBuffer*) = 0;
		virtual void					RHISetConstantBuffer(const RHIPixelShader*, const RHIConstantBuffer*) = 0;

		virtual void					RHISetVertexLayout(const RHIVertexLayout*) = 0;


		virtual void					RHIDrawPrimitiveIndexed(U32, U32, DrawType type = DrawType::Triangles) = 0;
		virtual void					RHIDrawPrimitive(U32, U32, DrawType type = DrawType::Triangles) = 0;

		virtual void					RHISetViewport(F32, F32, F32, F32) = 0;
		virtual void					RHISetRenderTarget(const RHITexture*) = 0;
		virtual void					RHISetRenderTarget(const RHITexture*, const RHITexture*) = 0;
		virtual void					RHISetScissorRect(U32, U32, U32, U32) = 0;
		virtual void					RHIResizeViewport(const RHIViewport*, U32, U32, RHIPixelFormat, bool) = 0;
		virtual void					RHIBegin(const RHIViewport*) = 0;
		virtual void					RHIEnd(const RHIViewport*) = 0;
	};
	extern DynamicRHI* GDynamicRHI;
}
#endif // !DYNAMICRHI_H
