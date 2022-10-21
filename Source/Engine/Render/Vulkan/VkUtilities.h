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

	VkFormat FindSupportedFormat(VkPhysicalDevice gpu, const std::vector<VkFormat>& candidates, VkImageTiling tiling,
		VkFormatFeatureFlags features);

	VkFormat FindDepthFormat(VkPhysicalDevice device);


	VkSamplerAddressMode TextureWrapToVK(const TextureWrap wrap);

	VkFilter TextureFilterToVK(const TextureFilter filter);


	RHIPixelFormat VKToFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_R8_SRGB:
			return RHIPixelFormat::R8_UNORM;
		case VK_FORMAT_R8G8_SRGB:
			return RHIPixelFormat::RG8_UNORM;
		case VK_FORMAT_R8G8B8_SRGB:
			return RHIPixelFormat::RGB8_UNORM;
		case VK_FORMAT_R8G8B8A8_SRGB:
			return RHIPixelFormat::RGBA8_UNORM;
		case VK_FORMAT_R16G16B16_SFLOAT:
			return RHIPixelFormat::RGB16_F32;
		case VK_FORMAT_R16G16B16A16_SFLOAT:
			return RHIPixelFormat::RGBA16_F32;
		case VK_FORMAT_R32G32B32_SFLOAT:
			return RHIPixelFormat::RGB32_F32;
		case VK_FORMAT_R32G32B32A32_SFLOAT:
			return RHIPixelFormat::RGBA32_F32;
		case VK_FORMAT_R8_UNORM:
			return RHIPixelFormat::R8_UNORM;
		case VK_FORMAT_R8G8_UNORM:
			return RHIPixelFormat::RG8_UNORM;
		case VK_FORMAT_R8G8B8A8_UNORM:
			return RHIPixelFormat::RGBA8_UNORM;
		case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
			return RHIPixelFormat::RG11B10_F32;
		case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
			return RHIPixelFormat::RGB10A2_UNORM;
		case VK_FORMAT_D16_UNORM:
			return RHIPixelFormat::DEPTH16_UNORM;
		case VK_FORMAT_D32_SFLOAT:
			return RHIPixelFormat::DEPTH32_F32;
		case VK_FORMAT_D24_UNORM_S8_UINT:
			return RHIPixelFormat::DEPTH24_UNORM_STENCIL8_U32;
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
			return RHIPixelFormat::DEPTH32_F32_STENCIL8_U32;
		default:
			LOG("[Texture] Unsupported texture type!");
			return RHIPixelFormat::RGBA8_UNORM;
		}
	}
}
#endif // !VKUTILITIES_H
