#ifndef VKFRAMEBUFFER_H
#define VKFRAMEBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Math/Vector2.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanFrameBuffer
	{
	public:
		static VulkanFrameBuffer* GetInstance() { return thisInstance; }
		VulkanFrameBuffer();
		~VulkanFrameBuffer();
		bool Create(VkDevice, VkRenderPass, std::vector<VkImageView>, const Vector2u&);
		VkFramebuffer GetFrameBuffer() const { return  m_SwapchainFramebuffers; }
		u32 GetAttachmentCount() const { return m_AttachmentCount; }
	private:
		static VulkanFrameBuffer* thisInstance;
		u32				m_AttachmentCount;
		VkDevice		m_Device;
		VkFramebuffer	m_SwapchainFramebuffers;

	};
}
#endif // !VKFRAMEBUFFER_H
