#ifndef VKUNIFORMBUFFER_H
#define VKUNIFORMBUFFER_H
#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/CommandBuffer.h>

namespace MeteorEngine
{
	class METEOR_API VulkanUniformBuffer : public VulkanBuffer
	{
	public:
		VulkanUniformBuffer(cp0*, u32);
		~VulkanUniformBuffer();
		void SetData(cp0*, u32);
	};
}
#endif // !VKUNIFORMBUFFER_H
