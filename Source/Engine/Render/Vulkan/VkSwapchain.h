#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Core/Window.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanSwapChain
	{
	public:
		VulkanSwapChain();
		~VulkanSwapChain();

		bool CreateSwapChain(u32, u32);

	private:

		VkSwapchainKHR				m_SwapChain;
		VkSurfaceFormatKHR			m_SwapchainFormat;

		std::vector<VkImage>		m_SwapchainImages;
		std::vector<VkImageView>	m_SwapchainImageViews;

	};
}
#endif // !VKSWAPSHAIN_H
