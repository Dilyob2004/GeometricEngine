#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/Singleton.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanSwapChain : public Singleton<VulkanSwapChain>
	{
	public:
		static VulkanSwapChain* GetInstance() { return thisInstance; }
		VulkanSwapChain();
		~VulkanSwapChain();

		bool CreateSwapChain(u32, u32);
		VkFormat GetSwapChainFormat() const { return m_SwapchainFormat.format;  }
		VkSwapchainKHR GetSwapChain() const { return m_SwapChain;  }
		std::vector<VkImageView> GetSwapChainImageViews() const { return m_SwapchainImageViews;  }
	private:
		static VulkanSwapChain* thisInstance;

		VkSwapchainKHR				m_SwapChain;
		VkSurfaceFormatKHR			m_SwapchainFormat;

		std::vector<VkImage>		m_SwapchainImages;
		std::vector<VkImageView>	m_SwapchainImageViews;

	};
}
#endif // !VKSWAPSHAIN_H
