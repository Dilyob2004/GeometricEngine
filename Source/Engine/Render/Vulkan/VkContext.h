#ifndef VKCONTEXT_H
#define VKCONTEXT_H
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Core/Window.h>
#include <Engine/Render/RenderContext.h>
namespace MeteorEngine
{
	class METEOR_API VulkanContext : public RenderContext
	{
	public:
		VulkanContext();
		VulkanContext(Window*);
		~VulkanContext();
		static VulkanContext* GetInstance() { return m_ThisInstance; }
		void Create(Window*);
		VkInstance GetVulkanInstance() const { return m_Instance;  }
		VkSurfaceKHR GetSurface() const { return m_Surface; }
	private:
		bool CreateInstance(bool);

		static VulkanContext*	m_ThisInstance;
		VulkanDevice*			m_VulkanDevice;
		VkInstance				m_Instance;
		VkSurfaceKHR			m_Surface;
	};
}
#endif // !VKCONTEXT_Hâ
