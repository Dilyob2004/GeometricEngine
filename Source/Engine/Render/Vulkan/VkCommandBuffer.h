#ifndef VKCOMMANDBUFFER_H
#define VKCOMMANDBUFFER_H


#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkFence.h>
#include <Engine/Math/Vector2.h>

namespace MeteorEngine
{
	enum class CommandBufferState
	{
		ReadyForBegin,
		IsInsideBegin,
		IsInsideRenderPass,
		HasEnded,
		Submitted
	};

	class METEOR_API VulkanCommandBuffer
	{
	public:
		VulkanCommandBuffer();
		~VulkanCommandBuffer();

		CommandBufferState	GetState() const { return m_State; }
		bool Create(VkDevice, bool, VkCommandPool);
		void Begin();
		void Submit(VkQueue, VkSemaphore);
		void End();
		void UpdateViewport(const Vector2u&, bool);
		bool Wait();
		void Reset();
		bool Flush();
		VkCommandBuffer		GetCommandBuffer() const { return m_CommandBuffer; }
		VkSemaphore			GetSemaphore() const { return m_Semaphore; }
	private:
		CommandBufferState	m_State;
		VkDevice			m_Device;
		VkCommandBuffer		m_CommandBuffer;
		VkSemaphore			m_Semaphore;
		VkCommandPool		m_CommandPool;
		VulkanFence*		m_VulkanFence;

	};
}
#endif // !VKCOMMANDBUFFER_H
