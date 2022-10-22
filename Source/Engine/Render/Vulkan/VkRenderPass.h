#ifndef VKRENDERPASS_H
#define VKRENDERPASS_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/RenderPass.h>
#include <Engine/Render/FrameBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanRenderPass : public RenderPass
	{
	public:
		VulkanRenderPass(const RenderPassDesc&);
		~VulkanRenderPass();

		bool Init(const RenderPassDesc&);
		const VkRenderPass& GetRenderPass() const { return m_RenderPass; }

		virtual void BeginRenderpass(CommandBuffer* commandBuffer, float* clearColour, FrameBuffer* frame, SubPassContents contents, const Vector2u&) const override;
		virtual void EndRenderpass(CommandBuffer* commandBuffer) override;
		virtual s32 GetAttachmentCount() const override { return m_ColorAttachmentCount; }
	private:
		VkRenderPass	m_RenderPass;
		VkClearValue*	m_ClearValue;
		u32				m_ColorAttachmentCount;
		bool			m_DepthOnly = false, m_ClearDepth = false, m_SwapChainTarget = false;
		u32				m_ClearCount;
	};
}
#endif // !VKRENDERPASS_H
