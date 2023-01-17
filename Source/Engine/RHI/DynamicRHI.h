#ifndef DYNAMICRHI_H
#define DYNAMICRHI_H
#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
namespace MeteorEngine
{
	class METEOR_API DynamicRHI
	{
	public:
		static DynamicRHI* CreateDynamicRHI();
		virtual ~DynamicRHI() {}
		virtual void Init() = 0;

		virtual RHIViewport*		RHICreateViewport(void*, u32, u32, bool) = 0;
		virtual RHIPixelShader*		RHICreatePixelShader(const std::vector<u32>&) = 0;
		virtual RHIVertexShader*	RHICreateVertexShader(const std::vector<u32>&) = 0;
		virtual RHIVertexLayout*	RHICreateVertexLayout(const RHIVertexShader*, const VertexLayoutGroup&) = 0;

		virtual RHIVertexBuffer*	RHICreateVertexBuffer(void*, u32) = 0;
		virtual RHIIndexBuffer*		RHICreateIndexBuffer(void*, u32) = 0;

		virtual void				RHIBindPixelShader(const RHIPixelShader*) = 0;
		virtual void				RHIBindVertexShader(const RHIVertexShader*) = 0;
		virtual void				RHIBindVertexBuffer(const RHIVertexBuffer*, u32, u32) = 0;
		virtual void				RHIBindIndexBuffer(const RHIIndexBuffer*) = 0;
		virtual void				RHIBindVertexLayout(const RHIVertexLayout*) = 0;
		virtual void				RHIDrawVertices(u32, u32) = 0;
		virtual void RHISetViewport(f32, f32, f32, f32, f32, f32) = 0;
		virtual void RHIResizeViewport(u32, u32, bool) = 0;
		virtual void RHIBegin() = 0;
		virtual void RHIEnd() = 0;
	};
	extern DynamicRHI* GDynamicRHI;
}
#endif // !DYNAMICRHI_H
