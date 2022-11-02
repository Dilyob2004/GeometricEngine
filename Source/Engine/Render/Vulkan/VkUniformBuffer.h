#ifndef VKUNIFORMBUFFER_H
#define VKUNIFORMBUFFER_H
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/UniformBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanUniformBuffer : public UniformBuffer, public VulkanBuffer
	{
	public:
		VulkanUniformBuffer(cp0*, u32);
		virtual ~VulkanUniformBuffer();
		virtual void SetData(cp0*, u32) override;
		virtual void SetData(cp0* data) override { SetData(data, m_Size); }

		VkBuffer* GetBuffer() { return &m_Buffer; }
		VkDeviceMemory* GetMemory() { return &m_Memory; }
		const VkDescriptorBufferInfo& GetBufferInfo() const { return m_DesciptorBufferInfo; };
	};
}
#endif // !VKUNIFORMBUFFER_H
