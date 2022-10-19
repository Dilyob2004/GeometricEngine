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

	VkImageView CreateImageViews(VkDevice device, VkImage image, VkFormat format, u32 mipLevels, VkImageViewType viewType, VkImageAspectFlags aspectMask, u32 layerCount, u32 baseArrayLayer = 0, u32 baseMipLevel = 0);
	VkSampler CreateTextureSampler(VkDevice device, VkFilter magFilter = VK_FILTER_LINEAR, VkFilter minFilter = VK_FILTER_LINEAR, float minLod = 0.0f, float maxLod = 1.0f, bool anisotropyEnable = false, float maxAnisotropy = 1.0f, VkSamplerAddressMode modeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VkSamplerAddressMode modeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VkSamplerAddressMode modeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE);



	VkSamplerAddressMode TextureWrapToVK(const TextureWrap wrap);

	VkFilter TextureFilterToVK(const TextureFilter filter);
}
#endif // !VKUTILITIES_H
