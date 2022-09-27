#ifndef VULKANTEXTURE_H
#define VULKANTEXTURE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Core/Config.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanTexture
	{
	public:
		VulkanTexture();
		~VulkanTexture();
		static bool CreateImage(u32, u32, VkFormat, VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags, VkImage&, VkDeviceMemory&);
		static bool CreateImageViews(VkImageViewCreateInfo, std::vector<VkImage>, std::vector<VkImageView>&);
	};
}
#endif // !VULKANTEXTURE_H
