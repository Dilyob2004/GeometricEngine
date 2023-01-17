#ifndef VKFRAMEBUFFER_H
#define VKFRAMEBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/FrameBuffer.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanFrameBuffer : public FrameBuffer
	{
	public:
		static VulkanFrameBuffer* GetInstance() { return thisInstance; }
		VulkanFrameBuffer(const FrameBufferDesc& );
		~VulkanFrameBuffer();
		const VkFramebuffer& GetFrameBuffer() const { return  m_Framebuffers; }
		virtual u32 GetAttachmentCount() const override { return m_AttachmentCount; }

		virtual const FrameBufferDesc& GetSpecification() const override { return m_FrameBufferDesc; }
	private:
		static VulkanFrameBuffer* thisInstance;
		u32				m_AttachmentCount;
		VkFramebuffer	m_Framebuffers;
		Vector2u		m_Size;
		FrameBufferDesc	m_FrameBufferDesc;
	};
}
#endif // !VKFRAMEBUFFER_H
