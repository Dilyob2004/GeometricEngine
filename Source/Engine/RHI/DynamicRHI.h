#ifndef DYNAMICRHI_H
#define DYNAMICRHI_H
#include <Engine/RHI/RHIResources.h>
#include <Engine/Core/EngineModule.h>
namespace GeometricEngine
{
	class GEOMETRIC_API DynamicRHI
	{
	public:
		static DynamicRHI* CreateDynamicRHI();
		virtual ~DynamicRHI() {}
		virtual bool Initialize() = 0;

		virtual RHIViewport*		RHICreateViewport(void*, U32, U32, bool) = 0;
		virtual RHIPixelShader*		RHICreatePixelShader(const TVector<U32>&) = 0;
		virtual RHIVertexShader*	RHICreateVertexShader(const TVector<U32>&) = 0;
		virtual RHIVertexLayout*	RHICreateVertexLayout(const RHIVertexShader*, const VertexLayoutGroup&) = 0;

		virtual RHIVertexBuffer*	RHICreateVertexBuffer(void*, U32) = 0;
		virtual RHIIndexBuffer*		RHICreateIndexBuffer(U32*, U32) = 0;

		virtual RHIConstantBuffer*  RHICreateConstantBuffer(void*, U32) = 0;


		virtual void				RHIBindPixelShader(const RHIPixelShader*) = 0;
		virtual void				RHIBindVertexShader(const RHIVertexShader*) = 0;
		virtual void				RHIBindVertexBuffer(const RHIVertexBuffer*, const RHIVertexLayout* , U32 Offset = 0) = 0;
		virtual void				RHIBindIndexBuffer(const RHIIndexBuffer*) = 0;

		virtual void				RHIUpdateConstantBuffer(const RHIConstantBuffer*, void*, U32) = 0;
		virtual void				RHIBindVSConstantBuffer(const RHIConstantBuffer*) = 0;
		virtual void				RHIBindPSConstantBuffer(const RHIConstantBuffer*) = 0;

		virtual void				RHIBindVertexLayout(const RHIVertexLayout*) = 0;


		virtual void				RHIDraw(U32, U32, DrawType type = DrawType::TRIANGLES) = 0;

		virtual void RHISetViewport(F32, F32, F32, F32, F32, F32) = 0;
		virtual void RHIResizeViewport(U32, U32, bool) = 0;
		virtual void RHIBegin() = 0;
		virtual void RHIEnd() = 0;
	};
	extern DynamicRHI* GDynamicRHI;
}
#endif // !DYNAMICRHI_H
