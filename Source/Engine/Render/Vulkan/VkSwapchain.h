#ifndef VKSWAPSHAIN_H
#define VKSWAPCHAIN_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkCommandPool.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Core/Window.h>
#include <Engine/Math/Vector2.h>
#include <vector>
namespace MeteorEngine
{
	struct FrameData
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

		bool Create( void *, const Vector2u&, bool);
		bool Create( const Vector2u&, bool);

		void OnResize(const Vector2u&, void* handle = NULL);
		void CreateFrameData();
		VkFormat GetSwapChainFormat() const { return m_ColourFormat;  }
		VkSwapchainKHR GetSwapChain() const { return m_SwapChain;  }
		FrameData& GetCurrentFrameData();

		void Begin();
		void Present(VkSemaphore);
		void End();
		void QueueSubmit();
	private:

		void AcquireNextImage();
		void FindSwapChainFormat();

		static VulkanSwapChain* m_ThisInstance;

		Vector2u m_Size;
		VkSwapchainKHR				m_SwapChain;
		VkSwapchainKHR				m_OldSwapChain;
		VkSurfaceKHR				m_Surface;
		VkFormat					m_ColourFormat;
		VkColorSpaceKHR				m_ColourSpace;

		u32							m_AcquireImageIndex;
		u32							m_SwapChainBufferCount;
		u32							m_CurrentBuffer;
		FrameData					m_Frames[3];


	};
}
#endif // !VKSWAPSHAIN_H
