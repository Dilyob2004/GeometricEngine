#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkCommandPool.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Texture.h>
#include <Engine/Math/Vector2.h>
#include <Engine/Render/SwapChain.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <vector>
namespace MeteorEngine
{
	struct VulkanBackBuffer
	{
		VkSemaphore				PresentSemaphore = NULL;
		VulkanCommandPool*		CommandPool = NULL;
		VulkanCommandBuffer*	CommandBuffer = NULL;
	};
	class METEOR_API VulkanSwapChain : public SwapChain
	{
	public:
		static VulkanSwapChain* GetInstance() { return m_ThisInstance; }
		VulkanSwapChain();
		VulkanSwapChain(VulkanContext*, const Vector2u&, bool);
		~VulkanSwapChain();

		bool Create(VulkanContext*, const Vector2u&, bool);
		bool Create( const Vector2u&, bool);

		void Resize(const Vector2u&) override;
		void CreateFrameData();
		VulkanBackBuffer& GetCurrentBackBuffer();
		CommandBuffer* GetCurrentCommandBuffer() override{ return GetCurrentBackBuffer().CommandBuffer; }

		Texture* GetCurrentImage() override{ return (Texture*)m_SwapChainBuffers[m_AcquireImageIndex]; };
		u32 GetCurrentImageIndex()  const override { return m_AcquireImageIndex; }
		Texture* GetImage(u32 index) override{ return (Texture*)m_SwapChainBuffers[index]; };
		u32 GetSwapChainBufferCount() const override { return m_SwapChainBufferCount; }
		VkFormat GetSwapChainFormat() const { return m_ColourFormat; }
		VkSwapchainKHR GetSwapChain() const { return m_SwapChain; }
		void Begin() override;
		void Present()override;
		void End()override;
		void QueueSubmit()override;
	private:

		void AcquireNextImage();
		void FindSwapChainFormat();

		static VulkanSwapChain*		m_ThisInstance;
		Vector2u					m_Size;
		VkSwapchainKHR				m_SwapChain;
		VkSwapchainKHR				m_OldSwapChain;
		VkFormat					m_ColourFormat;
		VkColorSpaceKHR				m_ColourSpace;

		std::vector<Texture*>		m_SwapChainBuffers;
		u32							m_AcquireImageIndex;
		u32							m_SwapChainBufferCount;
		u32							m_CurrentBuffer;
		VulkanBackBuffer			m_FramesBackBuffer[16];
		VulkanContext*				m_ContextWindow;

	};
}
#endif // !VKSWAPSHAIN_H
