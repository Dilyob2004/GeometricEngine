#ifndef VKSURFACE_H
#define VKSURFACE_H
#include <Engine/Render/Vulkan/Vk.h>

namespace MeteorEngine
{
	class METEOR_API VulkanSurface
	{
	public:
		VulkanSurface();
		~VulkanSurface();

		bool Create(VkInstance, HWND);
		VkSurfaceKHR GetSurface() const { return m_Surface; }
	private:
		VkSurfaceKHR	m_Surface;
		VkInstance		m_Instance;

	};
}
#endif // !VKSURFACE_H
