#ifndef VKCOMMANDBUFFER_H
#define VKCOMMANDBUFFER_H


#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkFence.h>
#include <Engine/Render/CommandBuffer.h>
#include <Engine/Math/Vector2.h>

namespace MeteorEngine
{


	class METEOR_API VulkanCommandBuffer : public CommandBuffer
	{
	public:
		VulkanCommandBuffer();
		~VulkanCommandBuffer();

		virtual CommandBufferState	GetState() const override{ return m_State; }
		virtual bool Init(bool, VkCommandPool);
		virtual bool Init(bool) override;
		virtual void Begin() override;
		virtual void Submit(VkSemaphore);
		virtual void Submit() override;
		virtual void End() override;
		virtual void UpdateViewport(const Vector2u&, bool) override;
		virtual bool Wait() ;
		virtual void Reset();
		virtual bool Flush() override;
		VkCommandBuffer		GetCommandBuffer() const { return m_CommandBuffer; }
		VkSemaphore			GetSemaphore() const { return m_Semaphore; }
	private:
		CommandBufferState	m_State;
		VkCommandBuffer		m_CommandBuffer;
		VkSemaphore			m_Semaphore;
		VkCommandPool		m_CommandPool;
		VulkanFence*		m_VulkanFence;

	};
}
#endif // !VKCOMMANDBUFFER_H
