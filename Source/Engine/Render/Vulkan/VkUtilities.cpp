#include <Engine/Render/Vulkan/VkUtilities.h>
namespace MeteorEngine
{
	VkCullModeFlags CullModeToVK(CullMode mode)
	{
		switch (mode)
		{
		case CullMode::BACK:
			return VK_CULL_MODE_BACK_BIT;
		case CullMode::FRONT:
			return VK_CULL_MODE_FRONT_BIT;
		case CullMode::FRONTANDBACK:
			return VK_CULL_MODE_FRONT_AND_BACK;
		case CullMode::NONE:
			return VK_CULL_MODE_NONE;
		}

		return VK_CULL_MODE_BACK_BIT;
	}
	VkPolygonMode PolygonModeToVk(PolygonMode mode)
	{
		switch (mode)
		{
		case PolygonMode::FILL:
			return VK_POLYGON_MODE_FILL;
			break;
		case PolygonMode::LINE:
			return VK_POLYGON_MODE_LINE;
			break;
		case PolygonMode::POINT:
			return VK_POLYGON_MODE_POINT;
			break;
		default:
			LOGLN("Unknown Polygon Mode");
			return VK_POLYGON_MODE_FILL;
			break;
		}
	}

	VkPrimitiveTopology DrawTypeToVk(DrawType type)
	{
		switch (type)
		{
		case DrawType::TRIANGLE:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
		case DrawType::LINES:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			break;
		case DrawType::POINT:
			return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			break;
		default:
			LOGLN("Unknown Draw Type");
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
		}
	}
	VkDescriptorType DescriptorTypeToVK(DescriptorType type)
	{
		switch (type)
		{
		case DescriptorType::UNIFORM_BUFFER:
			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		case DescriptorType::UNIFORM_BUFFER_DYNAMIC:
			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
		case DescriptorType::IMAGE_SAMPLER:
			return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		case DescriptorType::IMAGE_STORAGE:
			return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		}

		LOGLN("Unsupported Descriptor Type");
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}
	VkShaderStageFlagBits ShaderTypeToVK(const ShaderType& shaderName)
	{
		switch (shaderName)
		{
		case ShaderType::VERTEX: return VK_SHADER_STAGE_VERTEX_BIT;
		case ShaderType::FRAGMENT: return VK_SHADER_STAGE_FRAGMENT_BIT;
		default:
			LOG("Unknown Shader Type");
			return VK_SHADER_STAGE_VERTEX_BIT;
		}
	}
	void CopyBufferToImage(VkDevice device, VkQueue queue, VkCommandPool commandPool, VkBuffer buffer, VkImage image, u32 width, u32 height)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands(device, commandPool);

		VkBufferImageCopy region;
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;
		region.imageOffset = { 0, 0, 0 };
		region.imageExtent = {
								width,
								height,
								1
		};

		vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

