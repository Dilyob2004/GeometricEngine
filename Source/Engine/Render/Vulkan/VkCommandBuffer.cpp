#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkUtilities.h>


namespace MeteorEngine
{

	VulkanCommandBuffer::VulkanCommandBuffer() :
		m_State(CommandBufferState::ReadyForBegin),
		m_Semaphore(0),
		m_VulkanFence(0),
		m_CommandBuffer(0),
		m_CommandPool(0)
	{

	}
	VulkanCommandBuffer::~VulkanCommandBuffer()
	{

		if(m_Semaphore)
			vkDestroySemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Semaphore, 0);

		if(m_CommandBuffer)
			vkFreeCommandBuffers(VulkanDevice::GetInstance()->GetLogicalDevice(), m_CommandPool, 1, &m_CommandBuffer);
	}
	void VulkanCommandBuffer::Begin()
	{
		m_State = CommandBufferState::IsInsideBegin;
		VkCommandBufferBeginInfo beginCreateInfo = VkCommandBufferBeginInfo();
		beginCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginCreateInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		if (vkBeginCommandBuffer(m_CommandBuffer, &beginCreateInfo) != VK_SUCCESS)
			return;
	}
	void VulkanCommandBuffer::End()
	{

		vkEndCommandBuffer(m_CommandBuffer);
		m_State = CommandBufferState::HasEnded;
	}
	void VulkanCommandBuffer::Submit()
	{
		Submit(NULL);
	}
	void VulkanCommandBuffer::Submit(VkSemaphore waitSemaphore)
	{
		VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		// Signal the render finished semaphore once the queue has been processed
		VkSubmitInfo submitInfo				= VkSubmitInfo();
		submitInfo.sType					= VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount		= 1;
		submitInfo.pWaitSemaphores			= &waitSemaphore;
		submitInfo.pWaitDstStageMask		= &waitStages;
		submitInfo.commandBufferCount		= 1;
		submitInfo.pCommandBuffers			= &m_CommandBuffer;
		submitInfo.signalSemaphoreCount		= 1;
		submitInfo.pSignalSemaphores		= &m_Semaphore;

		m_VulkanFence->Reset();
		if (vkQueueSubmit(VulkanDevice::GetInstance()->GetQueue(), 1, &submitInfo, m_VulkanFence->GetFence()) != VK_SUCCESS)
			return;
	}
	bool VulkanCommandBuffer::Init(bool primary)
	{
		m_CommandPool = VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool();
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = VkCommandBufferAllocateInfo();
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = m_CommandPool;
		commandBufferAllocateInfo.level = primary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		commandBufferAllocateInfo.commandBufferCount = 1;
		(vkAllocateCommandBuffers(VulkanDevice::GetInstance()->GetLogicalDevice(), &commandBufferAllocateInfo, &m_CommandBuffer));

		VkSemaphoreCreateInfo semaphoreInfo = VkSemaphoreCreateInfo();
		semaphoreInfo.pNext = nullptr;

		(vkCreateSemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), &semaphoreInfo, nullptr, &m_Semaphore));

		m_VulkanFence = new VulkanFence();
		if (!m_VulkanFence->Create(VulkanDevice::GetInstance()->GetLogicalDevice()))
			return false;

		return true;
	}

	bool VulkanCommandBuffer::Init( bool primary, VkCommandPool commandPool)
	{
		m_CommandPool = commandPool;
		VkCommandBufferAllocateInfo commandBufferAllocateInfo	= VkCommandBufferAllocateInfo();
		commandBufferAllocateInfo.sType							= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool					= commandPool;
		commandBufferAllocateInfo.level							= primary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		commandBufferAllocateInfo.commandBufferCount			= 1;

		if (vkAllocateCommandBuffers(VulkanDevice::GetInstance()->GetLogicalDevice(), &commandBufferAllocateInfo, &m_CommandBuffer) != VK_SUCCESS)
			return false;

		VkSemaphoreCreateInfo semaphoreCreateInfo = VkSemaphoreCreateInfo();
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), &semaphoreCreateInfo, 0, &m_Semaphore) != VK_SUCCESS)
			return false;
		m_VulkanFence = new VulkanFence();
		if (!m_VulkanFence->Create(VulkanDevice::GetInstance()->GetLogicalDevice()))
			return false;


		return true;

	}

	void VulkanCommandBuffer::UpdateViewport(const Vector2u& size, bool flipViewport)
	{

		VkViewport viewport		= VkViewport();
		viewport.x				= 0.0f;
		viewport.y				= 0.0f;
		viewport.width			= static_cast<f32>(size.x);
		viewport.height			= static_cast<f32>(size.y);
		viewport.minDepth		= 0.0f;
		viewport.maxDepth		= 1.0f;

		if (flipViewport)
		{
			viewport.x		= 0;
			viewport.y		= static_cast<f32>(size.y);
			viewport.width	= static_cast<f32>(size.x);
			viewport.height	= -static_cast<f32>(size.y);
		}

		VkRect2D scissor	= VkRect2D();
		scissor.offset		= { 0, 0 };
		scissor.extent		= { size.x, size.y };

		vkCmdSetViewport(m_CommandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(m_CommandBuffer, 0, 1, &scissor);
	}
	bool VulkanCommandBuffer::Wait()
	{

		m_VulkanFence->Wait();
		m_VulkanFence->Reset();
		m_State = CommandBufferState::ReadyForBegin;

		return true;
	}
	void VulkanCommandBuffer::Reset()
	{
		vkResetCommandBuffer(m_CommandBuffer, 0);
	}
	bool VulkanCommandBuffer::Flush()
	{

		if (m_State == CommandBufferState::ReadyForBegin)
			return true;

		VulkanDevice::GetInstance()->WaitIdle();

		if (m_State == CommandBufferState::Submitted)
			return Wait();

		return true;
	}
}