#include <Engine/Render/Vulkan/VkSurface.h>


namespace MeteorEngine
{

	VulkanSurface::VulkanSurface():
		m_Surface(0),
		m_Instance(0)
	{
	}
	VulkanSurface::~VulkanSurface()
	{
		if (m_Surface)
			vkDestroySurfaceKHR(m_Instance, m_Surface, 0);
	}

	bool VulkanSurface::Create(VkInstance vinstance, HWND hwnd)
	{
		m_Instance = vinstance;
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
		surfaceCreateInfo.hwnd = hwnd;
		if (vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, nullptr, &m_Surface) != VK_SUCCESS)
			return false;

		return true;
	}
}