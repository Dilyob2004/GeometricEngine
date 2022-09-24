#ifndef VULKANFRAMEBUFFER_H
#define VULKANFRAMEBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Render/Vulkan/Vk.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanFrameBuffer
	{
	public:
		VulkanFrameBuffer();
		~VulkanFrameBuffer();
		bool CreateFrameBuffer();
	private:


		std::vector<VkFramebuffer>      m_SwapchainFramebuffers;

	};
}
#endif // !VULKANFRAMEBUFFER_H
