#include <Engine/Render/VertexBuffer.h>
#include <Engine/Render/Vulkan/VkVertexBuffer.h>
namespace MeteorEngine
{
    VertexBuffer *VertexBuffer::Create(f32 *vertices, u32 size)
    {
		return new VulkanVertexBuffer(vertices, size);
    }
}
