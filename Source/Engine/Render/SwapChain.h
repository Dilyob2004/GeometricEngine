#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H
#include <Engine/Render/Texture.h>
#include <Engine/Render/CommandBuffer.h>
#include <Engine/Render/RenderContext.h>
namespace MeteorEngine
{
	class METEOR_API SwapChain
	{
	public:
		virtual ~SwapChain(){}
		static SwapChain* Create(RenderContext*, const Vector2u&, bool);
		virtual CommandBuffer* GetCurrentCommandBuffer() = 0;

		virtual Texture* GetCurrentImage() = 0;
		virtual u32 GetCurrentImageIndex() const = 0;
		virtual Texture* GetImage(u32 index) = 0;
		virtual u32 GetSwapChainBufferCount()const = 0;


		virtual void Resize(const Vector2u&) = 0;
		virtual void Begin() = 0;
		virtual void Present() = 0;
		virtual void End() = 0;
		virtual void QueueSubmit() = 0;
	};
}
#endif // !SWAPCHAIN_H
