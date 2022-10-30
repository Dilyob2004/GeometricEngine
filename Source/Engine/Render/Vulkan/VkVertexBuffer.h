#ifndef VKVERTEXBUFFER_H
#define VKVERTEXBUFFER_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/VertexBuffer.h>
namespace MeteorEngine
{
	class METEOR_API VulkanVertexBuffer : public VertexBuffer, public VulkanBuffer
	{
	public:
		VulkanVertexBuffer(f32*, u32 );
		~VulkanVertexBuffer();
		void Bind(CommandBuffer*) const override;
		void UnBind() const override {}
		void SetData(f32*, u32) override;
		void Resize(u32) override;
		u32 GetSize() const override { return m_Size; }
	protected:
		u32 m_Size;
		bool m_MappedBuffer;
	};
}
#endif // !VKVERTEXBUFFER_H
