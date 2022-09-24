#ifndef VKCONTEXT_H
#define VKCONTEXT_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkSwapChain.h>
#include <Engine/Core/Singleton.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanContext : public Singleton<VulkanContext>
	{
	public:
		VulkanContext();
		~VulkanContext();

		void Create(Window*);

		VkInstance GetVkInstance() const { return m_Instance;  }

	private:
		bool CreateInstance(bool);
		bool CreateSemaphores();
		bool CreateFences();
		bool CreateCommandPool();
		bool AllocateCommandBuffer();

	private:
		VulkanDevice*	m_VulkanDevice;
		VulkanSwapChain* m_VulkanSwapChain;

		VkInstance						m_Instance;
		VkCommandPool					m_CommandPool;

		const u32						m_MaxFramesInFlight;
		std::vector<VkFence>			m_Fences;
		std::vector<VkSemaphore>		m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>		m_RenderFinishedSemaphores;
		std::vector<VkCommandBuffer>	m_CommandBuffers;
	};
}
#endif // !VKCONTEXT_Hâ
