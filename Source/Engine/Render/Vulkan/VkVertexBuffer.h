#ifndef VKVERTEXBUFFER_H
#define VKVERTEXBUFFER_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanVertexBuffer : public VulkanBuffer
	{
	public:
		VulkanVertexBuffer(cp0, u32 );
		~VulkanVertexBuffer();
		void Bind(CommandBuffer*);
		void UnBind(){}
		void SetData(cp0, u32);
		void Resize(u32);
		u32 GetSize() const { return m_Size; }
	protected:
		u32 m_Size;
		bool m_MappedBuffer;
	};
}
#endif // !VKVERTEXBUFFER_H
