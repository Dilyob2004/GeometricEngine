#ifndef VKBUFFER_H
#define VKBUFFER_H
#include <Engine/Render/Vulkan/Vk.h>
namespace MeteorEngine
{
	class METEOR_API VulkanBuffer
	{
	public:
		VulkanBuffer(VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperyFlags, u32 size, const void* data);
		VulkanBuffer();
		virtual ~VulkanBuffer();

		void Create(VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperyFlags, u32 size, const void* data);
		void Resize(u32 size, const void* data);
		void SetData(u32 size, const void* data);

		void Map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void UnMap();

		void Flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void Invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void Destroy(bool deletionQueue = false);
		


		const VkBuffer& GetBuffer() const { return m_Buffer; }
		void SetUsage(VkBufferUsageFlags flags) { m_UsageFlags = flags; }
		void SetMemoryProperyFlags(VkBufferUsageFlags flags) { m_MemoryProperyFlags = flags; }

		const VkDescriptorBufferInfo& GetBufferInfo() const { return m_DesciptorBufferInfo; };
	protected:
		VkBuffer			m_Buffer{};
		VkDeviceMemory		m_Memory{};
		VkDescriptorBufferInfo m_DesciptorBufferInfo{};
		VkDeviceSize m_Size = 0;
		VkDeviceSize m_Alignment = 0;
		VkBufferUsageFlags m_UsageFlags;
		VkMemoryPropertyFlags m_MemoryProperyFlags;
		void* m_Mapped = nullptr;
	};
}
#endif // !VKBUFFER_H
