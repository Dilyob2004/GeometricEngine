#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <vector>

struct SwapChainBuffer
{
	VkImage image;
	VkImageView view;
};
namespace MeteorEngine
{
	class METEOR_API VulkanSwapChain
	{
	public:


		void InitSurface(void*);
		void Connect(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);
		void Create(u32* width, u32* height, bool vsync = false, bool fullscreen = false);
		VkResult AcquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex);
		VkResult QueuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
		void Cleanup();
	private:

		VkInstance						m_Instance;
		VkDevice						m_Device;
		VkPhysicalDevice				m_PhysicalDevice;
		VkSurfaceKHR					m_Surface;
		VkFormat						m_ColorFormat;
		VkColorSpaceKHR					m_ColorSpace;
		VkSwapchainKHR					m_SwapChain = VK_NULL_HANDLE;
		uint32_t						m_ImageCount;
		std::vector<VkImage>			m_Images;
		std::vector<SwapChainBuffer>	m_Buffers;
		uint32_t						m_QueueNodeIndex = UINT32_MAX;
	};
}
#endif // !VKSWAPSHAIN_H
