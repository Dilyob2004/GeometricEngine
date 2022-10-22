#ifndef VKUTILITIES_H
#define VKUTILITIES_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkTexture.h>

namespace MeteorEngine
{
	u32 FindMemoryType(VkPhysicalDevice device, u32 typeFilter, VkMemoryPropertyFlags properties);
	VkPipelineStageFlags AccessFlagsToPipelineStage(VkAccessFlags accessFlags, const VkPipelineStageFlags stageFlags);
	VkPipelineStageFlags LayoutToAccessMask(const VkImageLayout layout, const bool isDestination);
	bool IsDepthFormat(VkFormat format);
	bool IsStencilFormat(VkFormat format);
	VkFormat RHIPixelFormatToVK(RHIPixelFormat format, bool srgb);
	VkCommandBuffer BeginSingleTimeCommands(VkDevice, VkCommandPool);
	void EndSingleTimeCommands(VkDevice, VkQueue, VkCommandPool, VkCommandBuffer);
	void TransitionImageLayout(VkDevice, VkQueue, VkCommandPool, VkImage image, VkFormat format, VkImageLayout oldImageLayout, VkImageLayout newImageLayout,
		u32 mipLevels, u32 layerCount, VkCommandBuffer commandBuffer);

	void CreateImage(VkDevice device, VkPhysicalDevice physicalDevice, u32 width, u32 height, u32 mipLevels, 
		VkFormat format, VkImageType imageType, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, 
		VkImage& image, VkDeviceMemory& imageMemory, u32 arrayLayers, VkImageCreateFlags flags);

	VkFormat FindSupportedFormat(VkPhysicalDevice gpu, const std::vector<VkFormat>& candidates, VkImageTiling tiling,
		VkFormatFeatureFlags features);

	VkFormat FindDepthFormat(VkPhysicalDevice device);


	RHIPixelFormat VKToFormat(VkFormat format);
}
#endif // !VKUTILITIES_H
