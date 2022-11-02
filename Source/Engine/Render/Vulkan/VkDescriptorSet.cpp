#include <Engine/Render/Vulkan/VkDescriptorSet.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkShader.h>
#include <Engine/Render/Vulkan/VkRenderer.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkUniformBuffer.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
namespace MeteorEngine
{

	u32 g_DescriptorSetCount = 0;
	VulkanDescriptorSet::VulkanDescriptorSet()
	{

	}
	VulkanDescriptorSet::VulkanDescriptorSet(const DescriptorInfo& info)
	{

		m_FramesInFlight = u32(RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount());
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = VkDescriptorSetAllocateInfo();
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocateInfo.descriptorPool = VulkanRenderer::GetDescriptorPool();
		descriptorSetAllocateInfo.pSetLayouts = static_cast<VulkanShader*>(info.shader)->GetDescriptorLayout(info.layoutIndex);
		descriptorSetAllocateInfo.descriptorSetCount = info.count;
		descriptorSetAllocateInfo.pNext = nullptr;

		m_Shader = info.shader;
		m_Descriptors = m_Shader->GetDescriptorInfo(info.layoutIndex);

		for (auto& descriptor : m_Descriptors.descriptors)
			if (descriptor.type == DescriptorType::UNIFORM_BUFFER)
			{
				for (u32 frame = 0; frame < m_FramesInFlight; frame++)
				{
					// Uniform Buffer per frame in flight
					auto buffer = UniformBuffer::Create(NULL, descriptor.size);
					m_UniformBuffers[frame][descriptor.name] = buffer;
				}

				Buffer localStorage;
				localStorage.Allocate(descriptor.size);
				localStorage.InitialiseEmpty();

				UniformBufferInfo info;
				info.LocalStorage = localStorage;
				info.HasUpdated[0] = false;
				info.HasUpdated[1] = false;
				info.HasUpdated[2] = false;
				info.m_Members = descriptor.m_Members;
				m_UniformBuffersData[descriptor.name] = info;
			}

		for (u32 frame = 0; frame < m_FramesInFlight; frame++)
		{
			m_DescriptorDirty[frame] = true;
			m_DescriptorUpdated[frame] = false;
			m_DescriptorSet[frame] = NULL;
			g_DescriptorSetCount++;
			(vkAllocateDescriptorSets(VulkanDevice::GetInstance()->GetLogicalDevice(), &descriptorSetAllocateInfo, &m_DescriptorSet[frame]));
		}
	}
	VulkanDescriptorSet::~VulkanDescriptorSet()
	{
		for (uint32_t frame = 0; frame < m_FramesInFlight; frame++)
		{
			if (!m_DescriptorSet[frame])
				continue;

			auto descriptorSet = m_DescriptorSet[frame];
			auto pool = VulkanRenderer::GetDescriptorPool();
			auto device = VulkanDevice::GetInstance()->GetLogicalDevice();
			std::map<std::string, UniformBuffer*> buffers = m_UniformBuffers[frame];
			vkFreeDescriptorSets(device, pool, 1, &descriptorSet);
		}

		for (auto it = m_UniformBuffersData.begin(); it != m_UniformBuffersData.end(); it++)
		{
			it->second.LocalStorage.Release();
		}

		g_DescriptorSetCount -= 3;
	}