		EndSingleTimeCommands(device, queue, commandPool, commandBuffer);
	}
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
	u32 FindMemoryType(VkPhysicalDevice device, u32 typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

		for (u32 i = 0; i < memProperties.memoryTypeCount; i++)
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;

		return 0;
	}
	VkFormat FindSupportedFormat(VkPhysicalDevice gpu, const std::vector<VkFormat>& candidates, VkImageTiling tiling,
		VkFormatFeatureFlags features)
	{
		for (VkFormat format : candidates)
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(gpu, format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
				return format;
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
				return format;
		}

		LOG("Failed to find supported format!");
		return VK_FORMAT_UNDEFINED;
	}

	VkFormat FindDepthFormat(VkPhysicalDevice device)
	{
		return FindSupportedFormat(device,
			{ VK_FORMAT_D32_SFLOAT_S8_UINT,
			  VK_FORMAT_D32_SFLOAT,
			  VK_FORMAT_D24_UNORM_S8_UINT,
			  VK_FORMAT_D16_UNORM_S8_UINT,
			  VK_FORMAT_D16_UNORM },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}
	void CreateImageDefault(VkDevice device, VkPhysicalDevice physicalDevice, const VkImageCreateInfo& imageInfo, VkImage& image, VkDeviceMemory& imageMemory, VkMemoryPropertyFlags properties)
	{
		vkCreateImage(device, &imageInfo, nullptr, &image);

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device, image, &memRequirements);

		VkMemoryAllocateInfo allocInfo = VkMemoryAllocateInfo();
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

		vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory);
		vkBindImageMemory(device, image, imageMemory, 0);
	}
	void CreateImage(VkDevice device, VkPhysicalDevice physicalDevice, u32 width, u32 height, u32 mipLevels,
		VkFormat format, VkImageType imageType, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, 
		VkImage& image, VkDeviceMemory& imageMemory, u32 arrayLayers, VkImageCreateFlags flags)
	{
		VkImageCreateInfo imageInfo = VkImageCreateInfo();
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = imageType;
		imageInfo.extent = { width, height, 1 };
		imageInfo.mipLevels = mipLevels;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageInfo.arrayLayers = arrayLayers;
		imageInfo.flags = flags;

		CreateImageDefault(device, physicalDevice, imageInfo, image, imageMemory, properties);
	}

	VkPipelineStageFlags AccessFlagsToPipelineStage(VkAccessFlags accessFlags, const VkPipelineStageFlags stageFlags)
	{
		VkPipelineStageFlags stages = 0;

		while (accessFlags != 0)
		{
			VkAccessFlagBits AccessFlag = static_cast<VkAccessFlagBits>(accessFlags & (~(accessFlags - 1)));
			//ASSERT(AccessFlag != 0 && (AccessFlag & (AccessFlag - 1)) == 0, "Error");
			accessFlags &= ~AccessFlag;

			switch (AccessFlag)
			{
			case VK_ACCESS_INDIRECT_COMMAND_READ_BIT:
				stages |= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
				break;

			case VK_ACCESS_INDEX_READ_BIT:
				stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
				break;

			case VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT:
				stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
				break;

			case VK_ACCESS_UNIFORM_READ_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_INPUT_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				break;

			case VK_ACCESS_SHADER_READ_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_SHADER_WRITE_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_COLOR_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				break;

			case VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				break;

			case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
				break;

			case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
				break;

			case VK_ACCESS_TRANSFER_READ_BIT:
				stages |= VK_PIPELINE_STAGE_TRANSFER_BIT;
				break;

			case VK_ACCESS_TRANSFER_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_TRANSFER_BIT;
				break;

			case VK_ACCESS_HOST_READ_BIT:
				stages |= VK_PIPELINE_STAGE_HOST_BIT;
				break;

			case VK_ACCESS_HOST_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_HOST_BIT;
				break;

			case VK_ACCESS_MEMORY_READ_BIT:
				break;

			case VK_ACCESS_MEMORY_WRITE_BIT:
				break;

			default:
				LOG("Unknown access flag");
				break;
			}
		}
		return stages;
	}
	VkPipelineStageFlags LayoutToAccessMask(const VkImageLayout layout, const bool isDestination)
	{
		VkPipelineStageFlags accessMask = 0;

		switch (layout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			if (isDestination)
			{
				LOG("The new layout used in a transition must not be VK_IMAGE_LAYOUT_UNDEFINED.");
			}
			break;

		case VK_IMAGE_LAYOUT_GENERAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT; // VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			accessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			accessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			if (!isDestination)
			{
				accessMask = VK_ACCESS_HOST_WRITE_BIT;
			}
			else
			{
				LOG("The new layout used in a transition must not be VK_IMAGE_LAYOUT_PREINITIALIZED.");
			}
			break;

		case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			accessMask = VK_ACCESS_MEMORY_READ_BIT;
			break;

		default:
			LOG("Unexpected image layout");
			break;
		}

		return accessMask;
	}

	bool IsDepthFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_D16_UNORM:
		case VK_FORMAT_D32_SFLOAT:
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
		case VK_FORMAT_D24_UNORM_S8_UINT:
		case VK_FORMAT_D16_UNORM_S8_UINT:
			return true;
		}
		return false;
	}

	bool IsStencilFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
		case VK_FORMAT_D24_UNORM_S8_UINT:
			return true;
		}
		return false;
	}
	VkFormat RHIPixelFormatToVK(const RHIPixelFormat format, bool srgb)
	{
		if (srgb)
		{
			switch (format)
			{
				case RHIPixelFormat::R8_UNORM:
					return VK_FORMAT_R8_SRGB;
				case RHIPixelFormat::RG8_UNORM:
					return VK_FORMAT_R8G8_SRGB;
				case RHIPixelFormat::RGB8_UNORM:
					return VK_FORMAT_R8G8B8_SRGB;
				case RHIPixelFormat::RGBA8_UNORM:
					return VK_FORMAT_R8G8B8A8_SRGB;


				case RHIPixelFormat::RGB16_F32:
					return VK_FORMAT_R16G16B16_SFLOAT;
				case RHIPixelFormat::RGBA16_F32:
					return VK_FORMAT_R16G16B16A16_SFLOAT;


				case RHIPixelFormat::RGB32_F32:
					return VK_FORMAT_R32G32B32_SFLOAT;

				case RHIPixelFormat::RGBA32_F32:
					return VK_FORMAT_R32G32B32A32_SFLOAT;


				default:
					LOG("[Texture] Unsupported image bit-depth!");
					return VK_FORMAT_R8G8B8A8_SRGB;
			}
		}
		else
		{
			switch (format)
			{

				case RHIPixelFormat::R8_UNORM:
					return VK_FORMAT_R8_UNORM;

				case RHIPixelFormat::RG8_UNORM:
					return VK_FORMAT_R8G8_UNORM;

				case RHIPixelFormat::RGB8_UNORM:
					return VK_FORMAT_R8G8B8A8_UNORM;

				case RHIPixelFormat::RGBA8_UNORM:
					return VK_FORMAT_R8G8B8A8_UNORM;



				case RHIPixelFormat::RG11B10_F32:
					return VK_FORMAT_B10G11R11_UFLOAT_PACK32;

				case RHIPixelFormat::RGB10A2_UNORM:
					return VK_FORMAT_A2R10G10B10_UNORM_PACK32;



				case RHIPixelFormat::R16_F32:
					return VK_FORMAT_R16_SFLOAT;

				case RHIPixelFormat::RG16_F32:
					return VK_FORMAT_R16G16_SFLOAT;

				case RHIPixelFormat::RGB16_F32:
					return VK_FORMAT_R16G16B16_SFLOAT;

				case RHIPixelFormat::RGBA16_F32:
					return VK_FORMAT_R16G16B16A16_SFLOAT;




				case RHIPixelFormat::R32_F32:
					return VK_FORMAT_R32_SFLOAT;

				case RHIPixelFormat::RG32_F32:
					return VK_FORMAT_R32G32_SFLOAT;

				case RHIPixelFormat::RGB32_F32:
					return VK_FORMAT_R32G32B32_SFLOAT;

				case RHIPixelFormat::RGBA32_F32:
					return VK_FORMAT_R32G32B32A32_SFLOAT;




				case RHIPixelFormat::DEPTH16_UNORM:
					return VK_FORMAT_D16_UNORM;

				case RHIPixelFormat::DEPTH32_F32:
					return VK_FORMAT_D32_SFLOAT;

				case RHIPixelFormat::DEPTH24_UNORM_STENCIL8_U32:
					return VK_FORMAT_D24_UNORM_S8_UINT;

				case RHIPixelFormat::DEPTH32_F32_STENCIL8_U32:
					return VK_FORMAT_D32_SFLOAT_S8_UINT;


				default:
					LOG("[Texture] Unsupported image bit-depth!");
					return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}
	}
	VkCommandBuffer BeginSingleTimeCommands(VkDevice device, VkCommandPool commandPool)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;
		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	void EndSingleTimeCommands(VkDevice device, VkQueue queue, VkCommandPool commandPool,VkCommandBuffer commandBuffer)
	{
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo;
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		submitInfo.pSignalSemaphores = nullptr;
		submitInfo.pNext = nullptr;
		submitInfo.pWaitDstStageMask = nullptr;
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.waitSemaphoreCount = 0;

		vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(queue);

		vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
	}
	void TransitionImageLayout(VkDevice device, VkQueue queue, VkCommandPool commandPool, 
		VkImage image, VkFormat format, VkImageLayout oldImageLayout, VkImageLayout newImageLayout,
		u32 mipLevels, u32 layerCount, VkCommandBuffer commandBuffer)
	{

		bool singleTimeCommand = false;

		if (!commandBuffer)
		{
			commandBuffer = BeginSingleTimeCommands(device, commandPool);
			singleTimeCommand = true;
		}

		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = IsDepthFormat(format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;

		if (IsStencilFormat(format))
			subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;

		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = mipLevels;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount = layerCount;

		// Create an image barrier object
		VkImageMemoryBarrier imageMemoryBarrier = VkImageMemoryBarrier();
		imageMemoryBarrier.oldLayout = oldImageLayout;
		imageMemoryBarrier.newLayout = newImageLayout;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange = subresourceRange;
		imageMemoryBarrier.srcAccessMask = LayoutToAccessMask(oldImageLayout, false);
		imageMemoryBarrier.dstAccessMask = LayoutToAccessMask(newImageLayout, true);
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		VkPipelineStageFlags sourceStage = 0;
		{
			if (imageMemoryBarrier.oldLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			{
				sourceStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			}
			else if (imageMemoryBarrier.srcAccessMask != 0)
			{
				sourceStage = AccessFlagsToPipelineStage(imageMemoryBarrier.srcAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
			}
			else
			{
				sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			}
		}

		VkPipelineStageFlags destinationStage = 0;
		{
			if (imageMemoryBarrier.newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			{
				destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			}
			else if (imageMemoryBarrier.dstAccessMask != 0)
			{
				destinationStage = AccessFlagsToPipelineStage(imageMemoryBarrier.dstAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
			}
			else
			{
				destinationStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			}
		}

		// Put barrier inside setup command buffer
		vkCmdPipelineBarrier(
			commandBuffer,
			sourceStage,
			destinationStage,
			0,
			0, nullptr,
			0, nullptr,
			1, &imageMemoryBarrier);

		if (singleTimeCommand)
			EndSingleTimeCommands(device, queue, commandPool, commandBuffer);
	}



}