#ifndef VKINDEXBUFFER_H
#define VKINDEXBUFFER_H
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanIndexBuffer : public VulkanBuffer
	{
	public:
		//VulkanIndexBuffer(u16*, u32 count);
		VulkanIndexBuffer(u32*, u32 count);
		~VulkanIndexBuffer();

		void Bind(CommandBuffer*);
		void UnBind();

		u32 GetSize() { return m_Size; }
		u32 GetCount() { return m_Count; }


	private:
		u32 m_Size;
		u32 m_Count;
		bool m_MappedBuffer{ false };

	};
}
#endif // !VKINDEXBUFFER_H
