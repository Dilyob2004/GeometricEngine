
#include <Engine/Render/IndexBuffer.h>
#include <Engine/Render/Vulkan/VkIntexBuffer.h>
namespace MeteorEngine
{
    IndexBuffer *IndexBuffer::Create(u32 *indices, u32 size)
    {
		return new VulkanIndexBuffer(indices, size);
    }
}
