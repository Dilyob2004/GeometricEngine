#ifndef VKFRAMEBUFFER_H
#define VKFRAMEBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Render/Vulkan/Vk.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanFrameBuffer
	{
	public:
		static VulkanFrameBuffer* GetInstance() { return thisInstance; }
		VulkanFrameBuffer();
		~VulkanFrameBuffer();
		bool CreateFrameBuffer(u32, u32);
		std::vector<VkFramebuffer> GetFrameBuffer() const { return  m_SwapchainFramebuffers; }
	private:
		static VulkanFrameBuffer* thisInstance;


		std::vector<VkFramebuffer>      m_SwapchainFramebuffers;

	};
}
#endif // !VKFRAMEBUFFER_H
