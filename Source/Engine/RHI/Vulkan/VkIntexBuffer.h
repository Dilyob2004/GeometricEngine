#ifndef VKINDEXBUFFER_H
#define VKINDEXBUFFER_H
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/IndexBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanIndexBuffer : public IndexBuffer, public VulkanBuffer
	{
	public:
		//VulkanIndexBuffer(u16*, u32 count);
		VulkanIndexBuffer(u32*, u32 count);
		virtual ~VulkanIndexBuffer();

		virtual void Bind(CommandBuffer*) const override;
		virtual void UnBind() const override;

		virtual u32 GetSize() const override  { return m_Size; }
		virtual u32 GetCount() const override { return m_Count; }


	private:
		u32 m_Size;
		u32 m_Count;
		bool m_MappedBuffer{ false };

	};
}
#endif // !VKINDEXBUFFER_H
