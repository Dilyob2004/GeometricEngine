
#include <Engine/Render/FrameBuffer.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
namespace MeteorEngine
{
    FrameBuffer* FrameBuffer::Create(const FrameBufferDesc& spec)
    {
		return new VulkanFrameBuffer(spec);
    }

}
