#include <Engine/Render/Vulkan/VkTexture.h>

#include <Engine/Render/Vulkan/VkDevice.h>
#define	VKDI VulkanDevice::GetInstance()

namespace MeteorEngine
{
	VulkanTexture::VulkanTexture()
	{

	}
	VulkanTexture::~VulkanTexture()
	{

	}
	bool VulkanTexture::CreateImage(u32         width,
		u32								height,
		VkFormat              format,
		VkImageTiling         tiling,
		VkImageUsageFlags     usage,
		VkMemoryPropertyFlags properties,
		VkImage& image,
		VkDeviceMemory& imageMemory)
	{
		// We only have a single queue so we can request exclusive access
		VkImageCreateInfo imageCreateInfo = VkImageCreateInfo();
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
		imageCreateInfo.extent.width = width;
		imageCreateInfo.extent.height = height;
		imageCreateInfo.extent.depth = 1;
		imageCreateInfo.mipLevels = 1;
		imageCreateInfo.arrayLayers = 1;
		imageCreateInfo.format = format;
		imageCreateInfo.tiling = tiling;
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageCreateInfo.usage = usage;
		imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		// Create the image, this does not allocate any memory for it yet
		if (vkCreateImage(VKDI->GetLogicalDevice(), &imageCreateInfo, 0, &image) != VK_SUCCESS)
			return false;

		// Check what kind of memory we need to request from the GPU
		VkMemoryRequirements memoryRequirements = VkMemoryRequirements();
		vkGetImageMemoryRequirements(VKDI->GetLogicalDevice(), image, &memoryRequirements);

		// Check what GPU memory type is available for us to allocate out of
		VkPhysicalDeviceMemoryProperties memoryProperties = VkPhysicalDeviceMemoryProperties();
		vkGetPhysicalDeviceMemoryProperties(VKDI->GetPhysicalDevice(), &memoryProperties);

		u32 memoryType = 0;

		for (; memoryType < memoryProperties.memoryTypeCount; ++memoryType)
		{
			if ((memoryRequirements.memoryTypeBits & static_cast<unsigned int>(1 << memoryType)) &&
				((memoryProperties.memoryTypes[memoryType].propertyFlags & properties) == properties))
				break;
		}

		if (memoryType == memoryProperties.memoryTypeCount)
			return false;

		VkMemoryAllocateInfo memoryAllocateInfo = VkMemoryAllocateInfo();
		memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = memoryType;

		// Allocate the memory out of the GPU pool for the required memory type
		if (vkAllocateMemory(VKDI->GetLogicalDevice(), &memoryAllocateInfo, 0, &imageMemory) != VK_SUCCESS)
			return false;

		// Bind the allocated memory to our image object
		if (vkBindImageMemory(VKDI->GetLogicalDevice(), image, imageMemory, 0) != VK_SUCCESS)
			return false;

		return true;
	}



	bool VulkanTexture::CreateImageViews(VkImageViewCreateInfo imageViewCreateInfo, std::vector<VkImage> swapchainImages, std::vector<VkImageView>& swapchainImageViews)
	{
		for (u32 i = 0; i < swapchainImages.size(); ++i)
		{
			imageViewCreateInfo.image = swapchainImages[i];
			if (vkCreateImageView(VKDI->GetLogicalDevice(), &imageViewCreateInfo, 0, &swapchainImageViews[i]) != VK_SUCCESS)
				return false;
		}

		return true;
	}
}