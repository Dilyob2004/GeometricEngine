#ifndef VKCONTEXT_H
#define VKCONTEXT_H
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkSwapChain.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkCommandPool.h>
#include <Engine/Render/Vulkan/VkFence.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanContext
	{
	public:
		VulkanContext();
		~VulkanContext();
		static VulkanContext* GetInstance() { return thisInstance; }
		void Create(Window*);

		VkInstance GetVulkanInstance() const { return m_Instance;  }

		void Present();
	private:
		bool CreateInstance(bool);
	private:

		static VulkanContext* thisInstance;

		unsigned int       currentFrame = 0;
		bool               swapchainOutOfDate = false;
		VulkanFrameBuffer*		m_VulkanFrameBuffer;
		VulkanDevice*			m_VulkanDevice;
		VulkanSwapChain*		m_VulkanSwapChain;
		VkInstance						m_Instance;
	};
}
#endif // !VKCONTEXT_Hâ
