#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkCommandPool.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Texture.h>
#include <Engine/Math/Vector2.h>
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
	class METEOR_API VulkanSwapChain
	{
	public:
		static VulkanSwapChain* GetInstance() { return m_ThisInstance; }
		VulkanSwapChain();
		~VulkanSwapChain();

		bool Create(VulkanContext*, const Vector2u&, bool);
		bool Create( const Vector2u&, bool);

		void Resize(const Vector2u&);
		void CreateFrameData();
		VulkanBackBuffer& GetCurrentBackBuffer();
		CommandBuffer* GetCurrentCommandBuffer() { return GetCurrentBackBuffer().CommandBuffer; }

		Texture* GetCurrentImage() { return (Texture*)m_SwapChainBuffers[m_AcquireImageIndex]; };
		u32 GetCurrentImageIndex() const { return m_AcquireImageIndex; }
		Texture* GetImage(u32 index) { return (Texture*)m_SwapChainBuffers[index]; };
		VkFormat GetSwapChainFormat() const { return m_ColourFormat; }
		VkSwapchainKHR GetSwapChain() const { return m_SwapChain; }
		u32 GetSwapChainBufferCount() const { return m_SwapChainBufferCount; }
		void Begin();
		void Present();
		void End();
		void QueueSubmit();
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
