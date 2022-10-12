#ifndef  VKFENCE_H
#define VKFENCE_H

#include <Engine/Render/Vulkan/Vk.h>

namespace MeteorEngine
{
	class METEOR_API VulkanFence
	{
	public:
		VulkanFence();
		~VulkanFence();
		bool Create(VkDevice);
		void Wait();
		void Reset();
		VkFence GetFence() const { return m_Fence; }
	private:
		VkDevice m_Device;
		VkFence m_Fence;
	};
}
#endif // ! VKFENCE_H
