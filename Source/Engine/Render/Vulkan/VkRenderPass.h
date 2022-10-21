#ifndef VKRENDERPASS_H
#define VKRENDERPASS_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/RenderPass.h>
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{
	enum SubPassContents
	{
		INLINE,
		SECONDARY
	};
	class METEOR_API VulkanRenderPass : public RenderPass
	{
	public:
		VulkanRenderPass(const RenderPassDesc&);
		~VulkanRenderPass();

		bool Init(const RenderPassDesc&);


		//virtual void BeginRenderpass(CommandBuffer* commandBuffer, float* clearColour, Framebuffer* frame, SubPassContents contents, const Vector2u&) const = 0;
		virtual void EndRenderpass(CommandBuffer* commandBuffer) = 0;
		virtual int GetAttachmentCount() const = 0;
	private:
		VkRenderPass	m_RenderPass;
		VkClearValue*	m_ClearValue;
		u32				m_ColorAttachmentCount;
	};
}
#endif // !VKRENDERPASS_H