	void TransitionImageToCorrectLayout(Texture* texture)
	{
		if (!texture)
			return;

		auto commandBuffer = RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer();
		if (texture->GetType() == TextureType::COLOR)
		{
			if (((VulkanTexture2D*)texture)->GetImageLayout() != VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
			{
				((VulkanTexture2D*)texture)->TransitionImage(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer() );
			}
		}
		else if (texture->GetType() == TextureType::DEPTH)
		{
			((VulkanTextureDepth*)texture)->TransitionImage(VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());
		}
	}

	void VulkanDescriptorSet::TransitionImages(CommandBuffer* commandBuffer)
	{
		for (auto& imageInfo : m_Descriptors.descriptors)
		{
			if ((imageInfo.type == DescriptorType::IMAGE_SAMPLER || imageInfo.type == DescriptorType::IMAGE_STORAGE) && (imageInfo.texture || imageInfo.textures))
			{
				if (imageInfo.textureCount == 1)
				{
					if (imageInfo.texture)
					{
						if (imageInfo.type == DescriptorType::IMAGE_STORAGE)
							((VulkanTexture2D*)imageInfo.texture)->TransitionImage(VK_IMAGE_LAYOUT_GENERAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer() );
						else
							TransitionImageToCorrectLayout(imageInfo.texture);
					}
				}
			}
		}
	}

	void VulkanDescriptorSet::SetUniform(const std::string& bufferName, const std::string& uniformName, void* data)
	{
		std::map<std::string, UniformBufferInfo>::iterator itr = m_UniformBuffersData.find(bufferName);
		if (itr != m_UniformBuffersData.end())
		{
			for (auto& member : itr->second.m_Members)
			{
				if (member.name == uniformName)
				{
					itr->second.LocalStorage.Write(data, member.size, member.offset);

					itr->second.HasUpdated[0] = true;
					itr->second.HasUpdated[1] = true;
					itr->second.HasUpdated[2] = true;
					return;
				}
			}
		}

		LOGLN("Uniform not found {0}.{1}", bufferName, uniformName);
	}

	void VulkanDescriptorSet::SetUniform(const std::string& bufferName, const std::string& uniformName, void* data, u32 size)
	{
		std::map<std::string, UniformBufferInfo>::iterator itr = m_UniformBuffersData.find(bufferName);
		if (itr != m_UniformBuffersData.end())
		{
			for (auto& member : itr->second.m_Members)
			{
				if (member.name == uniformName)
				{
					itr->second.LocalStorage.Write(data, size, member.offset);
					itr->second.HasUpdated[0] = true;
					itr->second.HasUpdated[1] = true;
					itr->second.HasUpdated[2] = true;
					return;
				}
			}
		}

		LOGLN("Uniform not found {0}.{1}", bufferName, uniformName);
	}

	void VulkanDescriptorSet::SetUniformBufferData(const std::string& bufferName, void* data)
	{
		std::map<std::string, UniformBufferInfo>::iterator itr = m_UniformBuffersData.find(bufferName);
		if (itr != m_UniformBuffersData.end())
		{
			itr->second.LocalStorage.Write(data, itr->second.LocalStorage.GetSize(), 0);
			itr->second.HasUpdated[0] = true;
			itr->second.HasUpdated[1] = true;
			itr->second.HasUpdated[2] = true;
			return;
		}
		LOGLN("Uniform not found {0}.{1}", bufferName);
	}
	void VulkanDescriptorSet::Update()
	{
		m_Dynamic = false;
		int descriptorWritesCount = 0;
		u32 currentFrame = RendererCommand::GetMainSwapChain()->GetCurrentBufferIndex();

		for (auto& bufferInfo : m_UniformBuffersData)
		{
			if (bufferInfo.second.HasUpdated[currentFrame])
			{
				m_UniformBuffers[currentFrame][bufferInfo.first]->SetData((cp0*)bufferInfo.second.LocalStorage.Data);
				bufferInfo.second.HasUpdated[currentFrame] = false;
			}
		}

		if (m_DescriptorDirty[currentFrame] || !m_DescriptorUpdated[currentFrame])
		{
			m_DescriptorDirty[currentFrame] = false;
			int imageIndex = 0;
			int index = 0;

			for (auto& imageInfo : m_Descriptors.descriptors)
			{
				if (imageInfo.type == DescriptorType::IMAGE_SAMPLER && (imageInfo.texture || imageInfo.textures))
				{
					if (imageInfo.textureCount == 1)
					{
						if (imageInfo.texture)
						{
							TransitionImageToCorrectLayout(imageInfo.texture);

							VkDescriptorImageInfo& des = *static_cast<VkDescriptorImageInfo*>(imageInfo.texture->GetDescriptorInfo());
							m_ImageInfoPool[imageIndex].imageLayout = des.imageLayout;
							m_ImageInfoPool[imageIndex].imageView = des.imageView;
							m_ImageInfoPool[imageIndex].sampler = des.sampler;
						}
					}
					else
					{
						if (imageInfo.textures)
						{
							for (uint32_t i = 0; i < imageInfo.textureCount; i++)
							{
								TransitionImageToCorrectLayout(imageInfo.textures[i]);

								VkDescriptorImageInfo& des = *static_cast<VkDescriptorImageInfo*>(imageInfo.textures[i]->GetDescriptorInfo());
								m_ImageInfoPool[i + imageIndex].imageLayout = des.imageLayout;
								m_ImageInfoPool[i + imageIndex].imageView = des.imageView;
								m_ImageInfoPool[i + imageIndex].sampler = des.sampler;
							}
						}
					}

					VkWriteDescriptorSet writeDescriptorSet = {};
					writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writeDescriptorSet.dstSet = m_DescriptorSet[currentFrame];
					writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
					writeDescriptorSet.dstBinding = imageInfo.binding;
					writeDescriptorSet.pImageInfo = &m_ImageInfoPool[imageIndex];
					writeDescriptorSet.descriptorCount = imageInfo.textureCount;

					m_WriteDescriptorSetPool[descriptorWritesCount] = writeDescriptorSet;
					imageIndex++;
					descriptorWritesCount++;
				}
				else if (imageInfo.type == DescriptorType::IMAGE_STORAGE && imageInfo.texture)
				{
					if (imageInfo.texture)
					{
						((VulkanTexture2D*)imageInfo.texture)->TransitionImage(VK_IMAGE_LAYOUT_GENERAL);

						VkDescriptorImageInfo& des = *static_cast<VkDescriptorImageInfo*>(imageInfo.texture->GetDescriptorInfo());
						m_ImageInfoPool[imageIndex].imageLayout = des.imageLayout;
						m_ImageInfoPool[imageIndex].imageView = imageInfo.mipLevel > 0 ? ((VulkanTexture2D*)imageInfo.texture)->GetMipImageView(imageInfo.mipLevel) : des.imageView;
						m_ImageInfoPool[imageIndex].sampler = des.sampler;
					}

					VkWriteDescriptorSet writeDescriptorSet = VkWriteDescriptorSet();
					writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writeDescriptorSet.dstSet = m_DescriptorSet[currentFrame];
					writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
					writeDescriptorSet.dstBinding = imageInfo.binding;
					writeDescriptorSet.pImageInfo = &m_ImageInfoPool[imageIndex];
					writeDescriptorSet.descriptorCount = imageInfo.textureCount;

					m_WriteDescriptorSetPool[descriptorWritesCount] = writeDescriptorSet;
					imageIndex++;
					descriptorWritesCount++;
				}

				else if (imageInfo.type == DescriptorType::UNIFORM_BUFFER)
				{
					VulkanUniformBuffer* vkUniformBuffer = (VulkanUniformBuffer*)m_UniformBuffers[currentFrame][imageInfo.name];
					m_BufferInfoPool[index].buffer = *vkUniformBuffer->GetBuffer();
					m_BufferInfoPool[index].offset = imageInfo.offset;
					m_BufferInfoPool[index].range = imageInfo.size;

					VkWriteDescriptorSet writeDescriptorSet = {};
					writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writeDescriptorSet.dstSet = m_DescriptorSet[currentFrame];
					writeDescriptorSet.descriptorType = DescriptorTypeToVK(imageInfo.type);
					writeDescriptorSet.dstBinding = imageInfo.binding;
					writeDescriptorSet.pBufferInfo = &m_BufferInfoPool[index];
					writeDescriptorSet.descriptorCount = 1;

					m_WriteDescriptorSetPool[descriptorWritesCount] = writeDescriptorSet;
					index++;
					descriptorWritesCount++;

					if (imageInfo.type == DescriptorType::UNIFORM_BUFFER_DYNAMIC)
						m_Dynamic = true;
				}
			}

			vkUpdateDescriptorSets(VulkanDevice::GetInstance()->GetLogicalDevice(), descriptorWritesCount,
				m_WriteDescriptorSetPool, 0, nullptr);

			m_DescriptorUpdated[currentFrame] = true;
		}
	}
}